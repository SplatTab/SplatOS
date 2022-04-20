#___Kernel File___
override KERNEL := SplatKernel.elf

#___Compiler Executable___
ifeq ($(origin CC), default)
CC := gcc
endif

#___Linker Executable___
ifeq ($(origin LD), default)
LD := ld
endif

#___Add C Flags here___
CFLAGS ?= -O2 -g -Ilibstl/ -Wall -Wextra -Wpedantic -pipe

#___Add Linker Flags Here___
LDFLAGS ?=

#!!NOTE!! Do Not Touch!!#
#___Important C Flags___
override INTERNALCFLAGS :=   \
	-I.                  \
	-std=c11             \
	-ffreestanding       \
	-fno-stack-protector \
	-fno-stack-check     \
	-fno-pic             \
	-mabi=sysv           \
	-mno-80387           \
	-mno-mmx             \
	-mno-3dnow           \
	-mno-sse             \
	-mno-sse2            \
	-mno-red-zone        \
	-mcmodel=kernel      \
	-MMD

#___Important Linker Flags___
override INTERNALLDFLAGS :=    \
	-Tlinker.ld            \
	-nostdlib              \
	-zmax-page-size=0x1000 \
	-static

#___Source/Objs/Dep Files___
override CFILES := $(shell find ./ -type f -name '*.c')
override OBJ := $(CFILES:.c=.o)
override HEADER_DEPS := $(CFILES:.c=.d)

#___Default target___
.PHONY: all
all: $(KERNEL)

#___Get Limine Header___
limine.h:
	curl https://raw.githubusercontent.com/limine-bootloader/limine/trunk/limine.h -o $@

#___Kernel Linking___
$(KERNEL): $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) $(INTERNALLDFLAGS) -o $@

#___Object Compilation___
%.o: %.c
	$(CC) $(CFLAGS) $(INTERNALCFLAGS) -I. -c $< -o $@

%.o: %.asm
	nasm -felf32 $< -o $@

#___Cleanup___
.PHONY: clean
clean:
	rm -rf $(KERNEL) $(OBJ) $(HEADER_DEPS)

.PHONY: distclean
distclean: clean
	rm -f limine.h
