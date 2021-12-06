
#include "drv_flash.h"



bool drv_flash_unlock()
{
    while ((FLASH->SR & FLASH_SR_BSY) != 0) {
        // timeout management missing
    }

    if ((FLASH->PECR & FLASH_PECR_PELOCK) != 0) {
        FLASH->PEKEYR = FLASH_PEKEY1;
        FLASH->PEKEYR = FLASH_PEKEY2;
    }

    if ((FLASH->PECR & FLASH_PECR_PRGLOCK) != 0) {
        FLASH->PRGKEYR = FLASH_PRGKEY1;
        FLASH->PRGKEYR = FLASH_PRGKEY2;
    }

    return true;
}

bool drv_flash_lock()
{
    while ((FLASH->SR & FLASH_SR_BSY) != 0) {
        // timeout management missing
    }

    FLASH->PECR |= FLASH_PECR_PELOCK;
    FLASH->PECR |= FLASH_PECR_PRGLOCK;

    return true;
}

bool drv_flash_erase(uint32_t page_addr)
{

//(1) Set the ERASE and PROG bits in the FLASH_PECR register to enable page erasing
//(2) Write a 32-bit word value in an address of the selected page to start the erase sequence
//(3) Wait until the BSY bit is reset in the FLASH_SR register
//(4) Check the EOP flag in the FLASH_SR register
//(5) Clear EOP flag by software by writing EOP at 1
//(6) Reset the ERASE and PROG bits in the FLASH_PECR register to disable the page erase

    if(!drv_flash_unlock())
        return false;

    FLASH->PECR |= FLASH_PECR_ERASE | FLASH_PECR_PROG;
    *(__IO uint32_t *)(FLASH_BASEPROG_START_ADDR + page_addr) = (uint32_t)0;

    while ((FLASH->SR & FLASH_SR_BSY) != 0)
    {
        // timeout management missing
    }

    if ((FLASH->SR & FLASH_SR_EOP) != 0) /* (4) */
    {
        FLASH->SR = FLASH_SR_EOP; /* (5) */
    } else {
        // error management
    }

    FLASH->PECR &= ~(FLASH_PECR_ERASE | FLASH_PECR_PROG); /* (6) */

    if(!drv_flash_lock())
        return false;

    return true;
}

bool drv_flash_write(DWORD addr, BYTE *buf, DWORD len)
{
    if(!drv_flash_unlock())
        return false;

    FLASH->SR |= FLASH_SR_WRPERR;
    FLASH->PECR |= FLASH_PECR_DATA;//FLASH_PECR_ERASE|FLASH_PECR_DATA;

    BYTE len4 = len % 4;

    if(len4)
        for(BYTE i = len4; i < 4; i++)
            buf[len++] = 0;

    for(DWORD i = 0;i < len;i += 4) {
        while ((FLASH->SR & FLASH_SR_BSY) != 0) {
        //timeout management missing
        }

        FLASH->SR |= FLASH_SR_EOP;
        DWORD d = (((DWORD)buf[i + 3]) << 24) |
                (((DWORD)buf[i + 2]) << 16) |
                (((DWORD)buf[i + 1]) << 8) |
                (((DWORD)buf[i + 0]) << 0);

        *(DWORD*)(FLASH_BASEPROG_START_ADDR + addr + i) = d;

        while((FLASH->SR & FLASH_SR_EOP) == 0);
    }

    if(!drv_flash_lock())
        return false;
    /*
    FLASH->PECR |= FLASH_PECR_ERASE | FLASH_PECR_DATA;
    FLASH->SR|=FLASH_SR_EOP;
    *(__IO uint32_t *)addr = (uint32_t)0;
    while((FLASH->SR & FLASH_SR_EOP) != 0);
    FLASH->PECR &= ~(FLASH_PECR_ERASE | FLASH_PECR_DATA);
    */
    return true;
}

bool drv_flash_read(DWORD addr, BYTE *buf, DWORD len)
{
  for(DWORD i = 0; i < len; i++) {
    buf[i] = *(BYTE*)(FLASH_BASEPROG_START_ADDR + addr + i);
  }
  return true;
}












