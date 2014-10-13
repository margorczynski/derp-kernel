#include "keyboard.h"

#include <stdint.h>
#include <stdbool.h>

#include "../port_io/port_io.h"

/*
 * The adress of the keyboard encoder port.
 * It can be read to get the encoder input buffer.
 * It can be written to send a command to the encoder.
 */
enum _KEYBOARD_ENCODER_PORTS_ENUM
{
    KEYBOARD_ENCODER_READ_INPUT_BUFFER_PORT = 0x60,
    KEYBOARD_ENCODER_SEND_COMMAND_PORT      = 0x60
};

/*
 * The adress of the keyboard onboard controller port.
 * It can be read to get the status register value.
 * It can be written to send a command to the controller.
 */
enum _KEYBOARD_CONTROLLER_PORTS_ENUM
{
    KEYBOARD_CONTROLLER_STATUS_REGISTER_PORT = 0x64,
    KEYBOARD_CONTROLLER_SEND_COMMAND_PORT    = 0x64
};

/*
 * Bit mask used for handling the status register status byte.
 */
enum _KEYBOARD_CONTROLLER_STATUS_REGISTER_MASK_ENUM
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

//TODO: Some of the keys are missing (with the double scan code?)
/*
 * The scan code set of the keyboard.
 */
enum _KEYBOARD_SCAN_CODE_SET
{
    ESC_PRESSED  = 0x01,
    ESC_RELEASED = ESC_PRESSED + 0x80,

    NUM_ONE_PRESSED  = 0x02,
    NUM_ONE_RELEASED = NUM_ONE_PRESSED + 0x80,

    NUM_TWO_PRESSED  = 0x03,
    NUM_TWO_RELEASED = NUM_TWO_PRESSED + 0x80,

    NUM_THREE_PRESSED  = 0x04,
    NUM_THREE_RELEASED = NUM_THREE_PRESSED + 0x80,

    NUM_FOUR_PRESSED  = 0x05,
    NUM_FOUR_RELEASED = NUM_FOUR_PRESSED + 0x80,

    NUM_FIVE_PRESSED  = 0x06,
    NUM_FIVE_RELEASED = NUM_FIVE_PRESSED + 0x80,

    NUM_SIX_PRESSED  = 0x07,
    NUM_SIX_RELEASED = NUM_SIX_PRESSED + 0x80,

    NUM_SEVEN_PRESSED  = 0x08,
    NUM_SEVEN_RELEASED = NUM_SEVEN_PRESSED + 0x80,

    NUM_EIGHT_PRESSED  = 0x09,
    NUM_EIGHT_RELEASED = NUM_EIGHT_PRESSED + 0x80,

    NUM_NINE_PRESSED  = 0x0A,
    NUM_NINE_RELEASED = NUM_NINE_PRESSED + 0x80,

    NUM_ZERO_PRESSED  = 0x0B,
    NUM_ZERO_RELEASED = NUM_ZERO_PRESSED + 0x80,

    MINUS_PRESSED  = 0x0C,
    MINUS_RELEASED = MINUS_PRESSED + 0x80,

    PLUS_PRESSED  = 0x0D,
    PLUS_RELEASED = PLUS_PRESSED + 0x80,

    BACKSPACE_PRESSED  = 0x0E,
    BACKSPACE_RELEASED = BACKSPACE_PRESSED + 0x80,

    TAB_PRESSED  = 0x0F,
    TAB_RELEASED = TAB_PRESSED + 0x80,

    Q_PRESSED  = 0x10,
    Q_RELEASED = Q_PRESSED + 0x80,
    
    W_PRESSED  = 0x11,
    W_RELEASED = W_PRESSED + 0x80,

    E_PRESSED  = 0x12,
    E_RELEASED = E_PRESSED + 0x80,

    R_PRESSED  = 0x13,
    R_RELEASED = R_PRESSED + 0x80,

    T_PRESSED  = 0x14,
    T_RELEASED = T_PRESSED + 0x80,

    Y_PRESSED  = 0x15,
    Y_RELEASED = Y_PRESSED + 0x80,

    U_PRESSED  = 0x16,
    U_RELEASED = U_PRESSED + 0x80,

    I_PRESSED  = 0x17,
    I_RELEASED = I_PRESSED + 0x80,

    O_PRESSED  = 0x18,
    O_RELEASED = O_PRESSED + 0x80,

    P_PRESSED  = 0x19,
    P_RELEASED = P_PRESSED + 0x80,

    LEFT_BRACKET_PRESSED  = 0x1A,
    LEFT_BRACKET_RELEASED = LEFT_BRACKET_PRESSED + 0x80,

    RIGHT_BRACKET_PRESSED  = 0x1B,
    RIGHT_BRACKET_RELEASED = RIGHT_BRACKET_PRESSED + 0x80,

    ENTER_PRESSED  = 0x1C,
    ENTER_RELEASED = ENTER_PRESSED + 0x80,

    LEFT_CTRL_PRESSED  = 0x1D,
    LEFT_CTRL_RELEASED = LEFT_CTRL_PRESSED + 0x80,

    A_PRESSED  = 0x1E,
    A_RELEASED = A_PRESSED + 0x80,

    S_PRESSED  = 0x1F,
    S_RELEASED = S_PRESSED + 0x80,

    D_PRESSED  = 0x20,
    D_RELEASED = D_PRESSED + 0x80,

    F_PRESSED  = 0x21,
    F_RELEASED = F_PRESSED + 0x80,

    G_PRESSED  = 0x22,
    G_RELEASED = G_PRESSED + 0x80,

    H_PRESSED  = 0x23,
    H_RELEASED = H_PRESSED + 0x80,

    J_PRESSED  = 0x24,
    J_RELEASED = J_PRESSED + 0x80,

    K_PRESSED  = 0x25,
    K_RELEASED = K_PRESSED + 0x80,

    L_PRESSED  = 0x26,
    L_RELEASED = L_PRESSED + 0x80,

    SEMICOLON_PRESSED  = 0x27,
    SEMICOLON_RELEASED = SEMICOLON_PRESSED + 0x80,

    SINGLE_QUOTE_PRESSED  = 0x28,
    SINGLE_QUOTE_RELEASED = SINGLE_QUOTE_PRESSED + 0x80,

    BACK_TICK_PRESSED  = 0x29,
    BACK_TICK_RELEASED = BACK_TICK_PRESSED + 0x80,

    LEFT_SHIFT_PRESSED  = 0x2A,
    LEFT_SHIFT_RELEASED = LEFT_SHIFT_PRESSED + 0x80,

    BACK_SLASH_PRESSED = 0x2B,
    BACK_SLASH_RELEASED = BACK_SLASH_PRESSED + 0x80,

    Z_PRESSED  = 0x2C,
    Z_RELEASED = Z_PRESSED + 0x80,

    X_PRESSED  = 0x2D,
    X_RELEASED = X_PRESSED + 0x80,

    C_PRESSED  = 0x2E,
    C_RELEASED = C_PRESSED + 0x80,

    V_PRESSED  = 0x2F,
    V_RELEASED = V_PRESSED + 0x80,

    B_PRESSED  = 0x30,
    B_RELEASED = B_PRESSED + 0x80,

    N_PRESSED  = 0x31,
    N_RELEASED = N_PRESSED + 0x80,

    M_PRESSED  = 0x32,
    M_RELEASED = M_PRESSED + 0x80,

    COMMA_PRESSED  = 0x33,
    COMMA_RELEASED = COMMA_PRESSED + 0x80,

    FULL_STOP_PRESSED  = 0x34,
    FULL_STOP_RELEASED = FULL_STOP_PRESSED + 0x80,

    SLASH_PRESSED  = 0x35,
    SLASH_RELEASED = SLASH_PRESSED + 0x80,

    RIGHT_SHIFT_PRESSED  = 0x36,
    RIGHT_SHIFT_RELEASED = RIGHT_SHIFT_PRESSED + 0x80,

    KEYPAD_MULTIPLY_PRESSED  = 0x37,
    KEYPAD_MULTIPLY_RELEASED = KEYPAD_MULTIPLY_PRESSED + 0x80,

    LEFT_ALT_PRESSED  = 0x38,
    LEFT_ALT_RELEASED = LEFT_ALT_PRESSED + 0x80,

    SPACE_BAR_PRESSED  = 0x39,
    SPACE_BAR_RELEASED = SPACE_BAR_PRESSED + 0x80,

    CAPS_LOCK_PRESSED  = 0x3A,
    CAPS_LOCK_RELEASED = CAPS_LOCK_PRESSED + 0x80,

    F1_PRESSED  = 0x3B,
    F1_RELEASED = F1_PRESSED + 0x80,

    F2_PRESSED  = 0x3C,
    F2_RELEASED = F2_PRESSED + 0x80,

    F3_PRESSED  = 0x3D,
    F3_RELEASED = F3_PRESSED + 0x80,

    F4_PRESSED  = 0x3E,
    F4_RELEASED = F4_PRESSED + 0x80,

    F5_PRESSED  = 0x3F,
    F5_RELEASED = F5_PRESSED + 0x80,

    F6_PRESSED  = 0x40,
    F6_RELEASED = F6_PRESSED + 0x80,

    F7_PRESSED  = 0x41,
    F7_RELEASED = F7_PRESSED + 0x80,

    F8_PRESSED  = 0x42,
    F8_RELEASED = F8_PRESSED + 0x80,

    F9_PRESSED  = 0x43,
    F9_RELEASED = F9_PRESSED + 0x80,

    F10_PRESSED = 0x44,
    F10_RELEASED = F10_PRESSED + 0x80,

    NUM_LOCK_PRESSED  = 0x45,
    NUM_LOCK_RELEASED = NUM_LOCK_PRESSED + 0x80,

    SCROLL_LOCK_PRESSED  = 0x46,
    SCROLL_LOCK_RELEASED = SCROLL_LOCK_PRESSED+ 0x80,

    KEYPAD_NUM_SEVEN_PRESSED  = 0x47,
    KEYPAD_NUM_SEVEN_RELEASED = KEYPAD_NUM_SEVEN_PRESSED + 0x80,

    KEYPAD_NUM_EIGHT_PRESSED  = 0x48,
    KEYPAD_NUM_EIGHT_RELEASED = KEYPAD_NUM_EIGHT_PRESSED + 0x80,

    KEYPAD_NUM_NINE_PRESSED  = 0x49,
    KEYPAD_NUM_NINE_RELEASED = KEYPAD_NUM_NINE_PRESSED + 0x80,

    KEYPAD_MINUS_PRESSED  = 0x4A,
    KEYPAD_MINUES_RELEASED = KEYPAD_MINUS_PRESSED + 0x80,

    KEYPAD_NUM_FOUR_PRESSED  = 0x4B,
    KEYPAD_NUM_FOUR_RELEASED = KEYPAD_NUM_FOUR_PRESSED + 0x80,

    KEYPAD_NUM_FIVE_PRESSED  = 0x4C,
    KEYPAD_NUM_FIVE_RELEASED = KEYPAD_NUM_FIVE_PRESSED + 0x80,

    KEYPAD_NUM_SIX_PRESSED  = 0x4D,
    KEYPAD_NUM_SIX_RELEASED = KEYPAD_NUM_SIX_PRESSED + 0x80,

    KEYPAD_PLUS_PRESSED  = 0x4E,
    KEYPAD_PLUS_RELEASED = KEYPAD_PLUS_PRESSED + 0x80,

    KEYPAD_NUM_ONE_PRESSED  = 0x4F,
    KEYPAD_NUM_ONE_RELEASED = KEYPAD_NUM_ONE_PRESSED + 0x80,

    KEYPAD_NUM_TWO_PRESSED  = 0x50,
    KEYPAD_NUM_TWO_RELEASED = KEYPAD_NUM_TWO_PRESSED + 0x80,

    KEYPAD_NUM_THREE_PRESSED  = 0x51,
    KEYPAD_NUM_THREE_RELEASED = KEYPAD_NUM_THREE_PRESSED + 0x80,

    KEYPAD_NUM_ZERO_PRESSED  = 0x52,
    KEYPAD_NUM_ZERO_RELEASED = KEYPAD_NUM_ZERO_PRESSED + 0x80,

    KEYPAD_FULL_STOP_PRESSED  = 0x53,
    KEYPAD_FULL_STOP_RELEASED = KEYPAD_FULL_STOP_PRESSED + 0x80,

    F11_PRESSED  = 0x57,
    F11_RELEASED = F11_PRESSED + 0x80,

    F12_PRESSED  = 0x58,
    F12_RELEASED = F12_PRESSED + 0x80,

    //The keys with the double scan codes are missing for now
};

static struct
{
    bool is_keyboard_enabled;

    //Lock key activation status
    bool is_scroll_lock_active;
    bool is_caps_lock_active;
    bool is_num_lock_active;

    //Modifier key status
    bool is_ctrl_pressed;
    bool is_shift_pressed;
    bool is_alt_pressed;

    char current_key_code;

}_keyboard_state_struct_s;


//Controller port functions
static uint8_t _keyboard_controller_read_status(void);
static void    _keyboard_controller_send_status(uint8_t command);
//Encoder port functions
static uint8_t _keyboard_encoder_read_input_buffer(void);
static void    _keyboard_encoder_send_status(uint8_t command);
//Change keyboard state functions
static void _keyboard_set_lock_key_state(uint8_t scan_code);
static void _keyboard_set_modifier_key_state(uint8_t scan_code);
//Change the current key code function
static void _keyboard_set_current_key_code(uint8_t scan_code);


/*
 * Callback function called by the keyboard ISR everytime a keyboard interrupt occurs.
 * This callback is placed in the keyboard ISR event handler table by the kernel when it loads the drivers.
 */
void keyboard_interrupt_event_handler(void)
{
    //TODO:Generate a proper key code and set the keyboard state if needed
    uint8_t scan_code;

    scan_code = port_io_read_byte(KEYBOARD_ENCODER_READ_INPUT_BUFFER_PORT);

    //Change the state if needed
    _keyboard_set_lock_key_state(scan_code);
    _keyboard_set_modifier_key_state(scan_code);
}

//TODO: Needs a function for initializing the driver?

/*
 * Reads the status byte from the keyboard controller.
 *
 * @return The status byte of the keyboard controller.
 */
static uint8_t _keyboard_controller_read_status(void)
{
    return port_io_read_byte(KEYBOARD_CONTROLLER_STATUS_REGISTER_PORT); 
}

/*
 * Sends a command to the keyboard controller.
 *
 * @param command The command byte that will be sent to the controller command port.
 */
static void _keyboard_controller_send_status(uint8_t command)
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
static uint8_t _keyboard_encoder_read_input_buffer(void)
{
    return port_io_read_byte(KEYBOARD_ENCODER_READ_INPUT_BUFFER_PORT); 
}

/*
 * Sends a command to the keyboard encoder.
 *
 * @param command The command byte that will be sent to the encoder command port.
 */
static void _keyboard_encoder_send_status(uint8_t command)
{
    while( (_keyboard_controller_read_status() & KEYBOARD_CONTROLLER_STATUS_REGISTER_MASK_INPUT_BUFFER) )
    {
        //Wait until the input buffer of the encoder is empty (the second bit is 0).
    }

    port_io_write_byte(KEYBOARD_ENCODER_SEND_COMMAND_PORT, command);
}

/*
 * Analyzes the scan code and changes the state of the lock keys if needed.
 *
 * @param scan_code The scan code byte received from the keyboard.
 */
static void _keyboard_set_lock_key_state(uint8_t scan_code)
{
    switch(scan_code)
    {
        case NUM_LOCK_PRESSED:
            _keyboard_state_struct_s.is_num_lock_active = !_keyboard_state_struct_s.is_num_lock_active;
        case CAPS_LOCK_PRESSED:
            _keyboard_state_struct_s.is_caps_lock_active = !_keyboard_state_struct_s.is_caps_lock_active;
        case SCROLL_LOCK_PRESSED:
            _keyboard_state_struct_s.is_scroll_lock_active = !_keyboard_state_struct_s.is_scroll_lock_active;
    }
}

/*
 * Analyzes the scan code and changes the state of the modifier keys if needed.
 *
 * @param scan_code The scan code byte received from the keyboard.
 */
static void _keyboard_set_modifier_key_state(uint8_t scan_code)
{
    switch(scan_code)
    {
        case LEFT_SHIFT_PRESSED:
            _keyboard_state_struct_s.is_shift_pressed = true;
        case RIGHT_SHIFT_PRESSED:
            _keyboard_state_struct_s.is_shift_pressed = true;
        case LEFT_ALT_PRESSED:
            _keyboard_state_struct_s.is_alt_pressed = true;
        case LEFT_CTRL_PRESSED:
            _keyboard_state_struct_s.is_ctrl_pressed = true;

        //TODO: This may fail when two of the same group are pressed at the same time but one is released after another
        case LEFT_SHIFT_RELEASED:
            _keyboard_state_struct_s.is_shift_pressed = false;
        case RIGHT_SHIFT_RELEASED:
            _keyboard_state_struct_s.is_shift_pressed = false;
        case LEFT_ALT_RELEASED:
            _keyboard_state_struct_s.is_alt_pressed = false;
        case LEFT_CTRL_RELEASED:
            _keyboard_state_struct_s.is_ctrl_pressed = false;
    }
}

/*
 * Analyzes the scan code and changes the current key code if needed.
 *
 * @param scan_code The scan code byte received from the keyboard.
 */
static void _keyboard_set_current_key_code(uint8_t scan_code)
{
    //TODO: Needs to be written
}
