ifndef TOOLPREFIX
$(error TOOLPREFIX must be defined)
endif

_CC = $(TOOLPREFIX)gcc
_AS = $(TOOLPREFIX)gas
_AR = $(TOOLPREFIX)ar
_LD = $(TOOLPREFIX)ld
_OBJCOPY = $(TOOLPREFIX)objcopy
_OBJDUMP = $(TOOLPREFIX)objdump
_RM = rm
AT=@

ifndef VERBOSE
	export CC= $(AT)echo      "[CC]      $@"; $(_CC) 
	export AS= $(AT)echo      "[AS]      $@"; $(_AS) 
	export AR= $(AT)echo      "[AR]      $@"; $(_AR) 
	export LD= $(AT)echo      "[LD]      $@"; $(_LD) 
	export RM= $(AT)echo      "[RM]      $@"; $(_RM)
	export OBJCOPY= $(AT)echo "[OBJCOPY] $@"; $(_OBJCOPY) 
	export OBJDUMP= $(AT)echo "[OBJDUMP] $@"; $(_OBJDUMP)
else
	export CC=$(_CC)
	export AS=$(_AS)
	export AR=$(_AR)
	export LD=$(_LD)
	export RM=$(_RM)
	export OBJCOPY=$(_OBJCOPY)
	export OBJDUMP=$(_OBJDUMP)
endif