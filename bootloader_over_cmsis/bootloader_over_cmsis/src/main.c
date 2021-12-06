//=============================================================================
//=============================================================================
//=============================================================================
//
//
//
//
//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================


/*
    От себя :: 12 2021 :: убраны лишние драйвера -
    перенесено с другого камня . с оговорками работает на отладке NUCLEO L053 ..

*/

#include "main.h"
#include "bootloader_utils.h"
#include "drv_clock.h"
#include "drv_serial_port.h"
#include "drv_uart.h"
#include "sim.h"
#include "drv_usb_main.h"
#include "usb_utilities.h"










int main(void)
{
    move_vector_table();

    drv_clock_config();

    drv_clock_deinit();

    init_com_serial_port_driver();
    drv_uart_init(false);
    radio_init();

    drv_usb_detect_init();
    usb_connect_control();

    radio_reset(false);

    DWORD timer;
    CLEAR_TIMER(timer);
    DWORD ledtimer;
    CLEAR_TIMER(ledtimer);

    timer+=1000;

    bool led=true;

    if(usb_send)
        mode = EBM_MODE_BOOT;
    while(mode != EBM_MODE_JUMP)
    {
        usb_connect_control();

        if(!usb_send)
            mode = EBM_MODE_JUMP;

        if(TIMER(timer) >= 1000)
        {
            CLEAR_TIMER(timer);
        }

        if(TIMER(ledtimer) >= 100)
        {
          CLEAR_TIMER(ledtimer);
          led=!led;
        }
        usb_param_config();

        bootloader_mode_handler();
    }

    usb_send_pc_off();
    drv_usb_disconnect();
    drv_uart_deinit();

    radio_reset(true);
    radio_boot(false);

    JumpToApplication(0x8004000);

    return 0;
}
