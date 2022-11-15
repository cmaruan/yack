#include "x86.h"
.section .text
.type reload_segments, @function
.globl reload_segments
x86_load_gdt:
        pushl %ebp
        movl %esp, %ebp

        ljmpl $0x08, $(flush_cs)
flush_cs:
        movw $(X86_GDT_SEG_DATAK << 3), %ax
        movw %ax, %es
        movw %ax, %ss
        movw %ax, %ds
        movw %ax, %fs
        movw %ax, %gs
        ret

