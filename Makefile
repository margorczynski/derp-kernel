#The derp-kernel Makefile used for building the kernel and bootloader

BOOTLOADER_SOURCES = boot/boot.asm \
		     boot/print_string/print_string_real_mode.asm \
		     boot/print_string/print_string_protected_mode.asm \
		     boot/gdt/gdt.asm \
		     boot/gdt/switch_to_protected_mode.asm \
			 boot/disk_io/disk_read.asm


all: bootloader

bootloader: $(BOOTLOADER_SOURCES)
	    nasm boot/boot.asm -f bin -o boot/boot.bin
