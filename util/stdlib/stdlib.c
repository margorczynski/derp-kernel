#include "stdlib.h"

#include "../math/math.h"

char* itoa(int value, char* destination)
{
    const char digit_ascii_table[] = "0123456789";

    int destination_index        = 0;
    unsigned int value_char_size = 0;

    int absolute_value = value;

    int current_digit  = 0;
    int previous_leading_number = 0;


    if(!destination)
    {
        return NULL;
    }

    if(value < 0) 
    {
        destination[destination_index] = '-';
        absolute_value *= (-1);

        ++destination_index;
    }

    while(absolute_value / pow(10, value_char_size) > 0)
    {
        ++value_char_size;
    }

    while(value_char_size > 0)
    {
        int current_leading_number = absolute_value/pow(10, value_char_size - 1);

        current_digit = current_leading_number - (previous_leading_number * 10);
        destination[destination_index] = digit_ascii_table[current_digit];

        previous_leading_number = current_leading_number;
        ++destination_index;
        --value_char_size;
    }

    destination[destination_index] = '\0';

    return destination;
}
