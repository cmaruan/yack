KERNEL_ARCH_CFLAGS +=
KERNEL_ARCH_CPPFLAGS += -I$(ARCHDIR)/include 
KERNEL_ARCH_LDFLAGS += 
KERNEL_ARCH_LIBS +=

KERNEL_ARCH_OBJS=\
$(subst .c,.o,$(wildcard $(ARCHDIR)/*.c)) \
$(ARCHDIR)/asm/entry.o \



