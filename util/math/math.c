#include "math.h"

int pow(int base, unsigned int exponent)
{
    int i;
    int result = base;

    if(exponent == 0)
    {
        return 1;
    }

    for(i = 0; i < exponent; ++i)
    {
        result *= base;
    }

    return result;
}
