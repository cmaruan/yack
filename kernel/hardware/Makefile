PROJECT_ROOT ?= $(abspath $(dir ../../))

include ../../include.mk
include ../../macros.mk

LIBNAME = $(shell basename $(CURDIR))
SOURCES = $(wildcard *.c)
OBJECTS = $(subst .c,.o,$(SOURCES))
TARGET = lib$(LIBNAME).a

all: $(TARGET)

.depends:
	$(CC) $(INCFLAGS) $(CPPFLAGS) -MM $(SOURCES) >> .depends

$(TARGET): .depends $(OBJECTS)
	$(AR) rcs $@ $(OBJECTS)

clean:
	$(RM) -rf *.o *.a .depends

-include .depends