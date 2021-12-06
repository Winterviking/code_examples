
#include "usb_utilities.h"
#include "drv_serial_port.h"
#include "bootloader_utils.h"
#include "drv_clock.h"
#include "drv_flash.h"
#include "drv_usb_main.h"
#include "sim.h"

bool usb_send   = false;
DWORD COUNT     = 0;

BYTE FW_BUF[256];
DWORD FW_ADDR;
WORD FW_PE_ADDR;
WORD FW_LEN;


DWORD arr_to_dword(BYTE *mas)
{
    return (((DWORD)mas[0]) << 24)
         | (((DWORD)mas[1]) << 16)
         | (((DWORD)mas[2]) << 8)
         | (((DWORD)mas[3]) << 0);
}

void dword_to_arr(BYTE *arr, DWORD d)
{
    arr[0] = (d >> 24) & 0xff;
    arr[1] = (d >> 16) & 0xff;
    arr[2] = (d >> 8)  & 0xff;
    arr[3] = (d >> 0)  & 0xff;
}

void usb_send_message(BYTE typemes, BYTE* arr, WORD simbuflen) {
    WAIT(20);

    if(!usb_send)
        return;

    while(!is_com_serial_tx_ready(&COM1));

    com_serial_tx_add_byte(&COM1,0);
    com_serial_tx_add_byte(&COM1,typemes);
    int_to_hex(TIMER(COUNT)); // checkout other func CNT_IntToStr
    com_serial_tx_add_array(&COM1, (BYTE*)convert_str,convert_strlen);
    com_serial_tx_add_byte(&COM1,':');
    com_serial_tx_add_byte(&COM1,' ');
    com_serial_tx_add_byte(&COM1,' ');
    com_serial_tx_add_array(&COM1, arr, simbuflen);

    com_serial_tx_start(&COM1);
}

void usb_send_param_confirm(BYTE param, BYTE* arr, WORD size){
    WAIT(20);

    if (!usb_send)
        return;

    while(!is_com_serial_tx_ready(&COM1));

    com_serial_tx_add_byte(&COM1, param);
    if (param == 0xF1)
        com_serial_tx_add_array(&COM1, arr, size);
    com_serial_tx_start(&COM1);
}

void usb_send_pc_off(){
    if (usb_send){
        while(!is_com_serial_tx_ready(&COM1));

        com_serial_tx_add_byte(&COM1, 255); // USB PC OFF
        com_serial_tx_start(&COM1);

        WAIT(500);

        drv_usb_disconnect();
        usb_send = false;
    }
}

void usb_param_config() {
    if (COM1.rx.dataready) {
        if (COM1.rx.buf.data[0] == 0xF0) { // FIRMWARE !!!!!
            if (COM1.rx.buf.data[1] == 0) { // MCU
                DWORD addr = arr_to_dword((BYTE*)&(COM1.rx.buf.data[2]));
                WORD len = (((WORD)COM1.rx.buf.data[6]) << 8) | COM1.rx.buf.data[7];

                for (BYTE i = 0; i < len; i++)
                    FW_BUF[(addr%page_size_flash) + i] = COM1.rx.buf.data[8 + i];

                if ((addr%page_size_flash) == (page_size_flash - len)) {
                    drv_flash_erase((addr / page_size_flash) * page_size_flash);
                    drv_flash_write((addr / page_size_flash) * page_size_flash, FW_BUF, page_size_flash);
                }

                usb_send_param_confirm(0xF0, 0, 0);
            }

            if(COM1.rx.buf.data[1] == 1) { // module
                DWORD addr = arr_to_dword((BYTE*)&(COM1.rx.buf.data[2]));
                WORD len = (((WORD)COM1.rx.buf.data[6]) << 8) | COM1.rx.buf.data[7];

                for (BYTE i = 0; i < len; i++)
                    FW_BUF[(addr%page_size_module) + i] = COM1.rx.buf.data[8 + i];

                if ((addr%page_size_module) == (page_size_module - len)) {
                    FW_PE_ADDR = addr / page_size_module;
                    FW_ADDR = (addr / page_size_module) * page_size_module + 0x08000000;
                    module_state = 0x44;

                    com_serial_tx_add_byte(&COM0, 0x44);
                    com_serial_tx_add_byte(&COM0, 0xBB);
                    com_serial_tx_start(&COM0);
                } else {
                    usb_send_param_confirm(0xF0, 0, 0);
                }
            }
        }
        if (COM1.rx.buf.data[0] == 0xF1) { // VERIFY
            if (COM1.rx.buf.data[1] == 0) { // MCU
                DWORD addr = arr_to_dword((BYTE*)&(COM1.rx.buf.data[2]));
                WORD len = (((WORD)COM1.rx.buf.data[6]) << 8) | COM1.rx.buf.data[7];

                drv_flash_read(addr, FW_BUF, len);
                usb_send_param_confirm(0xF1, FW_BUF, len);
            }
            if (COM1.rx.buf.data[1] == 0) { // MODULE
                FW_ADDR = arr_to_dword((BYTE*)&(COM1.rx.buf.data[2])) + 0x08000000;
                FW_LEN = (((WORD)COM1.rx.buf.data[6]) << 8) | COM1.rx.buf.data[7];
                module_state = 0x11;

                com_serial_tx_add_byte(&COM0, 0x11);
                com_serial_tx_add_byte(&COM0, 0xEE);
                com_serial_tx_start(&COM0);

            }
        }
        if (COM1.rx.buf.data[0] == 1) {
            if (COM1.rx.buf.data[1] == 1)
                mode = EBM_MODE_JUMP;

            if (COM1.rx.buf.data[1] == 2) {
                radio_reset(true);
                radio_boot(true);

                WAIT(100);

                radio_reset(false);

                WAIT(100);

                module_state = 0x7f;

                com_serial_clear(&COM0);
                com_serial_tx_clear(&COM0);
                com_serial_tx_add_byte(&COM0, 0x7f);
                com_serial_tx_start(&COM0);
            }
        }
        com_serial_rx_read_data(&COM1);
    }
}

void usb_connect_control() {
    if (drv_usb_detected()) {
        if(!usb_send) {
            usb_send = true;
            drv_usb_init();

            BYTE i = 0;
            for (i = 0; i < 20; i++){
                WAIT(50);
                WAIT(50);
            }
        }
    } else {
        if(usb_send){
            usb_send = false;
            drv_usb_disconnect();
        }
    }
}










