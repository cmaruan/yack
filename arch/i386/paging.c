#include "x86.h"

__attribute__((__aligned__(X86_PAGESZ)))  //
pde_t x86_page_directory[X86_PDT_NENTRIES] = {
    // Map virtual [0, 4MB) to physical [0, 4MB)
    [0] = (X86_PDE_PRESENT | X86_PDE_RW | X86_PDE_PS),
    // Map virtual [X86_KERNEL_BASE, X86_KERNEL_BASE + 4MB) to physical [0, 4MB)
    [X86_PD_INDEX(X86_KERNEL_BASE)] =
        (X86_PDE_PRESENT | X86_PDE_RW | X86_PDE_PS),
    // Map the 4MB after Kernel VM to Physical [4, 8MB)
    [X86_PD_INDEX(X86_KERNEL_BASE) + 1] =
        (4 << 20) | (X86_PDE_PRESENT | X86_PDE_RW | X86_PDE_PS),
};