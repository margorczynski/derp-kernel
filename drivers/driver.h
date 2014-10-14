#ifndef __DRIVERS_DRIVER_H__
#define __DRIVERS_DRIVER_H__

#include <stdbool.h>

#define MAX_DRIVER_NAME_LENGHT 255

typedef enum
{
    DRIVER_UNDEFINED,
    DRIVER_INPUT,
    DRIVER_OUTPUT
}driver_type_enum_t;


typedef struct
{
    char               driver_name[MAX_DRIVER_NAME_LENGHT];
    void               *driver_buffer_memory_area;
    driver_type_enum_t driver_type;
}driver_descriptor_struct_t;

bool driver_register(const driver_descriptor_struct_t *driver_description);

#endif
