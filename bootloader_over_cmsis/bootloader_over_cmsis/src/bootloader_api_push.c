
#include "bootloader_api_push.h"

void bootloader_api_test_function(){

}

BOOTLOADER_FUNCTION_TABLE bootloader_api_table = {
{(DWORD)&bootloader_api_test_function}
};



