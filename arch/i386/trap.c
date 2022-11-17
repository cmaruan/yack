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

#define KEY_Fn(n)        0
#define KEY_LSHIFT       0
#define KEY_RSHIFT       0
#define KEY_HOME         0
#define KEY_ARROW_UP     0
#define KEY_PGUP         0
#define KEY_ARROW_LEFT   0
#define KEY_ARROW_CENTER 0
#define KEY_ARROW_RIGHT  0
#define KEY_END          0
#define KEY_ARROW_DOWN   0
#define KEY_PGDOWN       0
#define KEY_INS          0
#define KEY_DEL          0
#define KEY_CAPSLOCK     0
#define KEY_ALT          0
#define KEY_CTRL         0
#define KEY_ESC          0

int keyboard_scan_codes[256] = {
    [1] = KEY_ESC,
    [2] = '1',
    [3] = '2',
    [4] = '3',
    [5] = '4',
    [6] = '5',
    [7] = '6',
    [8] = '7',
    [9] = '8',
    [10] = '9',
    [11] = '0',
    [12] = '-',
    [13] = '=',
    [14] = '\b',
    [15] = '\t',
    [16] = 'Q',
    [17] = 'W',
    [18] = 'E',
    [19] = 'R',
    [20] = 'T',
    [21] = 'Y',
    [22] = 'U',
    [23] = 'I',
    [24] = 'O',
    [25] = 'P',
    [26] = '[',
    [27] = ']',
    [28] = '\n',
    [29] = KEY_CTRL,
    [30] = 'A',
    [31] = 'S',
    [32] = 'D',
    [33] = 'F',
    [34] = 'G',
    [35] = 'H',
    [36] = 'J',
    [37] = 'K',
    [38] = 'L',
    [39] = ';',
    [40] = '\'',
    [41] = '`',
    [42] = KEY_LSHIFT,
    [43] = '\\',
    [44] = 'Z',
    [45] = 'X',
    [46] = 'C',
    [47] = 'V',
    [48] = 'B',
    [49] = 'N',
    [50] = 'M',
    [51] = ',',
    [52] = '.',
    [53] = '/',
    [54] = KEY_RSHIFT,
    // [55] = 	'PrtSc',
    [56] = KEY_ALT,
    [57] = ' ',
    [58] = KEY_CAPSLOCK,
    [59] = KEY_Fn(1),
    [60] = KEY_Fn(2),
    [61] = KEY_Fn(3),
    [62] = KEY_Fn(4),
    [63] = KEY_Fn(5),
    [64] = KEY_Fn(6),
    [65] = KEY_Fn(7),
    [66] = KEY_Fn(8),
    [67] = KEY_Fn(9),
    [68] = KEY_Fn(10),
    // [69] = 	'Num',
    // [70] = 	'Scroll',
    [71] = KEY_HOME,
    [72] = KEY_ARROW_UP,
    [73] = KEY_PGUP,
    [74] = '-',
    [75] = KEY_ARROW_LEFT,
    // [76] = 	KEY_ARROW_CENTER, // ??
    [77] = KEY_ARROW_RIGHT,
    [78] = '+',
    [79] = KEY_END,
    [80] = KEY_ARROW_DOWN,
    [81] = KEY_PGDOWN,
    [82] = KEY_INS,
    [83] = KEY_DEL,
};

void
keyboard_handler(struct trapframe* tf)
{
        (void)tf;
        u8 byte = inb(0x60);
        if (keyboard_scan_codes[byte]) {
                klog(TRAP, "Letter: %c\n", keyboard_scan_codes[byte]);
        }
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
                klog(TRAP, "trapcounter: 0x%0x    trapno: %x\n", trap_counter,
                     tf->trapno);
        if (trap_callback_table[tf->trapno]) {
                trap_callback_table[tf->trapno](tf);
        }
        // else {
        //         klog(TRAP, "No handler available\n");
        // }
        x86_pic_eoi(tf->trapno);
}
//