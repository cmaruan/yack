#if !defined(KERNEL_KERNEL_H)
#define KERNEL_KERNEL_H

#include "io.h"

#define panic(expr)
#define kassert(expr)                \
        do {                         \
                if (!(expr)) {       \
                        panic(#expr) \
                }                    \
        } while (0)

#define klog(level, ...)                  \
        do {                              \
                kprintf("[%s] ", #level); \
                kprintf(__VA_ARGS__);     \
        } while (0)

#endif  // KERNEL_KERNEL_H
