KERNEL_ROOT ?= $(PROJECT_ROOT)/kernel

CFLAGS   += -Wall -Wextra -Werror -O0 -g -fno-omit-frame-pointer \
	    -nostdlib -fno-builtin -fno-stack-protector \
	    -nostartfiles -nodefaultlibs \
	    
CPPFLAGS += -D__kernel
INCFLAGS += -I$(KERNEL_ROOT)/include -I$(PROJECT_ROOT)/utils/include


%.o: %.c
	$(CC) $(CFLAGS) $(INCFLAGS) $(CPPFLAGS) -Wno-builtin-declaration-mismatch -lgcc  -c -o $@ $<

%.o: %.S
	$(CC) $(KERNEL_ARCH_CFLAGS) $(KERNEL_ARCH_CPPFLAGS) -g -D__ASSEMBLY__ -fno-pic -nostdinc  -c -o $@ $<
