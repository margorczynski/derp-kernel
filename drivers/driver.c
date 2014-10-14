#include "driver.h"

#include "../util/string/string.h"

#define MAX_NUMBER_OF_REGISTERED_DRIVERS 255

/*
 * This array holds all the descriptors of the drivers registered in the kernel.
 * TODO: This may be later changed to a dynamic list?
 */
static driver_descriptor_struct_t driver_descriptor_array[MAX_NUMBER_OF_REGISTERED_DRIVERS];

/*
 * Registers a driver in the kernel.
 * It takes the address of the descriptor created by the driver 
 * and copies it into the descriptor array.
 *
 * @param driver_description Reference to the descriptor created by the driver.
 *
 * @return If registering the driver succeded.
 */
bool driver_register(const driver_descriptor_struct_t *driver_descriptor)
{
    static int current_driver_descriptor_array_index = 0;

    driver_descriptor_struct_t *current_driver_descriptor = &driver_descriptor_array[current_driver_descriptor_array_index];

    //The supplied memory address of the descriptor is NULL
    if(!driver_descriptor)
    {
        return false;
    }

    //The max number of registered drivers has been reached
    if(current_driver_descriptor_array_index >= 255)
    {
        return false;
    }

    //TODO: Should also return false if it's an empty string and maybe if a driver with the same name is already registered?
    /*
    if(!driver_descriptor->driver_name)
    {
        return false;
    }
    */

    //The address of the driver buffer memory is NULL
    if(!driver_descriptor->driver_buffer_memory_area)
    {
        return false;
    } 

    //Copy the name into the string and assign the buffer address and type fields
    strcpy(current_driver_descriptor->driver_name, driver_descriptor->driver_name);
    current_driver_descriptor->driver_buffer_memory_area = driver_descriptor->driver_buffer_memory_area;
    current_driver_descriptor->driver_type               = driver_descriptor->driver_type;

    ++current_driver_descriptor_array_index;

    return true;
}
