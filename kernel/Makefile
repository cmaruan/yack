PROJECT_ROOT ?= $(abspath $(dir ../))
ARCHDIR := $(PROJECT_ROOT)/arch/i386

include ../macros.mk
include ../include.mk
include $(ARCHDIR)/config.mk

LIBDIRS = \
mm \
io \

LINKFLAGS = $(addprefix -l,$(LIBDIRS))
LDFLAGS += $(patsubst %,-L$(CURDIR)/%/, $(LIBDIRS))
SUBDIRSCLEAN=$(addsuffix clean,$(LIBDIRS))

LIBS += -nostdlib -lgcc 

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
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

all: kernel

export CFLAGS += $(KERNEL_ARCH_CFLAGS)
export CPPFLAGS += $(KERNEL_ARCH_CPPFLAGS)


$(LIBDIRS): 
	$(MAKE) -C $@

kernel: $(LIBDIRS) $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST) $(LINKFLAGS)

$(ARCHDIR)/crtend.o $(ARCHDIR)/crtbegin.o:
	$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F) | xargs -I{} cp {} $@

clean: $(SUBDIRSCLEAN)
	$(RM) -rf *.a $(KERNEL_OBJS) kernel $(ARCHDIR)/*.o

%clean: 
	$(MAKE) -C $(subst clean,,$@) clean

.PHONY: $(LIBDIRS) kernel