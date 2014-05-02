/*
 * The main source file containing the entry point (the function/symbol called by the bootloader) of the kernel
 */

#include "../drivers/vga/text_mode.h"

void kernel_main(void)
{
    attribute_struct_t attribute_struct;

    attribute_struct.character_color  = 0x7;
    attribute_struct.intensity        = 0x1;
    attribute_struct.background_color = 0x0;
    attribute_struct.blinking         = 0x0;

    vga_print_char_at('X', 0, 0, attribute_struct);
    vga_print_char_at('X', 1, 0, attribute_struct);
    vga_print_char_at('X', 2, 0, attribute_struct);
    vga_print_char_at('X', 0, 3, attribute_struct);
    vga_print_char_at('X', 0, 5, attribute_struct);
}
