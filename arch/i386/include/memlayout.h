#if !defined(ARCH_I386_MEMLAYOUT_H)
#define ARCH_I386_MEMLAYOUT_H

#include "x86.h"

#define KB (1 << 10U)
#define MB (1 << 20U)
#define GB (1 << 30U)

#define MM_MAXPHYS  (240 * MB)  // 240 MB of memory
#define MM_DEVSPACE (3 * GB)    // Dev devices are located at higher memory

#define MM_KERNEL_BASE  ((void *)X86_KERNEL_BASE)
#define MM_EXTENDED_MEM ((void *)X86_EXTENDED_MEMORY)
#define MM_KERNEL_LINK  ((void *)X86_KERNEL_LINK)

#define MM_VIRTADDR(pa) ((void *)X86_VIRTADDR((u32)(pa)))
#define MM_PHYSADDR(va) ((void *)X86_PHYSADDR((u32)(va)))

#define MM_PGSIZE            X86_PAGESZ
#define MM_PAGEUP(address)   X86_PG_ROUNDUP((u32)(address))
#define MM_PAGEDOWN(address) X86_PG_ROUNDDOWN((u32)(address))

// Returns 0 if address is not aligned to page size
#define mm_is_page_aligned(addr) ((((u32)(addr)) % MM_PGSIZE) == 0)

#endif  // ARCH_I386_MEMLAYOUT_H
