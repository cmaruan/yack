#include "drivers/serial.h"
#include "kernel.h"
#include "memlayout.h"
#include "mm/vm.h"

void
do_shutdown()
{
        klog(INFO, "Shutting down...\n");
        outw(0x604, 0x2000);
}

u16
read_pit_count(void)
{
        u16 count = 0;

        // al = channel in bits 6 and 7, remaining bits clear
        outb(0x43, 0b0000100);

        count = inb(0x40);        // Low byte
        count |= inb(0x40) << 8;  // High byte
        x86_pic_eoi(X86_PIC1_OFFSET);
        io_wait();

        return count;
}

void
set_pit_count(u16 count)
{
        // Set low byte
        outb(0x40, count & 0xFF);           // Low byte
        outb(0x40, (count & 0xFF00) >> 8);  // High byte
        x86_pic_eoi(X86_PIC1_OFFSET);
        io_wait();
}

void
kmain()
{
        // The assertion below ensures that we are loaded in
        // the higher virtual memory
        cli();
        kassert((void *)kmain > (void *)MM_KERNEL_LINK);
        serial_init_port(X86_SERIAL_COM1_BASE);
        serial_set_default_port(X86_SERIAL_COM1_BASE);
        trap_init();
        kvm_init();
        segments_init();
        klog(DEBUG, "Calling STI\n");
        sti();
        for (;;) {
        }
        do_shutdown();
}
