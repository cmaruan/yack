PROJECT_ROOT ?= $(abspath $(dir ../))
ARCHDIR := $(PROJECT_ROOT)/arch/i386

include ../macros.mk
include ../include.mk
include $(ARCHDIR)/config.mk

LIBDIRS = \
mm \
io \
drivers \
hardware \

LINKFLAGS = $(addprefix -l,$(LIBDIRS))
LDFLAGS += $(patsubst %,-L$(CURDIR)/%/, $(LIBDIRS))
SUBDIRSCLEAN=$(addsuffix clean,$(LIBDIRS))

LIBS += -nostdlib -lgcc 

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
memop.o \
kmain.o \

OBJS=\
$(ARCHDIR)/asm/crti.o \
$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/asm/crtn.o \


LINK_LIST=\
$(LDFLAGS) \
$(ARCHDIR)/asm/crti.o \
$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(LIBS) \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/asm/crtn.o \

all: kernel.elf

export CFLAGS += $(KERNEL_ARCH_CFLAGS)
export CPPFLAGS += $(KERNEL_ARCH_CPPFLAGS)


$(LIBDIRS): 
	$(AT)echo "*** Building $@"
	$(AT)$(MAKE) -C $@

kernel.elf: $(LIBDIRS) $(OBJS) $(ARCHDIR)/linker.ld
	$(AT)echo "*** Building $@"
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST) $(LINKFLAGS)

$(ARCHDIR)/crtend.o $(ARCHDIR)/crtbegin.o:
	$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F) | xargs -I{} cp {} $@

clean: $(SUBDIRSCLEAN)
	$(RM) -rf *.a $(KERNEL_OBJS) kernel.elf $(ARCHDIR)/*.o

%clean: 
	$(AT)$(MAKE) -C $(subst clean,,$@) clean

.PHONY: $(LIBDIRS) kernel