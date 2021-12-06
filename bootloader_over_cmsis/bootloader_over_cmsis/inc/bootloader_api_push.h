#ifndef __BOOTLOADER_API_PUSH_H_INCLUDED__
#define __BOOTLOADER_API_PUSH_H_INCLUDED__

#include "includer.h"



typedef struct {
    DWORD _functions_[MAX_BOOTLOADER_API_FUNCTION_NUMBER];
} BOOTLOADER_FUNCTION_TABLE;

extern BOOTLOADER_FUNCTION_TABLE bootloader_api_table;




#endif /* __BOOTLOADER_API_PUSH_H_INCLUDED__ */
