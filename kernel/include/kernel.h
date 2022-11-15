#if !defined(KERNEL_KERNEL_H)
#define KERNEL_KERNEL_H

#include "io.h"

#define __infinite_loop() \
        do {              \
        } while (1)

#define panic(...)                    \
        do {                          \
                kprintf("PANIC! ");   \
                kprintf(__VA_ARGS__); \
                kprintf("\n");        \
                __infinite_loop();    \
        } while (0)

// TODO How to I stop the kernel from now on??
#define kassert(expr)                                                   \
        do {                                                            \
                if (!(expr)) {                                          \
                        kprintf("ERROR [%s:%d] Failed assertion: %s\n", \
                                __FILE__, __LINE__, #expr);             \
                        __infinite_loop();                              \
                }                                                       \
        } while (0)

#define klog(level, ...)                  \
        do {                              \
                kprintf("[%s] ", #level); \
                kprintf(__VA_ARGS__);     \
        } while (0)

#define __USER
#define __KERNEL
#define __IN
#define __OUT

#endif  // KERNEL_KERNEL_H
