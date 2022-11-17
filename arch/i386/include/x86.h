#ifndef ARCH_I386_X86_H
#define ARCH_I386_X86_H
#include "types.h"

///////////////////////////////////////////////////////////////////////////////
// x86 Kernel Loading Addresses
///////////////////////////////////////////////////////////////////////////////
#define X86_EXTENDED_MEMORY 0x00100000  // Start of Extended Memory: 1MB
#define X86_KERNEL_BASE     0x80000000
#define X86_KERNEL_LINK     (X86_KERNEL_BASE + X86_EXTENDED_MEMORY)

///////////////////////////////////////////////////////////////////////////////
// Conversion between Physical and Virtual addresses within kernel space
///////////////////////////////////////////////////////////////////////////////
#define X86_PHYSADDR(va) ((va) - (X86_KERNEL_BASE))
#define X86_VIRTADDR(pa) ((pa) + (X86_KERNEL_BASE))

///////////////////////////////////////////////////////////////////////////////
// Control Register Flags
///////////////////////////////////////////////////////////////////////////////
// Control Register 0 (CR0)
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

// Control Register 4 (CR4)
#define X86_CR4_VME (1 << 0)  // Virtual 8086 Mode Extensions
#define X86_CR4_PVI (1 << 1)  // Protected mode Virtual Interrupts
#define X86_CR4_TSD (1 << 2)  // Time Stamp Disable
#define X86_CR4_DE  (1 << 3)  // Debugging Extensions
#define X86_CR4_PSE (1 << 4)  // Page Size Extension
#define X86_CR4_PAE (1 << 5)  // Physical Address Extension
#define X86_CR4_MCE (1 << 6)  // Machine Check Exception
#define X86_CR4_PGE (1 << 7)  // Page Global Enabled
#define X86_CR4_PCE (1 << 8)  // Performance Monitoring Counter Enable

///////////////////////////////////////////////////////////////////////////////
// x86 Page Directory Flags
///////////////////////////////////////////////////////////////////////////////
#define X86_PDE_PRESENT (1 << 0)   // Present
#define X86_PDE_RW      (1 << 1)   // Read-Write
#define X86_PDE_US      (1 << 2)   // User/Supervisor
#define X86_PDE_PWT     (1 << 3)   // Write Through
#define X86_PDE_PCD     (1 << 4)   // Cache Disabled
#define X86_PDE_A       (1 << 5)   // Accessed
#define X86_PDE_DIRTY   (1 << 6)   // Dirty
#define X86_PDE_PS      (1 << 7)   // Page Size. Indicates a 4MB Page
#define X86_PDE_GLOBAL  (1 << 8)   // Global
#define X86_PDE_AVL     (3 << 9)   // Application Specific (For OS usage)
#define X86_PDE_PAT     (1 << 12)  // Page attribute Table

///////////////////////////////////////////////////////////////////////////////
// x86 Page Entry Flags
///////////////////////////////////////////////////////////////////////////////
#define X86_PTE_PRESENT (1 << 0)  // Present
#define X86_PTE_RDONLY  (0 << 1)  // Read Only
#define X86_PTE_RDWR    (1 << 1)  // Read and Write
#define X86_PTE_USER    (1 << 2)  // Userland can access it
#define X86_PTE_KERNEL  (0 << 2)  // Only kernel can access it
#define X86_PTE_PWT     (1 << 3)  // Write Through
#define X86_PTE_PCD     (1 << 4)  // Cache Disabled
#define X86_PTE_A       (1 << 5)  // Accessed
#define X86_PTE_DIRTY   (1 << 6)  // Dirty
#define X86_PTE_PAT     (1 << 7)  // Page Attribute Table
#define X86_PTE_GLOBAL  (1 << 8)  // Global
#define X86_PTE_AVL     (3 << 9)  // Application Specific (For OS usage)

///////////////////////////////////////////////////////////////////////////////
// x86 Paging Masks and Helpers
///////////////////////////////////////////////////////////////////////////////
#define X86_PDT_NENTRIES 1024  // Total directory entries
#define X86_PDOFF        22  // Offset of Page Directory Index in a linear address
#define X86_PTOFF        12    // Offset of Page Table Index in a linear address
#define X86_PAGESZ       4096  // Page size in bytes
// Extract Page Directory Index from Virtual Address
#define X86_PD_INDEX(va) (((va) >> X86_PDOFF) & 0x3FF)
// Extract Page Table Index from Virtual Address
#define X86_PT_INDEX(va)   (((va) >> X86_PTOFF) & 0x3FF)
#define X86_PTE_ADDR(pte)  ((u32)(pte) & (~0xFFF))
#define X86_PTE_FLAGS(pte) ((u32)(pte) & (0xFFF))

// Make Virtual Address from directory, table and offset
#define X86_MKVA(dir, tab, off)                                             \
        ((u32)((dir & 0x3FF) << X86_PDOFF) | ((tab & 0x3FF) << X86_PTOFF) | \
         (off & 0xFFF))

#define X86_PG_ROUNDUP(size)   (((size) + X86_PAGESZ - 1) & ~(X86_PAGESZ - 1))
#define X86_PG_ROUNDDOWN(size) ((size) & ~(X86_PAGESZ - 1))

///////////////////////////////////////////////////////////////////////////////
// x86 Serial ports
///////////////////////////////////////////////////////////////////////////////
#define X86_SERIAL_COM1_BASE 0x3F8

///////////////////////////////////////////////////////////////////////////////
// x86 Serial Ports Operations
///////////////////////////////////////////////////////////////////////////////
#define X86_SERIAL_DATA_PORT(base)        (base)
#define X86_SERIAL_FIFO_CMD_PORT(base)    ((base) + 2)
#define X86_SERIAL_LINE_CMD_PORT(base)    ((base) + 3)
#define X86_SERIAL_MODEM_CMD_PORT(base)   ((base) + 4)
#define X86_SERIAL_LINE_STATUS_PORT(base) ((base) + 5)
// Instructs the serial port to expect the highest 8 bits on the data port, then
// the lowest 8 bits afterwards
#define X86_SERIAL_LINE_ENABLE_DLAB 0x80

#define X86_GDT_PRESENT  (1 << 7)  // if segment is valid and present
#define X86_GDT_USER     (3 << 5)  // Privilege 3: user
#define X86_GDT_KERNEL   (0 << 5)  // Privilege 0: kernel
#define X86_GDT_SEG      (1 << 4)  // 0 for system segment, 1 for either data or code
#define X86_GDT_X        (1 << 3)  // 0 for data, 1 for code
#define X86_GDT_DC       (1 << 2)  // Direction/Conformity
#define X86_GDT_RW       (1 << 1)  // 1 allows write data/read code. 0 denies
#define X86_GDT_ACCESSED (1 << 0)  // If segment is accessed
#define X86_GDT_G        (1 << 3)  // If set, limit is in 4KB blocks
#define X86_GDT_DB       (1 << 2)  // If set, segment is in 32bit protected mode

#define X86_GDT_SEG_NULL  0
#define X86_GDT_SEG_CODEK 1
#define X86_GDT_SEG_DATAK 2
#define X86_GDT_SEG_CODEU 3
#define X86_GDT_SEG_DATAU 4
#define X86_GDT_SEG_TSS   5
#define X86_GDT_SEG_SIZE  6

#define X86_MAX_CPU 16

#ifndef __ASSEMBLY__
#include "kernel.h"

// GDT registry
struct gdtr {
        u16 g_limit;
        u32 g_base;
} __attribute__((packed));

// a GDT entry
struct gdt_entry {
        u16 ge_limit_low;  // bits 0-15
        u16 ge_base_low;   // bits 0-15
        u8 ge_base_mid;    // bits 16-23
        u8 ge_access;      // access byte
        u8 ge_flags;       // granularity and size flags
        u8 ge_base_high;   // bits 24-31
} __attribute__((packed));

struct arch_cpu {
        u8 c_apicid;
};

struct trapframe {
        // registers as pushed by pusha
        u32 edi;
        u32 esi;
        u32 ebp;
        u32 oesp;  // useless & ignored
        u32 ebx;
        u32 edx;
        u32 ecx;
        u32 eax;

        // rest of trap frame
        u16 gs;
        u16 padding1;
        u16 fs;
        u16 padding2;
        u16 es;
        u16 padding3;
        u16 ds;
        u16 padding4;
        u32 trapno;

        // below here defined by x86 hardware
        u32 err;
        u32 eip;
        u16 cs;
        u16 padding5;
        u32 eflags;

        // below here only when crossing rings, such as from user to kernel
        u32 esp;
        u16 ss;
        u16 padding6;
};

typedef u32 pde_t;
extern pde_t x86_page_directory[];
extern u32 x86_lapic;

static inline void
cli(void)
{
        asm volatile("cli");
}

static inline void
sti(void)
{
        asm volatile("sti");
}

static inline void
stosb(void *addr, int data, int cnt)
{
        asm volatile("cld; rep stosb"
                     : "=D"(addr), "=c"(cnt)
                     : "0"(addr), "1"(cnt), "a"(data)
                     : "memory", "cc");
}
static inline u32
x86_get_cr0()
{
        u32 value;
        asm volatile("movl %%cr0, %0;"
                     : "=r"(value) /* output */
        );
        return value;
}
static inline u32
x86_get_cr2()
{
        u32 value;
        asm volatile("movl %%cr2, %0;"
                     : "=r"(value) /* output */
        );
        return value;
}
static inline u32
x86_get_cr3()
{
        u32 value;
        asm volatile("movl %%cr3, %0;"
                     : "=r"(value) /* output */
        );
        return value;
}
static inline u32
x86_get_cr4()
{
        u32 value;
        asm volatile("movl %%cr4, %0;"
                     : "=r"(value) /* output */
        );
        return value;
}

static inline void
x86_set_cr0(u32 value)
{
        asm volatile(
            "movl %%cr0, %%eax; "
            "orl  %0, %%eax;    "
            "movl %%eax, %%cr0; "
            :            /* output */
            : "r"(value) /* input */
            : "%eax"     /* clobbered register */
        );
}
static inline void
x86_set_cr2(u32 value)
{
        asm volatile(
            "movl %%cr2, %%eax; "
            "orl  %0, %%eax;    "
            "movl %%eax, %%cr2; "
            :            /* output */
            : "r"(value) /* input */
            : "%eax"     /* clobbered register */
        );
}
static inline void
x86_set_cr3(u32 value)
{
        asm volatile(
            "movl %%cr3, %%eax; "
            "orl  %0, %%eax;    "
            "movl %%eax, %%cr3; "
            :            /* output */
            : "r"(value) /* input */
            : "%eax"     /* clobbered register */
        );
}
static inline void
x86_set_cr4(u32 value)
{
        asm volatile(
            "movl %%cr4, %%eax; "
            "orl  %0, %%eax;    "
            "movl %%eax, %%cr4; "
            :            /* output */
            : "r"(value) /* input */
            : "%eax"     /* clobbered register */
        );
}
void x86_lgdt(void *gdt_desc, int ds, int cs);

static inline void
x86_lidt(void *desc, u16 size)
{
        volatile u16 ptr[3];
        u32 addr = (u32)desc;
        ptr[0] = size - 1;
        ptr[1] = (u16)(addr);
        ptr[2] = (u16)((addr) >> 16);
        klog(DEBUG, "lidt: addr: %p, ptr: %x %x %x\n", addr, ptr[0], ptr[1],
             ptr[2]);

        asm volatile("lidt (%0)" : : "r"(ptr));
}

static inline void
outb(u16 port, u8 data)
{
        asm volatile("out %0,%1" : : "a"(data), "d"(port));
}

static inline void
outw(u16 port, u16 data)
{
        asm volatile("out %0,%1" : : "a"(data), "d"(port));
}
static inline void
io_wait(void)
{
        outb(0x80, 0);
}
static inline u8
inb(u16 port)
{
        u8 data;
        asm volatile("in %1,%0" : "=a"(data) : "d"(port));
        return data;
}
static inline u16
inw(u16 port)
{
        u16 data;
        asm volatile("in %1,%0" : "=a"(data) : "d"(port));
        return data;
}
static inline void
insl(int port, void *addr, int cnt)
{
        asm volatile("cld; rep insl"
                     : "=D"(addr), "=c"(cnt)
                     : "d"(port), "0"(addr), "1"(cnt)
                     : "memory", "cc");
}

#define X86_PIC1_CMD    0x20
#define X86_PIC1_DATA   0x21
#define X86_PIC2_CMD    0xA0
#define X86_PIC2_DATA   0xA1
#define X86_PIC1_OFFSET 0x20
#define X86_PIC2_OFFSET 0x28

/* reinitialize the PIC controllers, giving them specified vector offsets
   rather than 8h and 70h, as configured by default */

#define ICW1_ICW4      0x01 /* ICW4 (not) needed */
#define ICW1_SINGLE    0x02 /* Single (cascade) mode */
#define ICW1_INTERVAL4 0x04 /* Call address interval 4 (8) */
#define ICW1_LEVEL     0x08 /* Level triggered (edge) mode */
#define ICW1_INIT      0x10 /* Initialization - required! */

#define ICW4_8086       0x01 /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO       0x02 /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE  0x08 /* Buffered mode/slave */
#define ICW4_BUF_MASTER 0x0C /* Buffered mode/master */
#define ICW4_SFNM       0x10 /* Special fully nested (not) */

#define PIC_EOI 0x20 /* End-of-interrupt command code */

static inline void
x86_pic_eoi(unsigned char irq)
{
        if (irq >= X86_PIC1_OFFSET)
                outb(X86_PIC1_CMD, PIC_EOI);
        if (irq >= X86_PIC2_OFFSET)
                outb(X86_PIC2_CMD, PIC_EOI);
}

/*
 * Flush the GDT registry to the processor. This function is
 * defined in `boot.s'.
 */
extern void gdt_flush(struct gdtr gdtr);

// void x86_gdt_set(size_t num, u32 base, u32 limit, u8 access,
//                  u8 flags);

// void x86_gdt_install();

// static inline void
// x86_encode_gdt_entry(u8 *target, const struct gdt *entry)
// {
//         // Check the limit to make sure that it can be encoded
//         if (entry->dt_limit > 0xFFFFF) {
//                 panic("GDT cannot encode limits larger than 0xFFFFF");
//         }

//         // Encode the limit
//         target[0] = entry->dt_limit & 0xFF;
//         target[1] = (entry->dt_limit >> 8) & 0xFF;
//         target[6] = (entry->dt_limit >> 16) & 0x0F;

//         // Encode the base
//         target[2] = entry->dt_base_address & 0xFF;
//         target[3] = (entry->dt_base_address >> 8) & 0xFF;
//         target[4] = (entry->dt_base_address >> 16) & 0xFF;
//         target[7] = (entry->dt_base_address >> 24) & 0xFF;

//         // Encode the access byte
//         target[5] = entry->dt_access_byte;

//         // Encode the flags
//         target[6] |= (entry->dt_flags << 4);

//         klog(DEBUG,
//              "GDT Entry: base: %p, limit: %x, access_byte: %x flags: %x\n",
//              entry->dt_base_address, entry->dt_limit, entry->dt_access_byte,
//              entry->dt_flags);
//         klog(DEBUG, "           %x %x %x %x %x %x %x %x\n", target[0],
//              target[1], target[2], target[3], target[4], target[5],
//              target[6], target[7]);
// }

/// @brief Configures the baud rate to be used in the serial port communication.
/// The devisor argument below specifies by how much we should divide the top
/// frequency of 115200 Hz. For instance, for a divisor = 2, then the baud rate
/// would be 115200Hz / 2 = 57600Hz
/// @param com COM port to be configured
/// @param divisor Baud rate divisor
static inline void
x86_serial_config_baud_rate(u16 com, u16 divisor)
{
        outb(X86_SERIAL_LINE_CMD_PORT(com), X86_SERIAL_LINE_ENABLE_DLAB);
        outb(X86_SERIAL_DATA_PORT(com), (divisor >> 8) & 0xFF);
        outb(X86_SERIAL_DATA_PORT(com), divisor & 0xFF);
}

/// @brief Configures the line of the given serial port.
/// Default configuration is:
/// * DLAB disabled
/// * No break control
/// * No parity bits
/// * No stop bits
/// * Messages are 8 bits in length
/// @param com COM port to be configured
/// @param attr Pointer to attributes object. Not used and must be set to NULL
static inline void
x86_serial_config_line(u16 com, void *attr)
{
        /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
         * Content: | d | b | prty  | s | dl  |
         * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
         */
        (void)attr;
        outb(X86_SERIAL_LINE_CMD_PORT(com), 0x03);
}

extern unsigned int trap_counter;
extern unsigned int last_trapno;

void trap_init();
void trap_handler(struct trapframe *tf);

#endif  // __ASSEMBLY__

#endif  // ARCH_I386_X86_H