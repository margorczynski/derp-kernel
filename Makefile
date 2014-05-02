#The derp-kernel Makefile used for building the kernel and bootloader

BOOTLOADER_SOURCES = boot/boot.asm \
		     boot/print_string/print_string_real_mode.asm \
		     boot/print_string/print_string_protected_mode.asm \
		     boot/gdt/gdt.asm \
		     boot/gdt/switch_to_protected_mode.asm \
			 boot/disk_io/disk_read.asm

KERNEL_SOURCES = kernel/kernel.c \
				 kernel/kernel_entry.asm

DRIVERS_SOURCES = drivers/vga/text_mode.c 


all: bootloader drivers kernel image

bootloader: $(BOOTLOADER_SOURCES)
	    nasm boot/boot.asm -f bin -o boot/boot.bin

kernel_entry: $(KERNEL_SOURCES)
		nasm kernel/kernel_entry.asm -f elf -o kernel/kernel_entry.o

kernel_object: $(KERNEL_SOURCES)
		gcc -m32 -ffreestanding -c kernel/kernel.c -o kernel/kernel.o

kernel: kernel_object kernel_entry
		ld -o kernel/kernel.bin -m elf_i386 -Ttext 0x1000 kernel/kernel_entry.o drivers/vga/text_mode.o kernel/kernel.o --oformat binary

drivers: $(DRIVERS_SOURCES)
		gcc -m32 -ffreestanding -c drivers/vga/text_mode.c -o drivers/vga/text_mode.o

image:	bootloader kernel 
		cat boot/boot.bin kernel/kernel.bin > image/os-image.img
		dd if=/dev/zero bs=1 count=1000000 >> image/os-image.img

test:	all
		qemu-kvm image/os-image.img

clean:
		rm boot/*.bin
		rm kernel/*.bin
		rm kernel/*o
		rm image/os-image.img
