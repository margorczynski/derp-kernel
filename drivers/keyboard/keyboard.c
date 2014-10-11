#include "keyboard.h"

#include <stdint.h>

#include "../port_io/port_io.h"

/*
 * The adress of the keyboard encoder port.
 * It can be read to get the encoder input buffer.
 * It can be written to send a command to the encoder.
 */
enum KEYBOARD_ENCODER_PORTS
{
    KEYBOARD_ENCODER_READ_INPUT_BUFFER_PORT = 0x60,
    KEYBOARD_ENCODER_SEND_COMMAND_PORT      = 0x60
};

/*
 * The adress of the keyboard onboard controller port.
 * It can be read to get the status register value.
 * It can be written to send a command to the controller.
 */
enum KEYBOARD_CONTROLLER_PORTS
{
    KEYBOARD_CONTROLLER_STATUS_REGISTER_PORT = 0x64,
    KEYBOARD_CONTROLLER_SEND_COMMAND_PORT    = 0x64
};

/*
 * Bit mask used for handling the status register status byte.
 */
enum _KEYBOARD_CONTROLLER_STATUS_REGISTER_MASK
{
    KEYBOARD_CONTROLLER_STATUS_REGISTER_MASK_OUTPUT_BUFFER         = 0x01,
    KEYBOARD_CONTROLLER_STATUS_REGISTER_MASK_INPUT_BUFFER          = 0x02,
    KEYBOARD_CONTROLLER_STATUS_REGISTER_MASK_SYSTEM_FLAG           = 0x04,
    KEYBOARD_CONTROLLER_STATUS_REGISTER_MASK_COMMAND_DATA          = 0x08,
    KEYBOARD_CONTROLLER_STATUS_REGISTER_MASK_KEYBOARD_LOCKED       = 0x10,
    KEYBOARD_CONTROLLER_STATUS_REGISTER_MASK_AUXILIARY_BUFFER_FULL = 0x20,
    KEYBOARD_CONTROLLER_STATUS_REGISTER_MASK_TIMEOUT               = 0x40,
    KEYBOARD_CONTROLLER_STATUS_REGISTER_MASK_PARITY_ERROR          = 0x80
};


//Controller port functions
uint8_t _keyboard_controller_read_status(void);
void    _keyboard_controller_send_status(uint8_t command);
//Encoder port functions
uint8_t _keyboard_encoder_read_input_buffer(void);
void    _keyboard_encoder_send_status(uint8_t command);


/*
 * Callback function called by the keyboard ISR everytime a keyboard interrupt occurs.
 * This callback is placed in the keyboard ISR event handler table by the kernel when it loads the drivers.
 */
void keyboard_interrupt_event_handler(void)
{
    //TODO:Handle the event using the encoder/controller ports
}

/*
 * Reads the status byte from the keyboard controller.
 *
 * @return The status byte of the keyboard controller.
 */
uint8_t _keyboard_controller_read_status(void)
{
    return port_io_read_byte(KEYBOARD_CONTROLLER_STATUS_REGISTER_PORT); 
}

/*
 * Sends a command to the keyboard controller.
 *
 * @param command The command byte that will be sent to the controller command port.
 */
void _keyboard_controller_send_status(uint8_t command)
{
    while( (_keyboard_controller_read_status() & KEYBOARD_CONTROLLER_STATUS_REGISTER_MASK_INPUT_BUFFER) )
    {
        //Wait until the input buffer of the controller is empty (the second bit is 0).
    }

    port_io_write_byte(KEYBOARD_CONTROLLER_SEND_COMMAND_PORT, command);
}

/*
 * Reads a byte from the keyboard encoder input buffer.
 *
 * @return A byte from the keyboard encoder input buffer.
 */
uint8_t _keyboard_encoder_read_input_buffer(void)
{
    return port_io_read_byte(KEYBOARD_ENCODER_READ_INPUT_BUFFER_PORT); 
}

/*
 * Sends a command to the keyboard encoder.
 *
 * @param command The command byte that will be sent to the encoder command port.
 */
void _keyboard_encoder_send_status(uint8_t command)
{
    while( (_keyboard_controller_read_status() & KEYBOARD_CONTROLLER_STATUS_REGISTER_MASK_INPUT_BUFFER) )
    {
        //Wait until the input buffer of the encoder is empty (the second bit is 0).
    }

    port_io_write_byte(KEYBOARD_ENCODER_SEND_COMMAND_PORT, command);
}
