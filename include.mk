KERNEL_ROOT ?= $(PROJECT_ROOT)/kernel

CFLAGS   += -Wall -Werror -O -fno-omit-frame-pointer
CPPFLAGS += -D__kernel
INCFLAGS += -I$(KERNEL_ROOT)/include -I$(PROJECT_ROOT)/utils/include


%.o: %.c
	$(CC) $(CFLAGS) $(INCFLAGS) $(CPPFLAGS) -nostdlib -nodefaultlibs -Wno-builtin-declaration-mismatch -lgcc  -c -o $@ $<

%.o: %.S
	$(CC) $(KERNEL_ARCH_CFLAGS) $(KERNEL_ARCH_CPPFLAGS) -D__ASSEMBLY__ -fno-pic -nostdinc  -c -o $@ $<
