#include "memop.h"

void*
memset(void* ptr_, uint8_t val, size_t size)
{
        char* ptr = ptr_;
        while (size-- != 0) {
                *ptr++ = val;
        }
        return ptr_;
}
void*
memcpy(void* dst_, const void* src_, size_t size)
{
        char* dst = dst_;
        const char* src = src_;
        while (size-- != 0) {
                *dst++ = *src++;
        }
        return dst_;
}
void*
memmove(void* dst_, const void* src_, size_t size)
{
        if (dst_ < src_)
                return memcpy(dst_, src_, size);
        char* dst = dst_ + size;
        const char* src = src_ + size;
        while (size-- != 0) {
                *--dst = *--src;
        }
        return dst_;
}
