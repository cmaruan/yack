#if !defined(KERNEL_IO_H)
#define KERNEL_IO_H

#include <stdarg.h>
#include <stddef.h>

#define IO_MAXBUFSIZE 4096

void putchar(char c);
int kprintf(const char *fmt, ...);
int kvsnprintf(char *buf, size_t bufsz, const char *fmt, va_list ap);

#endif  // KERNEL_IO_H
