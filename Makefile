#The derp-kernel Makefile used for building the kernel and bootloader

BOOTLOADER_SOURCES = boot/bootloader.asm \
		     boot/print_string/print_string_real_mode.asm \
		     boot/print_string/print_string_protected_mode.asm \
		     boot/gdt/gdt.asm \
		     boot/gdt/switch_to_protected_mode.asm \
			 boot/disk_io/disk_read.asm

KERNEL_ASSEMBLY = $(wildcard kernel/idt/*.asm kernel/gdt/*.asm)
KERNEL_SOURCES  = $(wildcard kernel/*.c kernel/idt/*.c kernel/gdt/*.c kernel/isr/*.c kernel/isr/exceptions/*.c kernel/isr/interrupts/*.c)
KERNEL_HEADERS  = $(wildcard kernel/*.h kernel/idt/*.h kernel/gdt/*.h kernel/isr/*.h kernel/isr/exceptions/*.h kernel/isr/interrupts/*.h)

DRIVERS_SOURCES = $(wildcard drivers/*.c drivers/*/*.c)
DRIVERS_HEADERS = $(wildcard drivers/*.h drivers/*/*.h)

UTIL_SOURCES = $(wildcard util/*/*.c)
UTIL_HEADERS = $(wildcard util/*/*.h)

KERNEL_OBJECTS          = ${KERNEL_SOURCES:.c=.o}
KERNEL_ASSEMBLY_OBJECTS = $(KERNEL_ASSEMBLY:.asm=.o)
DRIVERS_OBJECTS         = ${DRIVERS_SOURCES:.c=.o}
UTIL_OBJECTS            = ${UTIL_SOURCES:.c=.o}


all: image

kernel/kernel.bin: kernel/kernel_entry.o ${KERNEL_OBJECTS} ${KERNEL_ASSEMBLY_OBJECTS} ${DRIVERS_OBJECTS} ${UTIL_OBJECTS}
		ld -o $@ -m elf_i386 -Ttext 0x1000 $^ --oformat binary

%.o : %.c ${KERNEL_HEADERS} ${DRIVERS_HEADERS}
		clang -m32 -ffreestanding -c $< -o $@

%.o : %.asm 
		nasm $< -f elf -o $@

%.bin : %.asm
		nasm $< -f bin -o $@

image:	boot/bootloader.bin kernel/kernel.bin 
		mkdir image
		cat $^ > image/os-image.img
		dd if=/dev/zero bs=1 count=1000000 >> image/os-image.img

test:	all
		qemu-kvm image/os-image.img

clean:
		rm -fr boot/*.bin
		rm -fr kernel/*.bin
		rm -fr kernel/*.o
		rm -fr kernel/idt/*.o
		rm -fr kernel/gdt/*.o
		rm -fr drivers/vga/*.o
		rm -fr drivers/port_io/*.o
		rm -fr image/os-image.img
		rm -fr util/math/*.o
		rm -fr util/stdlib/*.o
		rm -fr util/string/*.o
