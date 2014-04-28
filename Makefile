#The derp-kernel Makefile used for building the kernel and bootloader

BOOTLOADER_SOURCES = boot/boot.asm \
		     print_string/print_string_real_mode.asm \
		     print_string/print_string_protected_mode.asm \
		     gdt/gdt.asm \
		     gdt/switch_to_protected_mode.asm

all: bootloader

bootloader: $(BOOTLOADER_SOURCES)
	    nasm boot/boot.asm -f bin -o boot/boot.bin
