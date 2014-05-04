#include "text_mode.h"

#include "../port_io/port_io.h"

#define VGA_VIDEO_MEMORY_ADDRESS 0xb8000

#define CONTROLLER_ADDRESS_REGISTER 0x3D4
#define CONTROLLER_DATA_REGISTER    0x3D5

static int _vga_get_video_memory_offset(int row, int column);
static char _vga_get_attribute_byte(attribute_struct_t attribute_struct);
static int _vga_get_cursor_position_offset(void);


/*
 * Single character print functions
 */

/*
 * Print a single character at the current cursor position
 *
 * @param character the character to be printed
 * @param attribute_struct the structure with the characters attribute
 */
void vga_print_char(char character, attribute_struct_t attribute_struct)
{
    vga_print_char_at(character, -1, -1, attribute_struct);
}

/*
 * Print a single character at a specified position
 * If the row or column argument is less than zero or greater than the maximum value
 * it will use the current cursor position instead
 *
 * @param character the character to be printed
 * @param row the row at which the character should be printed (see description)
 * @param column the column at which the character should be printed (see description)
 * @param attribute_struct the structure with the characters attribute
 */
void vga_print_char_at(char character, int row, int column, attribute_struct_t attribute_struct)
{
    unsigned char *vga_video_memory = (unsigned char*) VGA_VIDEO_MEMORY_ADDRESS;
    int offset = 0;

    if( row >= 0 && column >= 0 && row < MAX_ROW && column < MAX_COLUMN)
    {
        offset = _vga_get_video_memory_offset(row, column);
    }
    else
    {
        offset = _vga_get_video_memory_offset( vga_get_cursor_position_row(), vga_get_cursor_position_column() );
    }

    vga_video_memory[offset]     = character;
    vga_video_memory[offset + 1] = _vga_get_attribute_byte(attribute_struct);

    vga_set_cursor_position(row, column);
}

/*
 * String print functions
 */

/*
 * Screen functions
 */

/*
 * Cursor functions
 */

/*
 * Set the cursor at the specified position
 *
 * @param row the row of the cursors new position (0 <= row < MAX_ROW)
 * @param column the column of the cursors new position (0 <= column < MAX_COLUMN)
 */
void vga_set_cursor_position(int row, int column)
{
    const short CURSOR_POSITION_HIGH_BYTE_REGISTER = 14;
    const short CURSOR_POSITION_LOW_BYTE_REGISTER  = 15;
    const int VIDEO_MEMORY_CURSOR_CHAR_OFFSET      = _vga_get_video_memory_offset(row, column) / 2;

    if(row < 0 || column < 0 || row > MAX_ROW || column > MAX_COLUMN)
    {
        return;
    }

    //Write the high-byte of the cursors offset to the register
    port_io_write_byte(CONTROLLER_ADDRESS_REGISTER, CURSOR_POSITION_HIGH_BYTE_REGISTER);
    port_io_write_byte(CONTROLLER_DATA_REGISTER, (unsigned char) (VIDEO_MEMORY_CURSOR_CHAR_OFFSET >> 8));

    //Write the low-byte of the cursors offset to the register
    port_io_write_byte(CONTROLLER_ADDRESS_REGISTER, CURSOR_POSITION_LOW_BYTE_REGISTER);
    port_io_write_byte(CONTROLLER_DATA_REGISTER, (unsigned char) VIDEO_MEMORY_CURSOR_CHAR_OFFSET);
}

/*
 * Get the row of the current cursor position
 *
 * @return the row of the cursor position
 */
int vga_get_cursor_position_row(void)
{
    return (_vga_get_cursor_position_offset() / 2) / MAX_COLUMN;
}

/*
 * Get the column of the current cursor position
 *
 * @return the column of the cursor position
 */
int vga_get_cursor_position_column(void)
{
    return ((_vga_get_cursor_position_offset() / 2) - (vga_get_cursor_position_row() * MAX_COLUMN));
}


/*
 * Translate a position on the screen (described as the row and column)
 * into an offset in the video memory area
 *
 * @param row the row of the position
 * @param column the column of the position
 *
 * @return the offset in the video memory of the position
 */
static int _vga_get_video_memory_offset(int row, int column)
{
    return (row * MAX_COLUMN + column) * 2;
}

/*
 * Translate the attribute structure to a single byte written in memory
 *
 * @return the attribute byte that represents the structure
 */
static char _vga_get_attribute_byte(attribute_struct_t attribute_struct)
{
    char attribute_byte = 0;

    attribute_byte |= attribute_struct.character_color  << 0;
    attribute_byte |= attribute_struct.intensity        << 3;
    attribute_byte |= attribute_struct.background_color << 4;
    attribute_byte |= attribute_struct.blinking         << 7;

    return attribute_byte;
}

/*
 * Returns the video memory offset of the current cursor position
 *
 * @return the cursor offset (in the video memory)
 */
static int _vga_get_cursor_position_offset(void)
{
    const short CURSOR_POSITION_HIGH_BYTE_REGISTER = 14;
    const short CURSOR_POSITION_LOW_BYTE_REGISTER  = 15;

    int offset = 0;

    
    //Read the high-byte of the cursors offset to the register
    port_io_write_byte(CONTROLLER_ADDRESS_REGISTER, CURSOR_POSITION_HIGH_BYTE_REGISTER);
    offset = port_io_read_byte(CONTROLLER_DATA_REGISTER) << 8;

    //Read the low-byte of the cursors offset to the register
    port_io_write_byte(CONTROLLER_ADDRESS_REGISTER, CURSOR_POSITION_LOW_BYTE_REGISTER);
    offset += port_io_read_byte(CONTROLLER_DATA_REGISTER);

    return offset * 2;
}
