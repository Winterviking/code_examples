

#ifndef __UART_H_INCLUDED__
#define __UART_H_INCLUDED__

#include <config.h>
#include <includer.h>
#include <printf.h>
#include <leds.h>

// driver interface

void procUART(void* data);

void initUART(MDR_UART_TypeDef* UARTx);

//void putc( void* ptr, char Data );

#endif // End of __UART_H_INCLUDED__

