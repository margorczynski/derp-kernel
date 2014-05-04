#include "port_io.h"

/*
 * Read a byte from a specific port
 *
 * @param port the port number
 * 
 * @return the byte sent by the port
 */
unsigned char port_io_read_byte(unsigned short port)
{
    unsigned char data = 0;

    __asm__("in %%dx, %%al" : "=a" (data) : "d" (port));

    return data;
}

/*
 * Write a byte to a specific port
 *
 * @param port the port number
 * @param data the byte with the data to be written
 */
void port_io_write_byte(unsigned short port, unsigned char data)
{
    __asm__("out %%al, %%dx" : :"a" (data),  "d" (port));
}

/*
 * Read a word from a specific port
 *
 * @param port the port number
 * 
 * @return the word sent by the port
 */
unsigned short port_io_read_word(unsigned short port)
{
    unsigned char data = 0;

    __asm__("in %%dx, %%ax" : "=a" (data) : "d" (port));

    return data;
}

/*
 * Write a word to a specific port
 *
 * @param port the port number
 * @param data the word with the data to be written
 */
void port_io_write_word(unsigned short port, unsigned short data)
{
    __asm__("out %%ax, %%dx" : :"a" (data),  "d" (port));
}
