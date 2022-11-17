#if !defined(KERNEL_DRIVER_SERIAL_H)
#define KERNEL_DRIVER_SERIAL_H

#include "kernel.h"
#include "types.h"
#include "x86.h"

#define SERIAL_PORTS_MAX 4

void serial_init_port(u16 com);
int serial_set_default_port(u16 com);
int serial_write(const char *buffer, size_t size);

#endif  // KERNEL_DRIVER_SERIAL_H
