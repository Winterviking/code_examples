#ifndef __USB_UTILS_H_INCLUDED__
#define __USB_UTILS_H_INCLUDED__

#include "includer_hw.h"


extern bool usb_send;

void usb_send_message(BYTE typemes, BYTE* arr, WORD simbuflen);
void usb_send_param_confirm(BYTE param, BYTE* arr, WORD size);
void usb_send_pc_off();
void usb_param_config();
void usb_connect_control();



extern BYTE FW_BUF[256];
extern DWORD FW_ADDR;
extern WORD FW_PE_ADDR;
extern WORD FW_LEN;







#endif // End of __USB_UTILS_H_INCLUDED__
