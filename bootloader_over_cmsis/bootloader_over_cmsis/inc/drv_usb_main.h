#ifndef __DRV_USB_MAIN_H_INCLUDED__
#define __DRV_USB_MAIN_H_INCLUDED__

#include "includer_hw.h"


void drv_usb_disconnect(void);

void drv_usb_detect_init();
void drv_usb_detect_deinit();
bool drv_usb_detected();
void drv_usb_init(void);




#endif /* __DRV_USB_MAIN_H_INCLUDED__ */
