
#ifndef __CONFIG_H_INCLUDED__
#define __CONFIG_H_INCLUDED__


#include <types.h>

//
// Version
//

#define PROJECT_NAME    "INTERSTELLAR"
#define VERSION         "0.1.6"
#define YEAR            "2016"


//
// DBG
#define EVALBOARD



//
// MAIN config
//

//#define TEST_BOARD_RELEASE
#define TEST_BOARD_DEVELOPMENT
//#define REAL_DEVICE

#define EVALUATION_BOARD

//
// SYSTEM MODE
//

#ifdef EVALUATION_BOARD
        #define INTRO

        #define BUTTONS_LEDS_DEMO

#endif
//
// PORTS
//

#define PORT_A_PINS_INIT
#define PORT_B_PINS_INIT
#define PORT_C_PINS_INIT
#define PORT_D_PINS_INIT
#define PORT_E_PINS_INIT
#define PORT_F_PINS_INIT

//#define PORT_A_RXTX_INIT
//#define PORT_B_RXTX_INIT
//#define PORT_C_RXTX_INIT
//#define PORT_D_RXTX_INIT
//#define PORT_E_RXTX_INIT
//#define PORT_F_RXTX_INIT

// JTAG IS PUT ON SEPARATE PINS HERE

//
// Target system parameters
//

// RST_CLK generators frequencies in HZ
//#define HSI_Value       ((uint32_t)8000000)
#define HSE_Value       ((uint32_t)8000000)
//#define HSE2_Value      ((uint32_t)25000000)
//#define LSI_Value       ((uint32_t)40000)
//#define LSE_Value       ((uint32_t)32768)

// RST_CLK frequencies startup timeouts settings
//#define HSEonTimeOut    ((uint16_t)0x0600)
//#define HSE2onTimeOut   ((uint16_t)0x8000)
//#define LSEonTimeOut    ((uint16_t)0x0600)
//#define HSIonTimeOut    ((uint16_t)0x0600)
//#define LSIonTimeOut    ((uint16_t)0x0600)
//#define PLLCPUonTimeOut ((uint16_t)0x0600)
//#define PLLUSBonTimeOut ((uint16_t)0x0600)

#define FLASH_PROG_FREQ_MHZ     (8.0) // ????????????????????????

// PLL SETUP
#define PLL_MUL_LABEL           RST_CLK_CPU_PLLmul6
#define PLL_MUL_TRUE_VALUE      (PLL_MUL_LABEL + 1)

//
// DEBUG:::: UART
//
#define USE_DEBUG_UART

#if defined USE_DEBUG_UART  // TODO:::: USE THESE SETTINGS PLZ

#define DEBUG_UART                      MDR_UART1
#define DEBUG_UART_PORT                 MDR_PORTC
#define DEBUG_UART_PINS                 (PORT_Pin_3 | PORT_Pin_4)
#define DEBUG_UART_PINS_FUNCTION        PORT_FUNC_MAIN
#define DEBUG_BAUD_RATE                 230400

#endif // End of USE_DEBUG_UART



#endif // End of __CONFIG_H_INCLUDED__



