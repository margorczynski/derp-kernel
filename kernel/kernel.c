/*
 * The main source file containing the entry point (the function/symbol called by the bootloader) of the kernel
 */

#include <stdbool.h>

#include "../drivers/vga/text_mode.h"
#include "gdt/gdt.h"
#include "idt/idt.h"

__attribute__((naked)) void interrupt(void)
{
    asm ("pusha");


    attribute_struct_t attribute_struct;
    attribute_struct.character_color  = 0x7;
    attribute_struct.intensity        = 0x1;
    attribute_struct.background_color = 0x0;
    attribute_struct.blinking         = 0x0;
    vga_clear_screen();
    vga_print_string_at("Interrupt, IRQ 0", 1, 1, attribute_struct);
    for(;;) {}
     
    asm ("popa");
    asm ("iret");
}

void kernel_main(void)
{
    gdt_create_flat_layout();
    gdt_load_global_descriptor_table();

    idt_create_interrupt_service_routine(0, interrupt, RING_0);

    idt_load_interrupt_descriptor_table();

    attribute_struct_t attribute_struct;
    attribute_struct.character_color  = 0x7;
    attribute_struct.intensity        = 0x1;
    attribute_struct.background_color = 0x0;
    attribute_struct.blinking         = 0x0;

    vga_clear_screen();
    vga_print_string_at("Test", 1, 1, attribute_struct);
    vga_print_char('\n', attribute_struct);
    vga_print_string("JADRA", attribute_struct);
    //
    int b = 0;
    int a = 15/b;
    
    for(;;){}
}
