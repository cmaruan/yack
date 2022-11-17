#include "drivers/serial.h"

#include "types.h"

u16 serial_default_port_;
u16 serial_ports_[SERIAL_PORTS_MAX];

void
serial_init_port(u16 com)
{
        int i;
        for (i = 0; i < SERIAL_PORTS_MAX && serial_ports_[i] != 0; i++) {
                if (serial_ports_[i] == com) {
                        klog(DEBUG, "Port %p was already initialized\n", com);
                        // This port was already added, so return
                        return;
                }
        }
        if (i == SERIAL_PORTS_MAX) {
                klog(KWARN, "No available space to init another COM port.\n");
                return;
        }
        x86_serial_config_baud_rate(com, 12);
        x86_serial_config_line(com, NULL);
        u8 status = inb(X86_SERIAL_LINE_STATUS_PORT(com));
        if (status == 0xFF) {
                klog(DEBUG, "Port %p not available\n", com);
                return;
        }
        serial_ports_[i] = com;
}

int
serial_set_default_port(u16 com)
{
        kassert(com > 0);
        int i;
        for (i = 0; i < SERIAL_PORTS_MAX; i++) {
                if (serial_ports_[i] == com) {
                        break;
                }
        }
        if (i == SERIAL_PORTS_MAX) {
                klog(KWARN, "Port %p not initialized yet...\n");
                return -1;
        }
        serial_default_port_ = com;
        return 0;
}

int
serial_write(const char *buffer, size_t size)
{
        u16 com = serial_default_port_;
        serial_default_port_ = 0;
        if (com == 0) {
                return 0;
        }
        int bytes = 0;
        for (; size-- != 0; buffer++, bytes++) {
                u8 status;
                do {
                        status = inb(X86_SERIAL_LINE_STATUS_PORT(com));
                } while (status == 0x20);
                outb(X86_SERIAL_DATA_PORT(com), *buffer);
        }
        serial_default_port_ = com;
        return bytes;
}
