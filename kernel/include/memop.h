#if !defined(KERNEL_MEMORY_OPERATIONS_H)
#define KERNEL_MEMORY_OPERATIONS_H

#include <stddef.h>

#include "types.h"

void* memset(void* ptr, uint8_t val, size_t size);
void* memcpy(void* dst, const void* src, size_t size);
void* memmove(void* dst, const void* src, size_t size);

#endif  // KERNEL_MEMORY_OPERATIONS_H
