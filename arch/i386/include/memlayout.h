#if !defined(ARCH_I386_MEMLAYOUT_H)
#define ARCH_I386_MEMLAYOUT_H

#include "x86.h"

#define KB (1 << 10U)
#define MB (1 << 20U)
#define GB (1 << 30U)

#define MM_MAXPHYS  (240 * MB)  // 240 MB of memory
#define MM_DEVSPACE (3 * GB)    // Dev devices are located at higher memory

#define MM_KERNEL_BASE X86_KERNEL_BASE

#define MM_VIRTADDR(pa) ((void*)X86_VIRTADDR((uint32_t)(pa)))
#define MM_PHYSADDR(va) ((void*)X86_PHYSADDR((uint32_t)(va)))

#define MM_PGSIZE            X86_PAGESZ
#define MM_PAGEUP(address)   X86_PG_ROUNDUP((uint32_t)(address))
#define MM_PAGEDOWN(address) X86_PG_ROUNDDOWN((uint32_t)(address))

// Returns 0 if address is not aligned to page size
#define mm_is_page_aligned(addr) ((((uint32_t)(addr)) % MM_PGSIZE) == 0)

#endif  // ARCH_I386_MEMLAYOUT_H
