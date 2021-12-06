#ifndef __BOOTLOADER_UTILS_H_INCLUDED__
#define __BOOTLOADER_UTILS_H_INCLUDED__

#include "includer_hw.h"

typedef enum {
    EBM_MODE_JUMP = 0,
    EBM_MODE_BOOT = 1,
    EBM_MODE_MODULE = 2
} E_BOOTLOADER_MODE;


extern BYTE module_state;
extern E_BOOTLOADER_MODE mode;




// NVIC vector table trick
void move_vector_table();

void bootloader_mode_handler();

void JumpToApplication(DWORD ApplicationAddress);


#endif // End of __BOOTLOADER_UTILS_H_INCLUDED__
