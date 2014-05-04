#ifndef __DRIVERS_PORT_IO_H__
#define __DRIVERS_PORT_IO_H__

/*
 * Read/Write byte from/to specified port
 */
inline unsigned char port_io_read_byte(unsigned short port);
inline void          port_io_write_byte(unsigned short port, unsigned char data);

/*
 * Read/Write word from/to specified port
 */
inline unsigned short port_io_read_word(unsigned short port);
inline void           port_io_write_word(unsigned short port, unsigned short word);

#endif
