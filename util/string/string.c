#include "string.h"

#include "../stdlib/stdlib.h"

size_t strlen(const char *string)
{
    int length = 0;

    while(string[length] != '\0') ++length;

    return length;
}

//TODO: Needs to be implemented
char* strcpy(char *destination, const char *source)
{
    int i;

    for(i = 0; source[i] != '\0'; ++i)
    {
        destination[i] = source[i];    
    }

    return destination;
}
