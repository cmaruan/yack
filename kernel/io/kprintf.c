#include "io.h"

ssize_t
kprintf(const char *fmt, ...)
{
        char buffer[IO_MAXBUFSIZE];
        va_list ap;
        va_start(ap, fmt);
        ssize_t bytes = kvsnprintf(buffer, IO_MAXBUFSIZE, fmt, ap);
        va_end(ap);
        if (bytes > 0)
                write(buffer, bytes);
        return bytes;
}