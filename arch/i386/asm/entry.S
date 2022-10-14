# Declare constants for the multiboot header.
.set ALIGN,    	1 << 0             	# align loaded modules on page boundaries
.set MEMINFO, 	1 << 1             	# provide memory map
.set FLAGS,    	ALIGN | MEMINFO  	# this is the Multiboot 'flag' field
.set MAGIC,    	0x1BADB002       	# 'magic number' lets bootloader find the header
.set CHECKSUM, 	-(MAGIC + FLAGS) 	# checksum of above, to prove we are multiboot


#include "x86.h"

# Declare a header as in the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.extern x86_page_directory



# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:

	# Turn on page size extension for 4Mbyte pages
	movl    %cr4, %eax
	orl     $(X86_CR4_PSE), %eax
	movl    %eax, %cr4

	# # Set page directory
	lea X86_PHYSADDR(x86_page_directory), %eax
	movl    %eax, %cr3

	# Turn on paging and write protect bits.
	movl    %cr0, %eax
	orl     $(X86_CR0_PG | X86_CR0_WP), %eax
	movl    %eax, %cr0

	# Jump into higher half
	lea _higher_half, %ecx
	jmp *%ecx
.size _start, . - _start


.section .text
.global _higher_half
.type _higher_half, @function
_higher_half:
	movl $stack_top, %esp

	# Call the global constructors.
	call _init

	# Transfer control to the main kernel.
	call kmain

	# Hang if kmain unexpectedly returns.
	cli
	
1:	hlt
	jmp 1b
