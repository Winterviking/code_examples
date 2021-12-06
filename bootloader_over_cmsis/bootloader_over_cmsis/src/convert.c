
#include "convert.h"

// буфер преобразования
char convert_str[12];
BYTE convert_strlen = 0;

char* get_convert_string(void)
{
    return(convert_str);
}

static inline void swap(char* one, char* another) {
    char tmp = *one;
    *one = *another;
    *another = tmp;
}

/* A utility function to reverse a string  */
static inline void reverse(char* str, int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end)
    {
        swap((str + start), (str + end));
        start++;
        end--;
    }
}


#define _itoa2__ _itoa2_(_int16, signed short)
#include "itoa_core.h"
#undef _itoa2__

#define _itoa2__ _itoa2_(_int32, signed int)
#include "itoa_core.h"
#undef _itoa2__

#define _itoa2__ _itoa2_(_uint32, unsigned int)
#include "itoa_core.h"
#undef _itoa2__











