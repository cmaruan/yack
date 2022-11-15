#include "drivers/serial.h"
#include "kernel.h"
#include "memlayout.h"
#include "mm/vm.h"

void
do_shutdown()
{
        klog(INFO, "Shutting down...\n");
        outw(0x604, 0x2000);
}



void
kmain()
{
        // The assertion below ensures that we are loaded in
        // the higher virtual memory
        cli();
        kassert((void *)kmain > (void *)MM_KERNEL_LINK);
        serial_init_port(X86_SERIAL_COM1_BASE);
        serial_set_default_port(X86_SERIAL_COM1_BASE);
        trap_init();
        kvm_init();
        segments_init();
        klog(DEBUG, "Calling STI\n");
        sti();
        
        int *ptr = (int *)0xffffffff;
        *ptr = 45;

        klog(DEBUG, "Trap counter: %u\n", trap_counter);
        klog(DEBUG, "Last trapno: %u\n", last_trapno);
        do_shutdown();
}
