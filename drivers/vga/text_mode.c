#include "text_mode.h"

#include "../port_io/port_io.h"

#define VGA_VIDEO_MEMORY_ADDRESS 0xb8000

#define CONTROLLER_ADDRESS_REGISTER 0x3D4
#define CONTROLLER_DATA_REGISTER    0x3D5

static int _vga_get_video_memory_offset(int row, int column);
static unsigned char _vga_get_attribute_byte(attribute_struct_t attribute_struct);
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
 * If the row or column argument is less than zero or greater-equal than the maximum value
 * it will use the current cursor position instead
 *
 * @param character the character to be printed
 * @param row the row at which the character will be printed (see description)
 * @param column the column at which the character will be printed (see description)
 * @param attribute_struct the structure with the characters attribute
 */
void vga_print_char_at(char character, int row, int column, attribute_struct_t attribute_struct)
{
    const int current_cursor_row    = vga_get_cursor_position_row();
    const int current_cursor_column = vga_get_cursor_position_column();

    unsigned char *vga_video_memory = (unsigned char*) VGA_VIDEO_MEMORY_ADDRESS;
    int offset            = 0;
    int new_cursor_row    = row + column/MAX_COLUMN;
    int new_cursor_column = (column + 1) % MAX_COLUMN;


    if( row >= 0 && column >= 0 && row < MAX_ROW && column < MAX_COLUMN)
    {
        offset = _vga_get_video_memory_offset(row, column);
    }
    else
    {

        offset = _vga_get_video_memory_offset(current_cursor_row, current_cursor_column);

        new_cursor_row    = current_cursor_row + current_cursor_column/MAX_COLUMN;
        new_cursor_column = (current_cursor_column + 1) % MAX_COLUMN;
    }

    if(character == '\n')
    {
        offset = _vga_get_video_memory_offset(current_cursor_row, 79);

        new_cursor_row    = (current_cursor_row + 1) % MAX_ROW;
        new_cursor_column = 0;
    }

    vga_video_memory[offset]     = character;
    vga_video_memory[offset + 1] = _vga_get_attribute_byte(attribute_struct);

    //Move the cursor one position further (or newline if where at the end of the screen width)
    vga_set_cursor_position(new_cursor_row, new_cursor_column);
}

/*
 * String print functions
 */

/*
 * Print a string at the current cursor position
 *
 * @param string the constant pointer to the printed string (must be NULL-terminated)
 * @param attribute_structure the structure with the strings attribute
 */
void vga_print_string(const char *string, attribute_struct_t attribute_struct)
{
    vga_print_string_at(string, -1, -1, attribute_struct);
}

/*
 * Print a string at a specified position
 * If the row or column argument is less than zero or greater-equal than the maximum value
 * it will use the current cursor position instead
 *
 * @param string the constant pointer to the printed string (must be NULL-terminated)
 * @param row the row at which the string will be printed (see description)
 * @param column the column at which the string will be printed (see description)
 * @param attribute_struct the structure with the string attribute
 */
void vga_print_string_at(const unsigned char *string, int row, int column, attribute_struct_t attribute_struct)
{
    int i;

    if(row >= 0 || column >= 0)
    {
        vga_set_cursor_position(row, column);
    }

    for(i = 0; string[i] != '\0'; ++i)
    {
        vga_print_char_at(string[i], -1, -1, attribute_struct);
    }
}

/*
 * Screen functions
 */

/*
 * Clear the screen
 */
void vga_clear_screen(void)
{
    static const attribute_struct_t CLEARED_SCREEN_ATTRIBUTE_STRUCT = { VGA_WHITE, 0x1, VGA_BLACK, 0x0 };
    int i, j;

    for(i = 0; i < MAX_ROW; ++i)
    {
        for(j = 0; j < MAX_COLUMN; ++j)
        {
            vga_print_char_at(' ', i, j, CLEARED_SCREEN_ATTRIBUTE_STRUCT);
        }
    }

    vga_set_cursor_position(0, 0);
}

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
static inline int _vga_get_video_memory_offset(int row, int column)
{
    if(row < 0 || column < 0 || row >= MAX_ROW || column >= MAX_COLUMN)
    {
        return 0;
    }

    return (row * MAX_COLUMN + column) * 2;
}

/*
 * Translate the attribute structure to a single byte written in the video memory
 *
 * @return the attribute byte that represents the structure
 */
static inline unsigned char _vga_get_attribute_byte(attribute_struct_t attribute_struct)
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
static inline int _vga_get_cursor_position_offset(void)
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
