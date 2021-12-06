#ifndef __DRV_FLASH_H_INCLUDED__
#define __DRV_FLASH_H_INCLUDED__

#include "includer_hw.h"





bool drv_flash_unlock();
bool drv_flash_lock();
bool drv_flash_erase(uint32_t page_addr);
bool drv_flash_write(DWORD addr, BYTE *buf, DWORD len);
bool drv_flash_read(DWORD addr, BYTE *buf, DWORD len);







#endif /* __DRV_FLASH_H_INCLUDED__ */
