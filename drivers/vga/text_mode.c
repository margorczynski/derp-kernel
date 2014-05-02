#include "text_mode.h"

#define VGA_VIDEO_MEMORY_ADDRESS 0xb8000

static int _vga_get_video_memory_offset(int row, int column);
static char _vga_get_attribute_byte(attribute_struct_t attribute_struct);

/*
 * Single character print functions
 */

void vga_print_char(char character, attribute_struct_t attribute_struct)
{
    vga_print_char_at(character, -1, -1, attribute_struct);
}

void vga_print_char_at(char character, int row, int column, attribute_struct_t attribute_struct)
{
    unsigned char *vga_video_memory = (unsigned char*) VGA_VIDEO_MEMORY_ADDRESS;
    int offset = 0;

    if( row >= 0 && column >= 0 )
    {
        offset = _vga_get_video_memory_offset(row, column);
    }
    else
    {
        //offset = 2 * vga_get_cursor_position();
    }

    vga_video_memory[offset]     = character;
    vga_video_memory[offset + 1] = _vga_get_attribute_byte(attribute_struct);

    //vga_set_cursor_position(row, column);
}


static int _vga_get_video_memory_offset(int row, int column)
{
    return (row * 80 + column) * 2;
}

static char _vga_get_attribute_byte(attribute_struct_t attribute_struct)
{
    char attribute_byte = 0;

    attribute_byte |= attribute_struct.character_color  << 0;
    attribute_byte |= attribute_struct.intensity        << 3;
    attribute_byte |= attribute_struct.background_color << 4;
    attribute_byte |= attribute_struct.blinking         << 7;

    return attribute_byte;
}
