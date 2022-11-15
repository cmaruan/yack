#if !defined(KERNEL_MM_VM_H)
#define KERNEL_MM_VM_H

#include "memlayout.h"
#include "types.h"

// Virtual Memory Management

/// @brief Initialize the kernem virtual memory
void kvm_init();

/// @brief Create a new page with the kernel vm mapping
/// @return A newly allocated page to be used as a Page Directory Table
pde_t *kvm_create();

/// @brief Switches into the kernel page directory
void kmv_switch();

/// @brief Map the virtual address `vaddr` to `paddr`
/// @param directory A pointer to the directory to add the mapping
/// @param vaddr The virtual address
/// @param paddr The physical address being mapped to
/// @param size Number of pages to be mapped
/// @param uint16_t Permissions on the tables
/// @return Number of pages mapped. -1 if error
ssize_t vm_map_pages(pde_t *directory, void *vaddr, void *paddr, size_t size,
                     uint16_t uint16_t);

/// @brief
void segments_init();

#endif  // KERNEL_MM_VM_H
