#include "string.h"

#include "../stdlib/stdlib.h"

size_t strlen(const char *string)
{
    int length = 0;

    if(!string)
    {
     	return 0;
    }

    while(string[length] != '\0') ++length;

    return length;
}

//TODO: Needs to be implemented
char* strcpy(char *destination, const char *source)
{
    return NULL;
}
