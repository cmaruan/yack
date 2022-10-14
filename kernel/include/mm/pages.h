#if !defined(KERNEL_MM_PAGES_H)
#define KERNEL_MM_PAGES_H

#include "list.h"

void kfree_range(void *start, void *end);
void kfree(void *page);

#endif  // KERNEL_MM_PAGES_H
