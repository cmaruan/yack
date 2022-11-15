include macros.mk

all: kernel

kernel:
	$(MAKE) -C kernel

tools:
	$(MAKE) -C tools

clean:
	$(MAKE) -C kernel clean

.PHONY: tools kernel