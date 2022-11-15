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
        uint16_t th_base_low;
        uint16_t th_segment;
        uint8_t th_reserved;
        uint8_t th_flags;
        uint16_t th_base_high;
} __attribute__((__packed__));

extern uint32_t trap_handler_array[];
struct trap_handler trap_table[256];

void
x86_set_idt_gate(int interrupt, void* base, uint16_t seg_desc, uint8_t flags)
{
        trap_table[interrupt].th_base_low = ((uint32_t)base) & 0xFFFF;
        trap_table[interrupt].th_segment = seg_desc;
        trap_table[interrupt].th_reserved = 0;
        trap_table[interrupt].th_flags = flags;
        trap_table[interrupt].th_base_high = ((uint32_t)base >> 16) & 0xFFFF;
}

void
trap_init()
{
        for (int i = 0; i < 256; i++) {
                void* trap_addr = (void*)trap_handler_array[i];
                int flags =
                    IDT_FLAG_RING0 | IDT_FLAG_PRESENT | IDT_FLAG_GATE_32BIT_INT;
                x86_set_idt_gate(i, trap_addr, 0x8, flags);
        }
        klog(DEBUG, "sizeof struct trap_handler: %u\n",
             sizeof(struct trap_handler));
        x86_lidt(trap_table, sizeof trap_table);
        klog(DEBUG, "using idt trap_table at %p\n", trap_table);
}

void
trap_handler(struct trapframe* tf)
{
        (void)tf;
        trap_counter++;
        last_trapno = tf->trapno;
        klog(TRAP, "tf->trapno 0x%0x\n", tf->trapno);
        for (;;);
}
// 