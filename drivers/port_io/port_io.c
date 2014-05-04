#include "port_io.h"

/*
 * Read/Write byte 
 */
unsigned char port_io_read_byte(unsigned short port)
{
    unsigned char data = 0;

    __asm__("in %%dx, %%al" : "=a" (data) : "d" (port));

    return data;
}

void port_io_write_byte(unsigned short port, unsigned char data)
{
    __asm__("out %%al, %%dx" : :"a" (data),  "d" (port));
}

/*
 * Read/Write word
 */
unsigned short port_io_read_word(unsigned short port)
{
    unsigned char data = 0;

    __asm__("in %%dx, %%ax" : "=a" (data) : "d" (port));

    return data;
}

void port_io_write_word(unsigned short port, unsigned short data)
{
    __asm__("out %%ax, %%dx" : :"a" (data),  "d" (port));
}
