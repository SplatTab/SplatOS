CC := clang -target x86_64-pc-none-elf
LD := ld.lld
ASM := nasm

CCFLAGS ?= -Ilibstl -Isys -Idrivers

override CFILES = *.c libstl/*.c sys/*.c drivers/*.c
override ASMFILES = sys/*.asm

override INTERNALCCFLAGS = -std=gnu17 -ffreestanding -fno-stack-protector -fno-omit-frame-pointer -fno-pic -mabi=sysv -mno-80387 -mno-mmx -mno-3dnow -mno-sse -mno-sse2 -mno-red-zone -mcmodel=kernel -I. -I../limine $(CFILES) -c
override ASMFLAGS = -felf64 $(ASMFILES)
override LDFLAGS = -T../linker.ld -nostdlib -zmax-page-size=0x1000 -static *.o $(ASMFILES:.asm=.o) -o kernel.elf
override CPFLAGS = kernel.elf limine.cfg limine/limine-cd.bin limine/limine-cd-efi.bin limine/limine.sys iso_root

.PHONY: all
all: kernel

kernel:
	$(CC) $(INTERNALCCFLAGS) $(CCFLAGS)
	$(ASM) $(ASMFLAGS)
	$(LD) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f *.o $(ASMFILES:.asm=.o) *.elf