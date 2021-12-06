/*
The formats supported by this implementation are: 'd' 'u' 'c' 's' 'x' 'X'.

To use the printf you need to supply your own character output function,
something like :

void putc ( void* p, char c)
        {
        while (!SERIAL_PORT_EMPTY) ;
        SERIAL_PORT_TX_REGISTER = c;
        }

Before you can call printf you need to initialize it to use your
character output function with something like:

init_printf(NULL,putc);
*/

// Check these functions, correct its style and code :3 bcause we need some open source

#ifndef __TFP_PRINTF__
#define __TFP_PRINTF__

#include <stdarg.h>

void init_printf(void* putp,void (*putf) (void*,char));

void tfp_printf(char *fmt, ...);
void tfp_sprintf(char* s,char *fmt, ...);

void tfp_format(void* putp,void (*putf) (void*,char),char *fmt, va_list va);

#define printf tfp_printf
#define sprintf tfp_sprintf

#endif





