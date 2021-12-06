
#include "bootloader_utils.h"
#include "includer_hw.h"
#include "bootloader_api_push.h"
#include "usb_utilities.h"
#include "drv_serial_port.h"

BYTE module_state       = 0;
BYTE c;
WORD fw_count           = 0;
BYTE test               = 0;
E_BOOTLOADER_MODE mode  = EBM_MODE_JUMP;



void move_vector_table(){
  for(WORD i = 0; i < vectorTableSize; i++)
      *(BYTE*)(0x20000000 + i) = *(BYTE*)(0x8000000 + i);//копируем
  SCB->VTOR = 0x20000000; //устанавливаем указатель на таблицу для ядра

  //*(DWORD*)(0x20000000+vectorTableSize-4)=(DWORD)&GetAddress;//по заданному адресу (в конце таблицы векторов) устанавливаем адрес функции GetAddress

  *(DWORD*)(0x20000000 + vectorTableSize - 4) = (DWORD)&bootloader_api_table;//по заданному адресу (в конце таблицы векторов) устанавливаем адрес функции GetAddress

}






void bootloader_mode_handler(){
    while(get_sim_data(&c))
    {
        switch(module_state) {
            case 0x7f: {
                if(c == 0x79) {
                    mode = EBM_MODE_MODULE;
                    usb_send_message(0, (BYTE*)"The module loading mode is ready!", 33);
                    //uart_deinit();
                    //uart_init(true);
                } else {
                    module_state = 0;
                    usb_send_message(0, (BYTE*)"The module loading mode is error!", 33);
                }
                break;
            }
            case 0x11: {
                if(c == 0x79) {
                    BYTE fw_addr[4];
                    fw_addr[0] = (FW_ADDR >> 24)  & 0xff;
                    fw_addr[1] = (FW_ADDR >> 16)  & 0xff;
                    fw_addr[2] = (FW_ADDR >> 8)   & 0xff;
                    fw_addr[3] = (FW_ADDR >> 0)   & 0xff;

                    //fw_addr[3]=(FW_ADDR>>9)&0xff;
                    //usb_send_message(3,(BYTE*)"ACK",3);

                    com_serial_tx_add_array(&COM0, fw_addr, 4);
                    com_serial_tx_add_byte(&COM0, fw_addr[0]^fw_addr[1]^fw_addr[2]^fw_addr[3]);

                    com_serial_tx_start(&COM0);

                    module_state = 0x12;
                    //usb_send_message(0,(BYTE*)"Send ADDR",9);
                }

                if(c == 0x1F) {
                    //usb_send_message(1,(BYTE*)"NACK",4);
                    module_state = 0;
                }
                break;
            }
            case 0x12: {
                if(c == 0x79) {
                    //usb_send_message(3,(BYTE*)"ACK",3);
                    com_serial_tx_add_byte(&COM0, FW_LEN - 1);
                    com_serial_tx_add_byte(&COM0, (FW_LEN - 1) ^ 0xFF);

                    com_serial_tx_start(&COM0);

                    module_state = 0x13;
                    //usb_send_message(0,(BYTE*)"Send LEN",8);
                }

                if(c == 0x1F) {
                    //usb_send_message(1,(BYTE*)"NACK",4);
                    module_state=0;
                }
                break;
            }
            case 0x13: {
                if(c == 0x79) {
                    //usb_send_message(3,(BYTE*)"ACK",3);
                    //clear sim buffer prob;
                    module_state = 0x14;
                    fw_count = 0;
                }

                if(c == 0x1F) {
                    //USB_SendMessage(1,(BYTE*)"NACK",4);
                    module_state = 0;
                }
                break;
            }
            case 0x14: {
                FW_BUF[fw_count] = c;
                if(++fw_count >= FW_LEN) {
                    //usb_send_message(0,(BYTE*)"Data recieved",13);
                    usb_send_param_confirm(0xf1, FW_BUF, FW_LEN);
                    module_state = 0;

                    if(++test >= 3) {
                        test=0;
                        fw_count=0;
                    }
                }
                break;
            }

            case 0x44: {
                if(c == 0x79) {
                    //usb_send_message(3,(BYTE*)"ACK",3);
                    BYTE pn[2];

                    // magic numbers ....
                    pn[0]=((FW_ADDR/256) >> 8) & 0xff;
                    pn[1]=((FW_ADDR/256) >> 0) & 0xff;

                    com_serial_tx_add_byte(&COM0, 0);
                    com_serial_tx_add_byte(&COM0, 0);
                    com_serial_tx_add_byte(&COM0, pn[0]);
                    com_serial_tx_add_byte(&COM0, pn[1]);
                    com_serial_tx_add_byte(&COM0, 0 ^ 0 ^ pn[0] ^ pn[1]);

                    com_serial_tx_start(&COM0);
                    module_state = 0x45;
                    //usb_send_message(0,(BYTE*)"Send PAGE_NUM",13);
                }
                if(c == 0x1F) {
                    //usb_send_message(1,(BYTE*)"NACK",4);
                    module_state = 0;
                }
                break;
            }
            case 0x45: {
                if(c == 0x79) {
                    //usb_send_message(3,(BYTE*)"ACK",3);

                    module_state = 0x31;

                    //WAIT(1000);
                    //usb_send_message(0,(BYTE*)"Send 0x31",9);

                    com_serial_tx_add_byte(&COM0, 0x31);
                    com_serial_tx_add_byte(&COM0, 0xCE);

                    com_serial_tx_start(&COM0);
                }
                if(c == 0x1F) {
                    //usb_send_message(1,(BYTE*)"NACK",4);
                    module_state = 0;
                }
                break;
            }

            case 0x31: {
                if(c == 0x79) {
                    BYTE fw_addr[4];

                    fw_addr[0]=(FW_ADDR >> 24)  & 0xff;
                    fw_addr[1]=(FW_ADDR >> 16)  & 0xff;
                    fw_addr[2]=(FW_ADDR >> 8)   & 0xff;
                    fw_addr[3]=(FW_ADDR >> 0)   & 0xff;

                    //usb_send_message(3,(BYTE*)"ACK",3);

                    com_serial_tx_add_array(&COM0, fw_addr, 4);
                    com_serial_tx_add_byte(&COM0, fw_addr[0] ^ fw_addr[1] ^ fw_addr[2] ^ fw_addr[3]);

                    com_serial_tx_start(&COM0);

                    module_state = 0x32;

                    //usb_send_message(0,(BYTE*)"Send ADDR",9);
                }

                if(c == 0x1F) {
                    //usb_send_message(1,(BYTE*)"NACK",4);
                    module_state = 0;
                }
                break;
            }
            case 0x32: {
                if(c == 0x79) {
                    //usb_send_message(3,(BYTE*)"ACK",3);

                    module_state = 0x33;

                    com_serial_tx_add_byte(&COM0, 0xff);

                    BYTE xorbyte = 0xff;

                    for(WORD i = 0; i < 256; i++)
                    {
                        com_serial_tx_add_byte(&COM0, FW_BUF[i]);
                        xorbyte ^= FW_BUF[i];
                    }

                    com_serial_tx_add_byte(&COM0, xorbyte);

                    com_serial_tx_start(&COM0);

                    //usb_send_message(0,(BYTE*)"Send DATA",9);

                }
                if(c == 0x1F) {
                    //usb_send_message(1,(BYTE*)"NACK",4);
                    module_state = 0;
                }
                break;
            }
            case 0x33: {
                if(c == 0x79) {
                    //usb_send_message(3,(BYTE*)"ACK",3);

                    usb_send_param_confirm(0xf0, 0, 0);

                    module_state = 0;
                }

                if(c == 0x1F) {
                    //usb_send_message(1,(BYTE*)"NACK",4);

                    module_state = 0;
                }
                break;
            }
        }
    }
}



















void NVIC_Disable()
{
  HAL_NVIC_DisableIRQ(SysTick_IRQn);
  HAL_NVIC_DisableIRQ((IRQn_Type) USB_IRQn);
}

// передать управление прошивке
void JumpToApplication(DWORD ApplicationAddress)
{
    NVIC_Disable();
	typedef void(*pFunction)(void);

	pFunction Jump_To_Application;

	DWORD JumpAddress;

	SCB->VTOR = ApplicationAddress;                                    //должен быть выровнен по 0x80 байт
	JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);         //Адрес перехода по Reset
	Jump_To_Application = (pFunction) JumpAddress;                    //Указатель на функцию перехода
	__set_MSP(*(__IO uint32_t*) ApplicationAddress);                  //Установка стека
	Jump_To_Application();                                            //Запуск прошивки
}








