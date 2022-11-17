ifndef TOOLPREFIX
export TOOLPREFIX=i686-elf-
$(info [INFO]    using $$TOOLPREFIX as ${TOOLPREFIX})
endif

_CC = $(TOOLPREFIX)gcc
_AS = $(TOOLPREFIX)gas
_AR = $(TOOLPREFIX)ar
_LD = $(TOOLPREFIX)ld
_OBJCOPY = $(TOOLPREFIX)objcopy
_OBJDUMP = $(TOOLPREFIX)objdump
_RM = rm
_MAKE := $(MAKE)
AT=@

LIBNAME = 

ifndef VERBOSE
	export CC= $(AT)echo      "[CC]      $(shell basename $@)"; $(_CC) 
	export AS= $(AT)echo      "[AS]      $(shell basename $@)"; $(_AS) 
	export AR= $(AT)echo      "[AR]      $(shell basename $@)"; $(_AR) 
	export LD= $(AT)echo      "[LD]      $(shell basename $@)"; $(_LD) 
	export RM= $(AT)echo      "[RM]      $(shell basename $@)"; $(_RM)
	export OBJCOPY= $(AT)echo "[OBJCOPY] $(shell basename $@)"; $(_OBJCOPY) 
	export OBJDUMP= $(AT)echo "[OBJDUMP] $(shell basename $@)"; $(_OBJDUMP)
else
	export CC=$(_CC)
	export AS=$(_AS)
	export AR=$(_AR)
	export LD=$(_LD)
	export RM=$(_RM)
	export OBJCOPY=$(_OBJCOPY)
	export OBJDUMP=$(_OBJDUMP)
endif