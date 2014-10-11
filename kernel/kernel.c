/*
 * The main source file containing the entry point (the function/symbol called by the bootloader) of the kernel
 */

#include "../drivers/vga/text_mode.h"
#include "gdt/gdt.h"
#include "idt/idt.h"
#include "isr/isr.h"

static const attribute_struct_t attribute_white_on_black = 
{
    .character_color  = VGA_WHITE,
    .intensity        = 1,
    .background_color = VGA_BLACK,
    .blinking         = 0
};

void kernel_main(void)
{
    vga_clear_screen();

    //Load the GDT
    gdt_create_flat_layout();
    gdt_load_global_descriptor_table();
        vga_print_string("GDT loading: OK\n", attribute_white_on_black);

    //Create the ISR's and load the IDT
    isr_create_exception_isrs();
    isr_create_interrupt_isrs();
    idt_load_interrupt_descriptor_table();
        vga_print_string("IDT loading: OK\n", attribute_white_on_black);

    vga_print_string("Hanging the CPU...\n", attribute_white_on_black);

    for(;;){}
}
