#ifndef __DRIVERS_VGA_TEXT_MODE_H__
#define __DRIVERS_VGA_TEXT_MODE_H__

#define MAX_ROW             25
#define MAX_COLUMN          80


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
    VGA_BLACK = 0,
    VGA_BLUE,
    VGA_GREEN,
    VGA_CYAN,
    VGA_RED,
    VGA_MAGENTA,
    VGA_BROWN,
    VGA_WHITE
} color_enum_t;


/*
 * Single character print functions
 */
extern void vga_print_char(char character, attribute_struct_t attribute_struct);
extern void vga_print_char_at(char character, int row, int column, attribute_struct_t attribute_struct);

/*
 * String print functions 
 */
extern void vga_print_string(const char *string, attribute_struct_t attribute_struct);
extern void vga_print_string_at(const unsigned char *string, int row, int column, attribute_struct_t attribute_struct);

/*
 * Screen functions
 */
extern void vga_clear_screen(void);

/*
 * Cursor functions
 */
extern void vga_set_cursor_position(int row, int column);
extern int vga_get_cursor_position_row(void);
extern int vga_get_cursor_position_column(void);

#endif
