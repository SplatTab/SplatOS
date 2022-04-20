ISONAME = SplatOS.iso
HDDNAME := $(ISONAME:.iso=.hdd)

.PHONY: all
all: $(ISONAME)

.PHONY: all-hdd
all-hdd: $(HDDNAME)

.PHONY: run
run: $(ISONAME)
	qemu-system-x86_64 -M q35 -m 2G -cdrom $(ISONAME) -boot d

.PHONY: run-uefi
run-uefi: ovmf-x64 $(ISONAME)
	qemu-system-x86_64 -M q35 -m 2G -bios ovmf-x64/OVMF.fd -cdrom $(ISONAME) -boot d

.PHONY: run-hdd
run-hdd: $(HDDNAME)
	qemu-system-x86_64 -M q35 -m 2G -hda $(HDDNAME)

.PHONY: run-hdd-uefi
run-hdd-uefi: ovmf-x64 $(HDDNAME)
	qemu-system-x86_64 -M q35 -m 2G -bios ovmf-x64/OVMF.fd -hda $(HDDNAME)

ovmf-x64:
	mkdir -p ovmf-x64
	cd ovmf-x64 && curl -o OVMF-X64.zip https://efi.akeo.ie/OVMF/OVMF-X64.zip && 7z x OVMF-X64.zip

limine:
	git clone https://github.com/limine-bootloader/limine.git --branch=v3.0-branch-binary --depth=1
	make -C limine

.PHONY: kernel
kernel:
	$(MAKE) -C kernel

$(ISONAME): limine kernel
	rm -rf iso_root
	mkdir -p iso_root
	cp kernel/SplatKernel.elf \
		limine.cfg limine/limine.sys limine/limine-cd.bin limine/limine-cd-efi.bin iso_root/
	xorriso -as mkisofs -b limine-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot limine-cd-efi.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		iso_root -o $(ISONAME)
	limine/limine-deploy $(ISONAME)
	rm -rf iso_root

$(HDDNAME): limine kernel
	rm -f $(HDDNAME)
	dd if=/dev/zero bs=1M count=0 seek=64 of=$(HDDNAME)
	parted -s $(HDDNAME) mklabel gpt
	parted -s $(HDDNAME) mkpart ESP fat32 2048s 100%
	parted -s $(HDDNAME) set 1 esp on
	limine/limine-deploy $(HDDNAME)
	sudo losetup -Pf --show $(HDDNAME) >loopback_dev
	sudo mkfs.fat -F 32 `cat loopback_dev`p1
	mkdir -p img_mount
	sudo mount `cat loopback_dev`p1 img_mount
	sudo mkdir -p img_mount/EFI/BOOT
	sudo cp -v kernel/SplatKernel.elf limine.cfg limine/limine.sys img_mount/
	sudo cp -v limine/BOOTX64.EFI img_mount/EFI/BOOT/
	sync
	sudo umount img_mount
	sudo losetup -d `cat loopback_dev`
	rm -rf loopback_dev img_mount

.PHONY: clean
clean:
	rm -rf iso_root $(ISONAME) $(HDDNAME)
	$(MAKE) -C kernel clean

.PHONY: distclean
distclean: clean
	rm -rf limine ovmf-x64
	$(MAKE) -C kernel distclean
