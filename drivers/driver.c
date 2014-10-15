#include "driver.h"

#include "../util/string/string.h"

#define MAX_NUMBER_OF_REGISTERED_DRIVERS 255

/*
 * This array holds all the addresses of the descriptors of the drivers registered in the kernel.
 * TODO: This may be later changed to a dynamic list?
 */
static driver_descriptor_struct_t *driver_descriptor_address_array[MAX_NUMBER_OF_REGISTERED_DRIVERS];

/*
 * Registers a driver in the kernel.
 * It takes the address of the descriptor created by the driver 
 * and copies it (the address) into the descriptor address array.
 *
 * @param driver_description Address of the descriptor created by the driver.
 *
 * @return If registering the driver succeded.
 */
bool driver_register(driver_descriptor_struct_t *driver_descriptor_address)
{
    static int current_driver_descriptor_address_array_index = 0;

    //The supplied memory address of the descriptor is NULL
    if(!driver_descriptor_address)
    {
        return false;
    }

    //The max number of registered drivers has been reached
    if(current_driver_descriptor_address_array_index >= 255)
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
    if(!driver_descriptor_address->driver_buffer_memory_address)
    {
        return false;
    } 

    driver_descriptor_address_array[current_driver_descriptor_address_array_index] = driver_descriptor_address;

    ++current_driver_descriptor_address_array_index;

    return true;
}
