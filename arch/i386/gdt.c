#include "x86.h"

#define GDT_SIZE 256

struct gdt_entry gdt[GDT_SIZE];
struct gdtr gdtr;

// void
// x86_gdt_install()
// {
//         gdtr.g_limit = sizeof(gdtr) - 1;
//         gdtr.g_base = (uint32_t)X86_PHYSADDR(gdt);

//         klog(DEBUG, "Null descriptior\n");
//         // null-descriptor
//         x86_gdt_set(0, 0, 0, 0, 0);

//         klog(DEBUG, "GDT 1\n");
//         /*
//          * Code segment entry: base address 0, limit of 4GiB,
//          * 4KiB granularity, 32-bit opcodes, code segment set.
//          */
//         x86_gdt_set(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

//         klog(DEBUG, "GDT 2\n");
//         /*
//          * Data segment entry: base address 0, limit of 4GiB,
//          * 4KiB granularity, 32-bit opcodes, data segment set.
//          */
//         x86_gdt_set(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

//         klog(DEBUG, "Flushing\n");
//         gdt_flush(gdtr);
// }