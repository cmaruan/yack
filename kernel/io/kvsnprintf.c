#include "io.h"
#include "types.h"

static char *
strcpy(char *dest, const char *src)
{
        char *ptr = dest;
        while (*src) {
                *ptr++ = *src++;
        }
        *ptr = '\0';
        return dest;
}

static size_t
strlen(const char *src)
{
        size_t size = 0;
        while (*src++) {
                size++;
        }
        return size;
}

static const char *
utoa(uint32_t value, int base)
{
        static char buffer[16] = {0};
        char *ptr = buffer + 14;
        if (value == 0) {
                *ptr-- = '0';
        }
        else
                while (value > 0) {
                        int rem = value % base;
                        if (rem >= 0 && rem < 10) {
                                *ptr-- = '0' + rem;
                        }
                        else if (rem >= 10 && rem < base) {
                                *ptr-- = 'A' + rem - 10;
                        }
                        value /= base;
                }
        return ptr + 1;
}

static const char *
itoa(int32_t value, int base)
{
        int neg = 0;
        if (value < 0) {
                neg = 1;
                value *= -1;
        }
        char *ptr = (char *)utoa(value, base);
        if (neg)
                *ptr-- = '-';
        return ptr;
}

ssize_t
kvsnprintf(char *buf, size_t bufsz, const char *fmt, va_list ap)
{
        char *ptr = buf;
        const char *text;
        size_t fill_zeroes;
        size_t fill_length;
        size_t len;
        while (*fmt && ptr < buf + bufsz) {
                fill_length = 0;
                fill_zeroes = 0;
                if (*fmt != '%') {
                        *ptr++ = *fmt++;
                        continue;
                }
        again:
                switch (*++fmt) {
                case '0':
                        fill_zeroes = 1;
                        goto again;
                case '%':
                        text = "%";
                        break;
                case 'd':
                        text = itoa(va_arg(ap, int), 10);
                        fill_length = 10;
                        break;
                case 'p':
                        *ptr++ = '0';
                        *ptr++ = 'x';
                        fill_zeroes = 1;
                        // fallthrough
                case 'x':
                        text = utoa((uint32_t)va_arg(ap, void *), 16);
                        fill_length = 8;
                        break;
                case 's':
                        text = va_arg(ap, const char *);
                        break;
                case 'c':
                        *ptr++ = (char)va_arg(ap, int);
                        text = "";
                        break;
                case 'u':
                        text = utoa(va_arg(ap, uint32_t), 10);
                        break;
                default:
                        text = "";
                }
                len = strlen(text);
                while (fill_zeroes && len < fill_length--) {
                        *ptr++ = '0';
                }
                strcpy(ptr, text);
                ptr += strlen(text);
                fmt++;
        }
        *ptr = '\0';
        return ptr - buf;
}
