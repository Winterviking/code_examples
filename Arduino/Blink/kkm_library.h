//
//
// Экспериментальный код :: (НЕ ПРОДАКШН!!!!! )
// первые наброски
//



#ifndef __KKM_LIBRARY_H_INCLUDED__
#define __KKM_LIBRARY_H_INCLUDED__

#include <Arduino.h>

#define ENQ 0x05
#define STX 0x02
#define ACK 0x06
#define NAK 0x15


void print_string(const wchar_t* str);
void send_cmd( uint8_t* str, int len );

void print_progmem_string( int index_ );
void print_progmem_string_with_int( int index_, uint16_t param_ );
void print_progmem_string_with_string( int index_, wchar_t* param_ );

extern byte cutoff[7];


#endif // End of __KKM_LIBRARY_H_INCLUDED__


