#if !defined(KERNEL_SPINLOCK_H)
#define KERNEL_SPINLOCK_H

struct spinlock {};

#define spinlock_acquire(sp) ((void)0)
#define spinlock_release(sp) ((void)0)

#endif  // KERNEL_SPINLOCK_H
