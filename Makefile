#The derp-kernel Makefile used for building the kernel and bootloader

BOOTLOADER_SOURCES = boot/boot.asm \
		     boot/print_string/print_string_real_mode.asm \
		     boot/print_string/print_string_protected_mode.asm \
		     boot/gdt/gdt.asm \
		     boot/gdt/switch_to_protected_mode.asm \
			 boot/disk_io/disk_read.asm

KERNEL_SOURCES = kernel/kernel.c


all: bootloader kernel image

bootloader: $(BOOTLOADER_SOURCES)
	    nasm boot/boot.asm -f bin -o boot/boot.bin

kernel_object: $(KERNEL_SOURCES)
		gcc -ffreestanding -c kernel/kernel.c -o kernel/kernel.o

kernel: kernel_object
		ld -o kernel/kernel.bin -Ttext 0x1000 kernel/kernel.o --oformat binary

image:	bootloader kernel 
		cat boot/boot.bin kernel/kernel.bin > image/os-image.img

test:	all
		qemu-kvm image/os-image.img

clean:
		rm boot/*.bin
		rm kernel/*.bin
		rm kernel/*o
		rm image/os-image.img
