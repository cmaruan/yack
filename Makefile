include macros.mk

all: kernel

kernel:
	$(MAKE) -C kernel

tools:
	$(MAKE) -C tools

clean:
	$(MAKE) -C kernel clean

qemu:
	qemu-system-i386 -kernel kernel/kernel.elf -D qemu.log -d int,cpu_reset -no-reboot -action shutdown=pause

.PHONY: tools kernel

