#if !defined(KERNEL_IO_H)
#define KERNEL_IO_H

#include <stdarg.h>
#include <stddef.h>

#include "types.h"

#define IO_MAXBUFSIZE 4096

ssize_t write(const char *str, size_t size);
ssize_t kprintf(const char *fmt, ...);
ssize_t kvsnprintf(char *buf, size_t bufsz, const char *fmt, va_list ap);

#endif  // KERNEL_IO_H
