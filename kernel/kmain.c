#include "kernel.h"
#include "memlayout.h"
#include "mm/pages.h"

extern char end[];
void
kmain()
{
        klog(KDEBUG, "Hello from Kernel\n");
        // Free the first 4MB
        kfree_range(end, MM_PHYSADDR(4 * MB));
}
