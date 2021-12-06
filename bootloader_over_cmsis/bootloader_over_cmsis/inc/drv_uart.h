#ifndef __DRV_UART_H_INCLUDED__
#define __DRV_UART_H_INCLUDED__

#include "includer_hw.h"
#include "drv_serial_port.h"





void drv_uart_init(bool parity);
void drv_uart_deinit();

BYTE x;

void com_serial_generate_tx(volatile com_serial_port_def* port);
void uart_send(BYTE x);












#endif /* __DRV_UART_H_INCLUDED__ */
