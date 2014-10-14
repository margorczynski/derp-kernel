#ifndef __DRIVERS_KEYBOARD_H__
#define __DRIVERS_KEYBOARD_H__

#include <stdbool.h>

bool keyboard_intitialize(void);
void keyboard_interrupt_event_handler(void);

#endif
