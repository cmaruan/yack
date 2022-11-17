#include "hardware/cpu.h"
#include "memlayout.h"
#include "x86.h"

unsigned int trap_counter;
unsigned int last_trapno;

enum {
        IDT_FLAG_GATE_TASK = 0x5,
        IDT_FLAG_GATE_16BIT_INT = 0x6,
        IDT_FLAG_GATE_16BIT_TRAP = 0x7,
        IDT_FLAG_GATE_32BIT_INT = 0xE,
        IDT_FLAG_GATE_32BIT_TRAP = 0xF,

        IDT_FLAG_RING0 = (0 << 5),
        IDT_FLAG_RING1 = (1 << 5),
        IDT_FLAG_RING2 = (2 << 5),
        IDT_FLAG_RING3 = (3 << 5),

        IDT_FLAG_PRESENT = 0x80,

};
struct trap_handler {
        u16 th_base_low;
        u16 th_segment;
        u8 th_reserved;
        u8 th_flags;
        u16 th_base_high;
} __attribute__((__packed__));

extern u32 trap_handler_array[];
struct trap_handler trap_table[256];

typedef void (*trap_handler_func_t)(struct trapframe* tf);
trap_handler_func_t trap_callback_table[256];

void keyboard_handler(struct trapframe* tf)
{
        (void)tf;
        u8 byte = inb(0x60);
        klog(TRAP, "From keyboard: %x\n", byte);
}

void
x86_pic_remap(u8 offset1, u8 offset2)
{
        unsigned char a1, a2;

        a1 = inb(X86_PIC1_DATA);  // save masks
        a2 = inb(X86_PIC2_DATA);

        outb(X86_PIC1_CMD,
             ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in
                                      // cascade mode)
        io_wait();
        outb(X86_PIC2_CMD, ICW1_INIT | ICW1_ICW4);
        io_wait();
        outb(X86_PIC1_DATA, offset1);  // ICW2: Master PIC vector offset
        io_wait();
        outb(X86_PIC2_DATA, offset2);  // ICW2: Slave PIC vector offset
        io_wait();
        outb(X86_PIC1_DATA, 4);  // ICW3: tell Master PIC that there is a slave
                                 // PIC at IRQ2 (0000 0100)
        io_wait();
        outb(X86_PIC2_DATA,
             2);  // ICW3: tell Slave PIC its cascade identity (0000 0010)
        io_wait();

        outb(X86_PIC1_DATA, ICW4_8086);
        io_wait();
        outb(X86_PIC2_DATA, ICW4_8086);
        io_wait();

        outb(X86_PIC1_DATA, a1);  // restore saved masks.
        outb(X86_PIC2_DATA, a2);
}


void
x86_set_idt_gate(int interrupt, void* base, u16 seg_desc, u8 flags)
{
        trap_table[interrupt].th_base_low = ((u32)base) & 0xFFFF;
        trap_table[interrupt].th_segment = seg_desc;
        trap_table[interrupt].th_reserved = 0;
        trap_table[interrupt].th_flags = flags;
        trap_table[interrupt].th_base_high = ((u32)base >> 16) & 0xFFFF;
}

void
x86_idt_enable(int interrupt, trap_handler_func_t callback)
{
        trap_callback_table[interrupt] = callback;
        trap_table[interrupt].th_flags |= IDT_FLAG_PRESENT;
}

void
x86_idt_disable(int interrupt)
{
        trap_callback_table[interrupt] = NULL;
        trap_table[interrupt].th_flags &= ~IDT_FLAG_PRESENT;
}

void
trap_init()
{
        for (int i = 0; i < 256; i++) {
                void* trap_addr = (void*)trap_handler_array[i];
                int flags = IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT;
                x86_set_idt_gate(i, trap_addr, 0x8, flags);
                x86_idt_enable(i, NULL);
        }
        klog(DEBUG, "sizeof struct trap_handler: %u\n",
             sizeof(struct trap_handler));
        x86_lidt(trap_table, sizeof trap_table);
        klog(DEBUG, "using idt trap_table at %p\n", trap_table);
        x86_pic_remap(X86_PIC1_OFFSET, X86_PIC2_OFFSET);
        x86_idt_enable(X86_PIC1_OFFSET + 1, keyboard_handler);
}

void
log_trapframe(const struct trapframe* tf)
{
        klog(DEBUG, "tf->TRAPNO: 0x%0x\n", tf->trapno);
        klog(DEBUG, "tf->ERR:    0x%0x\n", tf->err);

        klog(DEBUG, "tf->EAX:    0x%0x\n", tf->eax);
        klog(DEBUG, "tf->EBX:    0x%0x\n", tf->ebx);
        klog(DEBUG, "tf->EDX:    0x%0x\n", tf->edx);
        klog(DEBUG, "tf->ECX:    0x%0x\n", tf->ecx);
        klog(DEBUG, "tf->EDI:    0x%0x\n", tf->edi);

        klog(DEBUG, "tf->CS:     0x%0x\n", tf->cs);
        klog(DEBUG, "tf->DS:     0x%0x\n", tf->ds);
        klog(DEBUG, "tf->GS:     0x%0x\n", tf->gs);
        klog(DEBUG, "tf->FS:     0x%0x\n", tf->fs);
        klog(DEBUG, "tf->ES:     0x%0x\n", tf->es);
        klog(DEBUG, "tf->SS:     0x%0x\n", tf->ss);

        klog(DEBUG, "tf->ESI:    0x%0x\n", tf->esi);
        klog(DEBUG, "tf->EBP:    0x%0x\n", tf->ebp);
        klog(DEBUG, "tf->ESP:    0x%0x\n", tf->esp);
        klog(DEBUG, "tf->EIP:    0x%0x\n", tf->eip);
        klog(DEBUG, "tf->EFLAGS: 0x%0x\n", tf->eflags);
}

void
trap_handler(struct trapframe* tf)
{
        (void)tf;
        trap_counter++;
        last_trapno = tf->trapno;
        // // log_trapframe(tf);
        if (last_trapno != X86_PIC1_OFFSET)
                klog(TRAP, "trapcounter: 0x%0x    trapno: %x\n", trap_counter, tf->trapno);
        if (trap_callback_table[tf->trapno]) {
                trap_callback_table[tf->trapno](tf);
        } 
        // else {
        //         klog(TRAP, "No handler available\n");
        // }
        x86_pic_eoi(tf->trapno);
}
//