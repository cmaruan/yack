#include "io.h"

int
kprintf(const char *fmt, ...)
{
        char buffer[IO_MAXBUFSIZE];
        char *ptr = buffer;
        va_list ap;
        va_start(ap, fmt);
        int rv = kvsnprintf(buffer, IO_MAXBUFSIZE, fmt, ap);
        va_end(ap);
        while (*ptr) {
                putchar(*ptr++);
        }
        return rv;
}