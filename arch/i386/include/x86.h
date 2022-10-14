#ifndef ARCH_I386_X86_H
#ifndef __ASSEMBLY__

#endif
#include "types.h"

#define X86_KERNEL_BASE 0x80000000

#define X86_PHYSADDR(va) ((va) - (X86_KERNEL_BASE))
#define X86_VIRTADDR(pa) ((pa) + (X86_KERNEL_BASE))

// Control Register 0 Masks
#define X86_CR0_PME (1 << 0)   // Protected Mode Enabled
#define X86_CR0_MP  (1 << 1)   // Monitor Co-Processor
#define X86_CR0_EM  (1 << 2)   // x87 FPU EMulation
#define X86_CR0_TS  (1 << 3)   // Task Switched
#define X86_CR0_ET  (1 << 4)   // Extention Type
#define X86_CR0_NE  (1 << 5)   // Numeric Error
#define X86_CR0_WP  (1 << 16)  // Write Protect
#define X86_CR0_AM  (1 << 18)  // Alignment Mask
#define X86_CR0_NW  (1 << 29)  // Not-Write Through
#define X86_CR0_CD  (1 << 30)  // Cache disabled
#define X86_CR0_PG  (1 << 31)  // Paging

// Control Register 4 Masks
#define X86_CR4_VME (1 << 0)  // Virtual 8086 Mode Extensions
#define X86_CR4_PVI (1 << 1)  // Protected mode Virtual Interrupts
#define X86_CR4_TSD (1 << 2)  // Time Stamp Disable
#define X86_CR4_DE  (1 << 3)  // Debugging Extensions
#define X86_CR4_PSE (1 << 4)  // Page Size Extension
#define X86_CR4_PAE (1 << 5)  // Physical Address Extension
#define X86_CR4_MCE (1 << 6)  // Machine Check Exception
#define X86_CR4_PGE (1 << 7)  // Page Global Enabled
#define X86_CR4_PCE (1 << 8)  // Performance Monitoring Counter Enable

#define X86_PDE_PRESENT (1 << 0)    // Present
#define X86_PDE_RW      (1 << 1)    // Read-Write
#define X86_PDE_US      (1 << 2)    // User/Supervisor
#define X86_PDE_PWT     (1 << 3)    // Write Through
#define X86_PDE_PCD     (1 << 4)    // Cache Disabled
#define X86_PDE_A       (1 << 5)    // Accessed
#define X86_PDE_DIRTY   (1 << 6)    // Dirty
#define X86_PDE_PS      (1 << 7)    // Page Size
#define X86_PDE_GLOBAL  (1 << 8)    // Global
#define X86_PDE_AVL     (0x3 << 9)  // Application Specific (For OS usage)
#define X86_PDE_PAT     (1 << 12)   // Page attribute Table

#define X86_PDT_NENTRIES 1024  // Total directory entries
#define X86_PDOFF        22  // Offset of Page Directory Index in a linear address
#define X86_PTOFF        12    // Offset of Page Table Index in a linear address
#define X86_PAGESZ       4096  // Page size in bytes
// Extract Page Directory Index from Virtual Address
#define X86_PD_INDEX(va) (((va) >> X86_PDOFF) & 0x3FF)
// Extract Page Table Index from Virtual Address
#define X86_PT_INDEX(va) (((va) >> X86_PTOFF) & 0x3FF)
// Make Virtual Address from directory, table and offset
#define X86_MKVA(dir, tab, off)                   \
        ((uint32_t)((dir & 0x3FF) << X86_PDOFF) | \
         ((tab & 0x3FF) << X86_PTOFF) | (off & 0xFFF))

#define X86_PG_ROUNDUP(size)   (((size) + X86_PAGESZ - 1) & ~(X86_PAGESZ - 1))
#define X86_PG_ROUNDDOWN(size) ((size) & ~(X86_PAGESZ - 1))

#ifndef __ASSEMBLY__
typedef uint32_t pde_t;
extern pde_t x86_page_directory[];

inline void
cr0_load(uint32_t *p_value)
{
        if (p_value != NULL) {
                uint32_t value;
                asm("movl %%cr0, %0;"
                    : "=r"(value) /* output */
                );
                *p_value = value;
        }
}
inline void
cr2_load(uint32_t *p_value)
{
        if (p_value != NULL) {
                uint32_t value;
                asm("movl %%cr2, %0;"
                    : "=r"(value) /* output */
                );
                *p_value = value;
        }
}
inline void
cr3_load(uint32_t *p_value)
{
        if (p_value != NULL) {
                uint32_t value;
                asm("movl %%cr3, %0;"
                    : "=r"(value) /* output */
                );
                *p_value = value;
        }
}
inline void
cr4_load(uint32_t *p_value)
{
        if (p_value != NULL) {
                uint32_t value;
                asm("movl %%cr4, %0;"
                    : "=r"(value) /* output */
                );
                *p_value = value;
        }
}

inline void
cr0_set(uint32_t value)
{
        asm("movl %%cr0, %%eax; "
            "orl  %0, %%eax;    "
            "movl %%eax, %%cr0; "
            :            /* output */
            : "r"(value) /* input */
            : "%eax"     /* clobbered register */
        );
}
inline void
cr2_set(uint32_t value)
{
        asm("movl %%cr2, %%eax; "
            "orl  %0, %%eax;    "
            "movl %%eax, %%cr2; "
            :            /* output */
            : "r"(value) /* input */
            : "%eax"     /* clobbered register */
        );
}
inline void
cr3_set(uint32_t value)
{
        asm("movl %%cr3, %%eax; "
            "orl  %0, %%eax;    "
            "movl %%eax, %%cr3; "
            :            /* output */
            : "r"(value) /* input */
            : "%eax"     /* clobbered register */
        );
}
inline void
cr4_set(uint32_t value)
{
        asm("movl %%cr4, %%eax; "
            "orl  %0, %%eax;    "
            "movl %%eax, %%cr4; "
            :            /* output */
            : "r"(value) /* input */
            : "%eax"     /* clobbered register */
        );
}

void enable_paging();
#endif  // __ASSEMBLY__

#endif  // ARCH_I386_X86_H