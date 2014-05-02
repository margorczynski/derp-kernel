#ifndef __VGA_TEXT_MODE_H__
#define __VGA_TEXT_MODE_H__

#define MAX_ROWS             25
#define MAX_COLUMNS          80

#define CONTROLLER_ADDRESS_REGISTER 0x3D4
#define CONTROLLER_DATA_REGISTER    0x3D5

/*
 * Character attribute bitfield
 */
typedef struct
{
    unsigned char character_color  : 3;
    unsigned char intensity        : 1;
    unsigned char background_color : 3;
    unsigned char blinking         : 1
} attribute_struct_t;

/*
 *  Color enum
 */
typedef enum
{
    BLACK = 0,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    WHITE
} color_enum_t;


/*
 * Single character print functions
 */
extern void vga_print_char(char character, attribute_struct_t attribute_struct);
extern void vga_print_char_at(char character, int row, int column, attribute_struct_t attribute_struct);

/*
 * String print functions 
 */
extern void vga_print_string(char *string);
extern void vga_print_string_at(unsigned char *string, int row, int column);

/*
 * Screen functions
 */
extern void vga_clear_screen(void);

/*
 * Cursor functions
 */
extern void vga_set_cursor_position(int row, int column);
extern int vga_get_cursor_position(void);

#endif
