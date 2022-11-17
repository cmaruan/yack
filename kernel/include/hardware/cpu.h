#if !defined(KERNEL_HARDWARE_CPU_H)
#define KERNEL_HARDWARE_CPU_H

#include "x86.h"

struct cpu {
        u32 cpp_id;
        struct gdt_entry cpu_gdt[X86_GDT_SEG_SIZE];
};

struct cpu *this_cpu();

#endif  // KERNEL_HARDWARE_CPU_H
