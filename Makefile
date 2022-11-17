include macros.mk

all: kernel

kernel:
	$(AT)$(MAKE) -C kernel

tools:
	$(AT)$(MAKE) -C tools

clean:
	$(AT)$(MAKE) -C kernel clean

qemu:
	qemu-system-i386 -kernel kernel/kernel.elf -D qemu.log -d int,cpu_reset -no-reboot -action shutdown=pause

.PHONY: tools kernel

