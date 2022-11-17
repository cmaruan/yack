#include "hardware/cpu.h"
#include "kernel.h"
#include "memlayout.h"
#include "memop.h"
#include "mm/pages.h"
#include "mm/vm.h"

typedef u32 pte_t;

///////////////////////////////////////////////////////////////////////////////
// These symbols are exported by linker.ld
// start address of the .data section
extern char data[];
// address after kernel is loaded into memory
extern char end[];
// copy of the kernel page directory table
static pde_t *kpagedir_;

static char TSS[108];

///////////////////////////////////////////////////////////////////////////////
static int vm_map_page_(pde_t *directory, void *vaddr, void *paddr,
                        u16 permissions);

///////////////////////////////////////////////////////////////////////////////
pde_t *
kvm_create()
{
        // We allocate a page to configure the kernel page directory mapping.
        pde_t *pagedir = kpalloc();
        kassert(pagedir != NULL);

        // Map I/O space
        // 0..MM_EXTENDED_MEM to MM_KERNEL_BASE..MM_KERNEL_LINK
        // and make them writable
        vm_map_pages(pagedir, MM_KERNEL_BASE, 0, (size_t)MM_EXTENDED_MEM,
                     X86_PTE_RDWR);

        // Map Kernel .text and .rodata; .rodata ends at .data
        // Mark it as read only
        vm_map_pages(pagedir, MM_KERNEL_LINK, MM_EXTENDED_MEM,
                     MM_PHYSADDR(data) - MM_EXTENDED_MEM, X86_PTE_RDONLY);

        // Map Kernel .data as writable
        vm_map_pages(pagedir, data, MM_PHYSADDR(data), end - data,
                     X86_PTE_RDWR);

        // Map devices ???
        return pagedir;
}
///////////////////////////////////////////////////////////////////////////////
void
kvm_init()
{
        // entry.S loads the x86_page_directory array as the first
        // page directiry. This array maps the following memory:
        //      Virtual Range [0, 4MB) to [0, 4MB)
        //      Virtual Range [KERNEL_BASE, KERNEL_BASE + 4MB) to [0, 4MB)
        //
        // When kmain is executed, we assert to ensure we are loaded
        // in high virtual memory. Because of that, we can now unmap
        // the Virtual Range [0, 4MB) from [0, 4MB).
        x86_page_directory[0] = 0;

        // If the kernel is smaller than 4MB, then we have pages that could
        // be reused by other process. The value `end` is defined and
        // exported by kernel.ld and denotes the end of the kernel code. The
        // remaining memory between `end` and KERNEL_BASE + 4MB is freed
        // below.
        kpfree_range(end, MM_VIRTADDR(4 * MB));

        kpagedir_ = kvm_create();
        // kmv_switch();
}
///////////////////////////////////////////////////////////////////////////////

void
kmv_switch()
{
        x86_set_cr3((u32)MM_PHYSADDR(kpagedir_));
}
///////////////////////////////////////////////////////////////////////////////

ssize_t
vm_map_pages(pde_t *directory, void *vaddr, void *paddr, size_t size,
             u16 permissions)
{
        // NOTE from https://wiki.osdev.org/Paging
        // X86_PTE_US, the 'User/Supervisor' bit, controls access to the page
        // based on privilege level. If the bit is set, then the page may be
        // accessed by all; if the bit is not set, however, only the supervisor
        // can access it. For a page directory entry, the user bit controls
        // access to all the pages referenced by the page directory entry.
        // Therefore if you wish to make a page a user page, you must set the
        // user bit in the relevant page directory entry as well as the page
        // table entry.
        ssize_t total_maps = 0;
        void *first = (void *)MM_PAGEDOWN(vaddr);
        void *last = (void *)MM_PAGEUP(vaddr + size);
        void *curr;
        for (curr = first; curr < last; curr += MM_PGSIZE, paddr += MM_PGSIZE) {
                if (vm_map_page_(directory, curr, paddr, permissions) != 0) {
                        break;
                }
                total_maps++;
        }
        return total_maps;
}
///////////////////////////////////////////////////////////////////////////////
static inline u16 *
x86_get_gdt()
{
        static u16 values[3];
        asm volatile("sgdt (%0)" : "=m"(values));
        return values;
}
static inline u32
x86_get_segment(char segment)
{
        u32 value;
        switch (segment) {
        case 'e':
                asm volatile("movl %%es, %0;" : "=r"(value));
                break;
        case 'c':
                asm volatile("movl %%cs, %0;" : "=r"(value));
                break;
        case 's':
                asm volatile("movl %%ss, %0;" : "=r"(value));
                break;
        case 'd':
                asm volatile("movl %%ds, %0;" : "=r"(value));
                break;
        case 'f':
                asm volatile("movl %%fs, %0;" : "=r"(value));
                break;
        case 'g':
                asm volatile("movl %%gs, %0;" : "=r"(value));
                break;
        default:
                return 0xFFFFFFFF;
        }

        return value;
}
static void
x86_gdt_set(struct gdt_entry *entry, u32 base, u32 limit,
            u8 access, u8 flags)
{
        // base
        entry->ge_base_low = base & 0xFFFF;
        entry->ge_base_mid = (base >> 16) & 0xFF;
        entry->ge_base_high = (base >> 24) & 0xFF;

        // limit
        entry->ge_limit_low = limit & 0xFFFF;
        entry->ge_flags = (limit >> 16) & 0x0F;

        // access and granularity flags
        entry->ge_flags |= flags & 0xF0;
        entry->ge_access = access;
        u8 *bytes = (u8 *)entry;
        u32 *binary = (u32 *)bytes;
        klog(DEBUG, "GDT Entry: %0x %0x\n", binary[1], binary[0]);
}

void
segments_init()
{
        // x86_gdt_install();

        struct cpu *cpu = this_cpu();
        memset(cpu->cpu_gdt, 0, sizeof(cpu->cpu_gdt));
        klog(DEBUG, "GDT address: %p\n", cpu->cpu_gdt);

        x86_gdt_set(&cpu->cpu_gdt[X86_GDT_SEG_CODEK], 0, 0xFFFFFFFF, 0x9A,
                    0xCF);
        x86_gdt_set(&cpu->cpu_gdt[X86_GDT_SEG_DATAK], 0, 0xFFFFFFFF, 0x92,
                    0xCF);
        x86_gdt_set(&cpu->cpu_gdt[X86_GDT_SEG_CODEU], 0, 0xFFFFFFFF, 0xFA,
                    0xCF);
        x86_gdt_set(&cpu->cpu_gdt[X86_GDT_SEG_DATAU], 0, 0xFFFFFFFF, 0xF2,
                    0xCF);
        x86_gdt_set(&cpu->cpu_gdt[X86_GDT_SEG_TSS], (u32)TSS, sizeof(TSS),
                    0xF2, 0xCF);

        // x86_lgdt(MM_PHYSADDR(gdt_), sizeof gdt_);
        volatile u16 ptr[3];
        u32 addr = (u32)cpu->cpu_gdt;
        ptr[0] = sizeof(cpu->cpu_gdt) - 1;
        ptr[1] = (u16)(addr);
        ptr[2] = (u16)((addr) >> 16);
        x86_lgdt((void *)ptr, X86_GDT_SEG_DATAK << 3, X86_GDT_SEG_CODEK << 3);
        klog(DEBUG, "Segments loaded\n");
        klog(DEBUG, "CS: %x\n", x86_get_segment('c'));
        klog(DEBUG, "ES: %x\n", x86_get_segment('e'));
        klog(DEBUG, "SS: %x\n", x86_get_segment('s'));
        klog(DEBUG, "DS: %x\n", x86_get_segment('d'));
        klog(DEBUG, "FS: %x\n", x86_get_segment('f'));
        klog(DEBUG, "GS: %x\n", x86_get_segment('g'));
        u16 *values = x86_get_gdt();
        klog(DEBUG, "SGDT: %x %x %x\n", values[0], values[1], values[2]);
}

///////////////////////////////////////////////////////////////////////////////
// Static Functions
///////////////////////////////////////////////////////////////////////////////
static int
vm_map_page_(pde_t *directory, void *vaddr, void *paddr, u16 permissions)
{
        kassert(mm_is_page_aligned(vaddr) && mm_is_page_aligned(paddr));
        int table_index = X86_PT_INDEX((u32)vaddr);
        int page_index = X86_PD_INDEX((u32)vaddr);
        pde_t *dir_entry = &directory[page_index];
        pte_t *page_table;

        (void)table_index;
        (void)dir_entry;

        if (!(*dir_entry & X86_PDE_PRESENT)) {
                klog(DEBUG, "Allocating a new page directory\n");
                // directory does not contain an entry for the provided
                // so we allocate a new page for it
                page_table = kpalloc();

                // Maybe an assert here is too aggressive...
                kassert(page_table != NULL);

                // Set the entire page to zero
                memset(page_table, 0, MM_PGSIZE);
                *dir_entry = (pde_t)MM_PHYSADDR(page_table) | X86_PDE_PRESENT |
                             X86_PDE_RW | X86_PDE_US;
        }
        // Extract the address from the directory entry
        // Because addresses in the paging tables are physical,
        // we need to convert it to a virtual one.
        page_table = MM_VIRTADDR(X86_PTE_ADDR(*dir_entry));

        // // If we are mapping a page, we are making it present
        page_table[table_index] =
            (u32)paddr | permissions | X86_PTE_PRESENT;
        return 0;
}