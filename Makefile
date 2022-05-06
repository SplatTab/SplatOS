override CPFLAGS = kernel/kernel.elf limine.cfg limine/limine-cd.bin limine/limine-cd-efi.bin limine/limine.sys iso_root
override XORRISOFLAGS = -as mkisofs -b limine-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table --efi-boot limine-cd-efi.bin -efi-boot-part --efi-boot-image --protective-msdos-label iso_root -o SplatOS.iso

.PHONY: all
all: iso

iso:
	mkdir -p iso_root
	$(MAKE) -C kernel
	cp $(CPFLAGS)
	xorriso $(XORRISOFLAGS)
	rm -rf iso_root
	./limine/limine-deploy.exe

qemu:
	qemu-system-x86_64.exe -boot d -cdrom ./SplatOS.iso -m 512 -smp cpus=2

.PHONY: clean
clean:
	rm -f *.iso
	rm -rf iso_root
	$(MAKE) -C kernel clean