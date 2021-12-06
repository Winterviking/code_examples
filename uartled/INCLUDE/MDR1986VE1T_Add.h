/*
Purpose is clear
remove MILANDR MDR code from project
*/

#ifndef __MDR_DEFINITIONS_H_INCLUDED__
#define __MDR_DEFINITIONS_H_INCLUDED__

#include <config.h>
#include <MDR1986VE1T.h>

/***************************************************************************************************************/
/***************************************************************************************************************/
/***************************************************************************************************************/
// Convertion :::: FILE MDR32F9Qx_rst_clk.h /******************************DONE-100%****************************/
/***************************************************************************************************************/
/***************************************************************************************************************/
/***************************************************************************************************************/

//
//
//RST_CLK_Exported_Types RST_CLK Exported Types
//
//

// Structure type for modules clocks frequencies expressed in Hz

typedef struct
{
  uint32_t CPU_CLK_Frequency;
  uint32_t USB_CLK_Frequency;
  uint32_t ADC_CLK_Frequency;
  uint32_t RTCHSI_Frequency;
  uint32_t RTCHSE_Frequency;
} RST_CLK_FreqTypeDef;

/***************************************************************************************************************/

// RST_CLK unit non-volatile settings init structure

typedef struct
{
     uint32_t REG_0F;
} Init_NonVolatile_RST_CLK_TypeDef;

//
//
// End of group RST_CLK_Exported_Types
//
//

//
//
// RST_CLK_Exported_Constants RST_CLK Exported Constants
//
//

/***************************************************************************************************************/

// HSE_configuration HSE configuration
// RST_CLK HSE (High Speed External) clock mode and source selection constants

#define RST_CLK_HSE_OFF                      ((uint32_t)0x00000000)
#define RST_CLK_HSE_ON                       ((uint32_t)0x00000001)
#define RST_CLK_HSE_Bypass                   ((uint32_t)0x00000002)

#define IS_RST_CLK_HSE(HSE)                  (((HSE) == RST_CLK_HSE_OFF) || \
                                              ((HSE) == RST_CLK_HSE_ON)  || \
                                              ((HSE) == RST_CLK_HSE_Bypass))

// End of group HSE_configuration

/***************************************************************************************************************/

// VE1T
// HSE2_configuration HSE2 configuration
// RST_CLK HSE2 (High Speed External 2 ) clock mode and source selection constants

#define RST_CLK_HSE2_OFF                                                ((uint32_t)0x00000000)
#define RST_CLK_HSE2_ON                                                 ((uint32_t)0x00000004)
#define RST_CLK_HSE2_Bypass                                             ((uint32_t)0x00000008)

#define IS_RST_CLK_HSE2(HSE2)                   (((HSE2) == RST_CLK_HSE2_OFF) || \
                                                 ((HSE2) == RST_CLK_HSE2_ON)  || \
                                                 ((HSE2) == RST_CLK_HSE2_Bypass))

// End of group HSE2_configuration

/***************************************************************************************************************/

// LSE_configuration LSE configuration
// RST_CLK LSE (Low Speed External) clock mode and source selection constants

#define RST_CLK_LSE_OFF                      ((uint32_t)0x00000000)
#define RST_CLK_LSE_ON                       ((uint32_t)0x00000001)
#define RST_CLK_LSE_Bypass                   ((uint32_t)0x00000002)

#define IS_RST_CLK_LSE(LSE)                  (((LSE) == RST_CLK_LSE_OFF) || \
                                              ((LSE) == RST_CLK_LSE_ON)  || \
                                              ((LSE) == RST_CLK_LSE_Bypass))

// End of group LSE_configuration

/***************************************************************************************************************/

// CPU_PLL_entry_clock_source CPU PLL entry clock source
// RST_CLK CPU_PLL clock mode and source selection constants

#define RST_CLK_CPU_PLLsrcHSIdiv1           ((uint32_t)0x00000000)
#define RST_CLK_CPU_PLLsrcHSIdiv2           ((uint32_t)0x00000001)
#define RST_CLK_CPU_PLLsrcHSEdiv1           ((uint32_t)0x00000002)
#define RST_CLK_CPU_PLLsrcHSEdiv2           ((uint32_t)0x00000003)

#define IS_RST_CLK_CPU_PLL_SOURCE(SRC)      (((SRC) == RST_CLK_CPU_PLLsrcHSIdiv1) || \
                                             ((SRC) == RST_CLK_CPU_PLLsrcHSIdiv2) || \
                                             ((SRC) == RST_CLK_CPU_PLLsrcHSEdiv1) || \
                                             ((SRC) == RST_CLK_CPU_PLLsrcHSEdiv2))

// End of group CPU_PLL_entry_clock_source

/***************************************************************************************************************/

// C2 Source
#define RST_CLK_CPU_C2_SRC_CPU_C1           ((uint32_t)0x00000000)
#define RST_CLK_CPU_C2_SRC_CPU_PLL0         ((uint32_t)0x00000004)


/***************************************************************************************************************/


// CPU_PLL_clock_multiplier CPU_PLL clock multiplier
// RST_CLK PLL_CPU_MUL multiplier of the CPU_C1 clock constants

#define RST_CLK_CPU_PLLmul1                     ((uint32_t)0x00000000)
#define RST_CLK_CPU_PLLmul2                     ((uint32_t)0x00000001)
#define RST_CLK_CPU_PLLmul3                     ((uint32_t)0x00000002)
#define RST_CLK_CPU_PLLmul4                     ((uint32_t)0x00000003)
#define RST_CLK_CPU_PLLmul5                     ((uint32_t)0x00000004)
#define RST_CLK_CPU_PLLmul6                     ((uint32_t)0x00000005)
#define RST_CLK_CPU_PLLmul7                     ((uint32_t)0x00000006)
#define RST_CLK_CPU_PLLmul8                     ((uint32_t)0x00000007)
#define RST_CLK_CPU_PLLmul9                     ((uint32_t)0x00000008)
#define RST_CLK_CPU_PLLmul10                    ((uint32_t)0x00000009)
#define RST_CLK_CPU_PLLmul11                    ((uint32_t)0x0000000A)
#define RST_CLK_CPU_PLLmul12                    ((uint32_t)0x0000000B)
#define RST_CLK_CPU_PLLmul13                    ((uint32_t)0x0000000C)
#define RST_CLK_CPU_PLLmul14                    ((uint32_t)0x0000000D)
#define RST_CLK_CPU_PLLmul15                    ((uint32_t)0x0000000E)
#define RST_CLK_CPU_PLLmul16                    ((uint32_t)0x0000000F)

#define IS_RST_CLK_CPU_PLL_MUL(SRC)             ((SRC>=0) && (SRC<16))

// End of group CPU_PLL_clock_multiplier

/***************************************************************************************************************/

// USB_PLL_entry_clock_source USB PLL entry clock source
// RST_CLK USB_PLL clock mode and source selection constants


#define RST_CLK_USB_PLLsrcHSIdiv1           ((uint32_t)0x00000000)
#define RST_CLK_USB_PLLsrcHSIdiv2           ((uint32_t)0x00000001)
#define RST_CLK_USB_PLLsrcHSEdiv1           ((uint32_t)0x00000002)
#define RST_CLK_USB_PLLsrcHSEdiv2           ((uint32_t)0x00000003)

#define IS_RST_CLK_USB_PLL_SOURCE(SRC)      (((SRC) == RST_CLK_USB_PLLsrcHSIdiv1) ||\
                                             ((SRC) == RST_CLK_USB_PLLsrcHSIdiv2) ||\
                                             ((SRC) == RST_CLK_USB_PLLsrcHSEdiv1) ||\
                                             ((SRC) == RST_CLK_USB_PLLsrcHSEdiv2))

// End of group USB_PLL_entry_clock_source

/***************************************************************************************************************/

// USB_PLL_clock_multiplier USB_PLL clock multiplier
// RST_CLK USB_C1 clock PLL_USB_MUL multiplier constants

#define RST_CLK_USB_PLLmul1                     ((uint32_t)0x00000000)
#define RST_CLK_USB_PLLmul2                     ((uint32_t)0x00000001)
#define RST_CLK_USB_PLLmul3                     ((uint32_t)0x00000002)
#define RST_CLK_USB_PLLmul4                     ((uint32_t)0x00000003)
#define RST_CLK_USB_PLLmul5                     ((uint32_t)0x00000004)
#define RST_CLK_USB_PLLmul6                     ((uint32_t)0x00000005)
#define RST_CLK_USB_PLLmul7                     ((uint32_t)0x00000006)
#define RST_CLK_USB_PLLmul8                     ((uint32_t)0x00000007)
#define RST_CLK_USB_PLLmul9                     ((uint32_t)0x00000008)
#define RST_CLK_USB_PLLmul10                    ((uint32_t)0x00000009)
#define RST_CLK_USB_PLLmul11                    ((uint32_t)0x0000000A)
#define RST_CLK_USB_PLLmul12                    ((uint32_t)0x0000000B)
#define RST_CLK_USB_PLLmul13                    ((uint32_t)0x0000000C)
#define RST_CLK_USB_PLLmul14                    ((uint32_t)0x0000000D)
#define RST_CLK_USB_PLLmul15                    ((uint32_t)0x0000000E)
#define RST_CLK_USB_PLLmul16                    ((uint32_t)0x0000000F)

#define IS_RST_CLK_USB_PLL_MUL(SRC)             ((SRC>=0) && (SRC<16))

// End of group USB_PLL_clock_multiplier

/***************************************************************************************************************/

// CPU_CLK_divider CPU CLK divider
// RST_CLK CPU_PLL output clock CPU_CLK_DIV divider constants

#define RST_CLK_CPUclkDIV1                    ((uint32_t)0x00000000)
#define RST_CLK_CPUclkDIV2                    ((uint32_t)0x00000008)
#define RST_CLK_CPUclkDIV4                    ((uint32_t)0x00000009)
#define RST_CLK_CPUclkDIV8                    ((uint32_t)0x0000000A)
#define RST_CLK_CPUclkDIV16                   ((uint32_t)0x0000000B)
#define RST_CLK_CPUclkDIV32                   ((uint32_t)0x0000000C)
#define RST_CLK_CPUclkDIV64                   ((uint32_t)0x0000000D)
#define RST_CLK_CPUclkDIV128                  ((uint32_t)0x0000000E)
#define RST_CLK_CPUclkDIV256                  ((uint32_t)0x0000000F)

#define IS_RST_CLK_CPUclkDIV(DIV)             (((DIV) == RST_CLK_CPUclkDIV1)   || \
                                               ((DIV) == RST_CLK_CPUclkDIV2)   || \
                                               ((DIV) == RST_CLK_CPUclkDIV4)   || \
                                               ((DIV) == RST_CLK_CPUclkDIV8)   || \
                                               ((DIV) == RST_CLK_CPUclkDIV16)  || \
                                               ((DIV) == RST_CLK_CPUclkDIV32)  || \
                                               ((DIV) == RST_CLK_CPUclkDIV64)  || \
                                               ((DIV) == RST_CLK_CPUclkDIV128) || \
                                               ((DIV) == RST_CLK_CPUclkDIV256))

// End of group CPU_CLK_divider

/***************************************************************************************************************/

// CPU_CLK_selector CPU CLK selector
// RST_CLK CPU_CLK source CPU_CLK selector constants

#define RST_CLK_CPUclkHSI                     ((uint32_t)0x00000000)
#define RST_CLK_CPUclkCPU_C3                  ((uint32_t)0x00000100)
#define RST_CLK_CPUclkLSE                     ((uint32_t)0x00000200)
#define RST_CLK_CPUclkLSI                     ((uint32_t)0x00000300)

#define IS_RST_CPU_CLK(SRC)                   (((SRC) == RST_CLK_CPUclkHSI)    || \
                                               ((SRC) == RST_CLK_CPUclkCPU_C3) || \
                                               ((SRC) == RST_CLK_CPUclkLSE)    || \
                                               ((SRC) == RST_CLK_CPUclkLSI))

// End of group CPU_CLK_selector

/***************************************************************************************************************/

// ADC_MCO_CLOCK_source ADC clock source
// RST_CLK ADC_CLK selector constants

#define RST_CLK_ADCclkCPU_C1                  ((uint32_t)0x00000020)
#define RST_CLK_ADCclkUSB_C1                  ((uint32_t)0x00000021)
#define RST_CLK_ADCclkCPU_C2                  ((uint32_t)0x00000022)
#define RST_CLK_ADCclkUSB_C2                  ((uint32_t)0x00000023)
#define RST_CLK_ADCclkLSE                     ((uint32_t)0x00000000)
#define RST_CLK_ADCclkLSI                     ((uint32_t)0x00000010)
#define RST_CLK_ADCclkHSI_C1                  ((uint32_t)0x00000030)

#define IS_RST_CLK_ADCclk(SRC)                (((SRC) == RST_CLK_ADCclkCPU_C1) || \
                                               ((SRC) == RST_CLK_ADCclkUSB_C1) || \
                                               ((SRC) == RST_CLK_ADCclkCPU_C2) || \
                                               ((SRC) == RST_CLK_ADCclkUSB_C2) || \
                                               ((SRC) == RST_CLK_ADCclkLSE)    || \
                                               ((SRC) == RST_CLK_ADCclkLSI)    || \
                                               ((SRC) == RST_CLK_ADCclkHSI_C1))

// End of group ADC_MCO_CLOCK_source

/***************************************************************************************************************/

// ADC_MCO_CS3_SEL ADC clock divider
// RST_CLK ADC_CS2_SEL output clock ADC_CS3_SEL divider constants

#define RST_CLK_ADCclkDIV1                    ((uint32_t)0x00000000)
#define RST_CLK_ADCclkDIV2                    ((uint32_t)0x00000008)
#define RST_CLK_ADCclkDIV4                    ((uint32_t)0x00000009)
#define RST_CLK_ADCclkDIV8                    ((uint32_t)0x0000000A)
#define RST_CLK_ADCclkDIV16                   ((uint32_t)0x0000000B)
#define RST_CLK_ADCclkDIV32                   ((uint32_t)0x0000000C)
#define RST_CLK_ADCclkDIV64                   ((uint32_t)0x0000000D)
#define RST_CLK_ADCclkDIV128                  ((uint32_t)0x0000000E)
#define RST_CLK_ADCclkDIV256                  ((uint32_t)0x0000000F)

#define IS_RST_CLK_ADCclkDivValue(SRC)        (((SRC) == RST_CLK_ADCclkDIV1)    || \
                                               ((SRC) == RST_CLK_ADCclkDIV2)    || \
                                               ((SRC) == RST_CLK_ADCclkDIV4)    || \
                                               ((SRC) == RST_CLK_ADCclkDIV8)    || \
                                               ((SRC) == RST_CLK_ADCclkDIV16)   || \
                                               ((SRC) == RST_CLK_ADCclkDIV32)   || \
                                               ((SRC) == RST_CLK_ADCclkDIV64)   || \
                                               ((SRC) == RST_CLK_ADCclkDIV128)  || \
                                               ((SRC) == RST_CLK_ADCclkDIV256))

// End of group ADC_MCO_CS3_SEL

/***************************************************************************************************************/

// AUC_MCO_CLOCK_source AUC clock source
// RST_CLK AUC_CLK selector constants

#define RST_CLK_AUCclkHSI_C1                                            ((uint32_t)0x00000000)
#define RST_CLK_AUCclkHSI_2_C1                                          ((uint32_t)0x00010000)
#define RST_CLK_AUCclkHSE_C1                                            ((uint32_t)0x00020000)
#define RST_CLK_AUCclkHSE_2_C1                                          ((uint32_t)0x00030000)
#define RST_CLK_AUCclkPLLCPU                                            ((uint32_t)0x00100000)
#define RST_CLK_AUCclkPLLUSB                                            ((uint32_t)0x00200000)

#define IS_RST_CLK_AUCclk(SRC)                                          (((SRC) == RST_CLK_AUCclkHSI_C1)   || \
                                                                                                         ((SRC) == RST_CLK_AUCclkHSI_2_C1) || \
                                                                                                         ((SRC) == RST_CLK_AUCclkHSE_C1)   || \
                                                                                                         ((SRC) == RST_CLK_AUCclkHSE_2_C1) || \
                                                                                                         ((SRC) == RST_CLK_AUCclkPLLCPU)   || \
                                                                                                         ((SRC) == RST_CLK_AUCclkPLLUSB))
// End of group AUC_MCO_CLOCK_source

/***************************************************************************************************************/

// AUCclkDIV_divider AUC MCO divider
// AUC_MCO_CLK AUC_CLK output clock AUC_CLK_DIV divider

#define RST_CLK_AUCclkDIV1                                                      ((uint32_t)0x00000000)
#define RST_CLK_AUCclkDIV2                                                      ((uint32_t)0x08000000 | 0x00000000)
#define RST_CLK_AUCclkDIV4                                                      ((uint32_t)0x08000000 | 0x01000000)
#define RST_CLK_AUCclkDIV8                                                      ((uint32_t)0x08000000 | 0x02000000)
#define RST_CLK_AUCclkDIV16                                                     ((uint32_t)0x08000000 | 0x03000000)
#define RST_CLK_AUCclkDIV32                                                     ((uint32_t)0x08000000 | 0x04000000)
#define RST_CLK_AUCclkDIV64                                                     ((uint32_t)0x08000000 | 0x05000000)
#define RST_CLK_AUCclkDIV128                                            ((uint32_t)0x08000000 | 0x06000000)
#define RST_CLK_AUCclkDIV256                                            ((uint32_t)0x08000000 | 0x07000000)

#define IS_RST_CLK_AUCclkDIV(DIV)                                       (((DIV) == RST_CLK_AUCclkDIV1)   || \
                                                                                                         ((DIV) == RST_CLK_AUCclkDIV2)   || \
                                                                                                         ((DIV) == RST_CLK_AUCclkDIV4)   || \
                                                                                                         ((DIV) == RST_CLK_AUCclkDIV8)   || \
                                                                                                         ((DIV) == RST_CLK_AUCclkDIV16)  || \
                                                                                                         ((DIV) == RST_CLK_AUCclkDIV32)  || \
                                                                                                         ((DIV) == RST_CLK_AUCclkDIV64)  || \
                                                                                                         ((DIV) == RST_CLK_AUCclkDIV128) || \
                                                                                                         ((DIV) == RST_CLK_AUCclkDIV256))
// End of group AUCclkDIV_divider

/***************************************************************************************************************/

// CLK_peripheral CLK peripheral
// RST_CLK peripheral modules clock constants

#define PCLK_BIT(BASE)              ((uint32_t)(1 << ((((uint32_t)BASE) >> 15) & 0x1F)))

// VE1T
        #define RST_CLK_PCLK_CAN1           PCLK_BIT(MDR_CAN1_BASE)
        #define RST_CLK_PCLK_CAN2           PCLK_BIT(MDR_CAN2_BASE)
        #define RST_CLK_PCLK_USB            PCLK_BIT(MDR_USB_BASE)
        #define RST_CLK_PCLK_EEPROM         PCLK_BIT(MDR_EEPROM_BASE)
        #define RST_CLK_PCLK_RST_CLK        PCLK_BIT(MDR_RST_CLK_BASE)
        #define RST_CLK_PCLK_DMA            PCLK_BIT(MDR_DMA_BASE)
        #define RST_CLK_PCLK_UART1          PCLK_BIT(MDR_UART1_BASE)
        #define RST_CLK_PCLK_UART2          PCLK_BIT(MDR_UART2_BASE)
        #define RST_CLK_PCLK_SSP1           PCLK_BIT(MDR_SSP1_BASE)
        #define RST_CLK_PCLK_MIL_STD_15531  PCLK_BIT(MDR_MIL_STD_15531_BASE)
        #define RST_CLK_PCLK_MIL_STD_15532  PCLK_BIT(MDR_MIL_STD_15532_BASE)
        #define RST_CLK_PCLK_POWER          PCLK_BIT(MDR_POWER_BASE)
        #define RST_CLK_PCLK_WWDG           PCLK_BIT(MDR_WWDG_BASE)
        #define RST_CLK_PCLK_IWDG           PCLK_BIT(MDR_IWDG_BASE)
        #define RST_CLK_PCLK_TIMER1         PCLK_BIT(MDR_TIMER1_BASE)
        #define RST_CLK_PCLK_TIMER2         PCLK_BIT(MDR_TIMER2_BASE)
        #define RST_CLK_PCLK_TIMER3         PCLK_BIT(MDR_TIMER3_BASE)
        #define RST_CLK_PCLK_ADC            PCLK_BIT(MDR_ADC_BASE)
        #define RST_CLK_PCLK_DAC            PCLK_BIT(MDR_DAC_BASE)
        #define RST_CLK_PCLK_TIMER4         PCLK_BIT(MDR_TIMER4_BASE)
        #define RST_CLK_PCLK_SSP2           PCLK_BIT(MDR_SSP2_BASE)
        #define RST_CLK_PCLK_PORTA          PCLK_BIT(MDR_PORTA_BASE)
        #define RST_CLK_PCLK_PORTB          PCLK_BIT(MDR_PORTB_BASE)
        #define RST_CLK_PCLK_PORTC          PCLK_BIT(MDR_PORTC_BASE)
        #define RST_CLK_PCLK_PORTD          PCLK_BIT(MDR_PORTD_BASE)
        #define RST_CLK_PCLK_PORTE          PCLK_BIT(MDR_PORTE_BASE)
        #define RST_CLK_PCLK_ARINC429R      PCLK_BIT(MDR_ARINC429R_BASE)
        #define RST_CLK_PCLK_BKP            PCLK_BIT(MDR_BKP_BASE)
        #define RST_CLK_PCLK_ARINC429T      PCLK_BIT(MDR_ARINC429T_BASE)
        #define RST_CLK_PCLK_PORTF          PCLK_BIT(MDR_PORTF_BASE)
        #define RST_CLK_PCLK_EBC            PCLK_BIT(MDR_EBC_BASE)
        #define RST_CLK_PCLK_SSP3           PCLK_BIT(MDR_SSP3_BASE)

#define IS_RST_CLK_PCLK(PCLK)                   (1)

// End of group CLK_peripheral

/***************************************************************************************************************/

//RST_CLK_Flag RST_CLK Flag
// RST_CLK flag identifiers

#define RST_CLK_FLAG_HSIRDY                   ((uint32_t)(0x00 | 23))
#define RST_CLK_FLAG_LSIRDY                   ((uint32_t)(0x00 | 21))
#define RST_CLK_FLAG_HSERDY                   ((uint32_t)(0x20 |  2))
#define RST_CLK_FLAG_HSE2RDY                  ((uint32_t)(0x20 |  3))
#define RST_CLK_FLAG_LSERDY                   ((uint32_t)(0x00 | 13))
#define RST_CLK_FLAG_PLLCPURDY                ((uint32_t)(0x20 |  1))
#define RST_CLK_FLAG_PLLUSBRDY                ((uint32_t)(0x20 |  0))

#define IS_RST_CLK_FLAG(FLAG)                 (((FLAG) == RST_CLK_FLAG_HSIRDY)    || \
                                               ((FLAG) == RST_CLK_FLAG_LSIRDY)    || \
                                               ((FLAG) == RST_CLK_FLAG_HSERDY)    || \
                                               ((FLAG) == RST_CLK_FLAG_HSE2RDY)   || \
                                               ((FLAG) == RST_CLK_FLAG_LSERDY)    || \
                                               ((FLAG) == RST_CLK_FLAG_PLLCPURDY) || \
                                               ((FLAG) == RST_CLK_FLAG_PLLUSBRDY))

// End of group RST_CLK_Flag

/***************************************************************************************************************/

#define IS_RCC_CLK_HSI_TRIM_VALUE(TRIM)       ((TRIM) <= 0x3F)
#define IS_RCC_CLK_LSI_TRIM_VALUE(TRIM)       ((TRIM) <= 0x1F)

/***************************************************************************************************************/

// RST_CLK_HSI_C1_SEL HSI clock divider
// RST_CLK HSI clock HSI_C1_SEL divider constants

#define RST_CLK_HSIclkDIV1                    ((uint32_t)0x00000000)
#define RST_CLK_HSIclkDIV2                    ((uint32_t)0x00000008)
#define RST_CLK_HSIclkDIV4                    ((uint32_t)0x00000009)
#define RST_CLK_HSIclkDIV8                    ((uint32_t)0x0000000A)
#define RST_CLK_HSIclkDIV16                   ((uint32_t)0x0000000B)
#define RST_CLK_HSIclkDIV32                   ((uint32_t)0x0000000C)
#define RST_CLK_HSIclkDIV64                   ((uint32_t)0x0000000D)
#define RST_CLK_HSIclkDIV128                  ((uint32_t)0x0000000E)
#define RST_CLK_HSIclkDIV256                  ((uint32_t)0x0000000F)

#define IS_RST_CLK_HSIclkDivValue(SRC)        (((SRC) == RST_CLK_HSIclkDIV1)    || \
                                               ((SRC) == RST_CLK_HSIclkDIV2)    || \
                                               ((SRC) == RST_CLK_HSIclkDIV4)    || \
                                               ((SRC) == RST_CLK_HSIclkDIV8)    || \
                                               ((SRC) == RST_CLK_HSIclkDIV16)   || \
                                               ((SRC) == RST_CLK_HSIclkDIV32)   || \
                                               ((SRC) == RST_CLK_HSIclkDIV64)   || \
                                               ((SRC) == RST_CLK_HSIclkDIV128)  || \
                                               ((SRC) == RST_CLK_HSIclkDIV256))

// End of group RST_CLK_HSI_C1_SEL

/***************************************************************************************************************/

// RST_CLK_HSE_C1_SEL HSE clock divider
// RST_CLK HSE clock HSE_C1_SEL divider constants
#define RST_CLK_HSEclkDIV1                    ((uint32_t)0x00000000)
#define RST_CLK_HSEclkDIV2                    ((uint32_t)0x00000008)
#define RST_CLK_HSEclkDIV4                    ((uint32_t)0x00000009)
#define RST_CLK_HSEclkDIV8                    ((uint32_t)0x0000000A)
#define RST_CLK_HSEclkDIV16                   ((uint32_t)0x0000000B)
#define RST_CLK_HSEclkDIV32                   ((uint32_t)0x0000000C)
#define RST_CLK_HSEclkDIV64                   ((uint32_t)0x0000000D)
#define RST_CLK_HSEclkDIV128                  ((uint32_t)0x0000000E)
#define RST_CLK_HSEclkDIV256                  ((uint32_t)0x0000000F)

#define IS_RST_CLK_HSEclkDivValue(SRC)        (((SRC) == RST_CLK_HSEclkDIV1)    || \
                                               ((SRC) == RST_CLK_HSEclkDIV2)    || \
                                               ((SRC) == RST_CLK_HSEclkDIV4)    || \
                                               ((SRC) == RST_CLK_HSEclkDIV8)    || \
                                               ((SRC) == RST_CLK_HSEclkDIV16)   || \
                                               ((SRC) == RST_CLK_HSEclkDIV32)   || \
                                               ((SRC) == RST_CLK_HSEclkDIV64)   || \
                                               ((SRC) == RST_CLK_HSEclkDIV128)  || \
                                               ((SRC) == RST_CLK_HSEclkDIV256))

// End of group RST_CLK_HSE_C1_SEL

//
//
// End of group RST_CLK_Exported_Constants RST_CLK Exported Constants
//
//

/***************************************************************************************************************/
/***************************************************************************************************************/
/***************************************************************************************************************/

/***************************************************************************************************************/
/***************************************************************************************************************/
/***************************************************************************************************************/
// Convertion :::: FILE MDR32F9Qx_port.h /********************************DONE-100%*****************************/
/***************************************************************************************************************/
/***************************************************************************************************************/
/***************************************************************************************************************/

//
//
// PORT_Exported_Types PORT Exported Types
//
//

#define IS_PORT_ALL_PERIPH(PERIPH) (((PERIPH) == MDR_PORTA) || \
                                    ((PERIPH) == MDR_PORTB) || \
                                    ((PERIPH) == MDR_PORTC) || \
                                    ((PERIPH) == MDR_PORTD) || \
                                    ((PERIPH) == MDR_PORTE) || \
                                    ((PERIPH) == MDR_PORTF))

/***************************************************************************************************************/

// Configuration OE enumeration

typedef enum
{
  PORT_OE_IN            = 0x0,
  PORT_OE_OUT           = 0x1
}PORT_OE_TypeDef;

#define IS_PORT_OE(OE) (((OE) == PORT_OE_IN) || ((OE) == PORT_OE_OUT))

/***************************************************************************************************************/

// Configuration Mode enumeration

typedef enum
{
  PORT_MODE_ANALOG      = 0x0,
  PORT_MODE_DIGITAL     = 0x1
}PORT_MODE_TypeDef;

#define IS_PORT_MODE(MODE) (((MODE) == PORT_MODE_ANALOG) || ((MODE) == PORT_MODE_DIGITAL))

/***************************************************************************************************************/

//  Configuration PULL_UP enumeration

typedef enum
{
  PORT_PULL_UP_OFF      = 0x0,
  PORT_PULL_UP_ON       = 0x1
}PORT_PULL_UP_TypeDef;

#define IS_PORT_PULL_UP(PULL_UP) (((PULL_UP) == PORT_PULL_UP_OFF) || ((PULL_UP) == PORT_PULL_UP_ON))

/***************************************************************************************************************/

// Configuration PULL_DOWN enumeration

typedef enum
{
  PORT_PULL_DOWN_OFF    = 0x0,
  PORT_PULL_DOWN_ON     = 0x1
}PORT_PULL_DOWN_TypeDef;

#define IS_PORT_PULL_DOWN(PULL_DOWN) (((PULL_DOWN) == PORT_PULL_DOWN_ON) || \
                                      ((PULL_DOWN) == PORT_PULL_DOWN_OFF))

/***************************************************************************************************************/

// Configuration PD_SHM enumeration

typedef enum
{
  PORT_PD_SHM_OFF       = 0x0,
  PORT_PD_SHM_ON        = 0x1
}PORT_PD_SHM_TypeDef;

#define IS_PORT_PD_SHM(PORT_PD_SHM) (((PORT_PD_SHM) == PORT_PD_SHM_OFF) || \
                                     ((PORT_PD_SHM) == PORT_PD_SHM_ON))

/***************************************************************************************************************/

// Configuration PD_PD enumeration

typedef enum
{
  PORT_PD_DRIVER        = 0x0,
  PORT_PD_OPEN          = 0x1
}PORT_PD_TypeDef;

#define IS_PORT_PD(PORT_PD) (((PORT_PD) == PORT_PD_DRIVER) || ((PORT_PD) == PORT_PD_OPEN))

/***************************************************************************************************************/

// Configuration GFEN enumeration

typedef enum
{
  PORT_GFEN_OFF         = 0x0,
  PORT_GFEN_ON          = 0x1
}PORT_GFEN_TypeDef;

#define IS_PORT_GFEN(PORT_GFEN) (((PORT_GFEN) == PORT_GFEN_OFF) || ((PORT_GFEN) == PORT_GFEN_ON))

/***************************************************************************************************************/

// Configuration Function enumeration

typedef enum
{
  PORT_FUNC_PORT        = 0x0,
  PORT_FUNC_MAIN        = 0x1,
  PORT_FUNC_ALTER       = 0x2,
  PORT_FUNC_OVERRID     = 0x3
}PORT_FUNC_TypeDef;

#define IS_PORT_FUNC(FUNC) (((FUNC) == PORT_FUNC_PORT)  || ((FUNC) == PORT_FUNC_MAIN) || \
                            ((FUNC) == PORT_FUNC_ALTER) || ((FUNC) == PORT_FUNC_OVERRID))

/***************************************************************************************************************/

// Configuration Speed enumeration

typedef enum
{
  PORT_OUTPUT_OFF       = 0x0,
  PORT_SPEED_SLOW       = 0x1,
  PORT_SPEED_FAST       = 0x2,
  PORT_SPEED_MAXFAST    = 0x3
}PORT_SPEED_TypeDef;

#define IS_PORT_SPEED(SPEED) (((SPEED) == PORT_OUTPUT_OFF) || ((SPEED) == PORT_SPEED_SLOW) || \
                              ((SPEED) == PORT_SPEED_FAST) || ((SPEED) == PORT_SPEED_MAXFAST))

/***************************************************************************************************************/

// PORT Init structure definition

typedef struct
{
  uint16_t PORT_Pin;                     /*!< Specifies PORT pins to be configured.
                                              This parameter is a mask of @ref PORT_pins_define values. */
  PORT_OE_TypeDef PORT_OE;               /*!< Specifies in/out mode for the selected pins.
                                              This parameter is one of @ref PORT_OE_TypeDef values. */
  PORT_PULL_UP_TypeDef PORT_PULL_UP;     /*!< Specifies pull up state for the selected pins.
                                              This parameter is one of @ref PORT_PULL_UP_TypeDef values. */
  PORT_PULL_DOWN_TypeDef PORT_PULL_DOWN; /*!< Specifies pull down state for the selected pins.
                                              This parameter is one of @ref PORT_PULL_DOWN_TypeDef values. */
  PORT_PD_SHM_TypeDef PORT_PD_SHM;       /*!< Specifies SHM state for the selected pins.
                                              This parameter is one of @ref PORT_PD_SHM_TypeDef values. */
  PORT_PD_TypeDef PORT_PD;               /*!< Specifies PD state for the selected pins.
                                              This parameter is one of @ref PORT_PD_TypeDef values. */
  PORT_GFEN_TypeDef PORT_GFEN;           /*!< Specifies GFEN state for the selected pins.
                                              This parameter is one of @ref PORT_GFEN_TypeDef values. */
  PORT_FUNC_TypeDef PORT_FUNC;           /*!< Specifies operating function for the selected pins.
                                              This parameter is one of @ref PORT_FUNC_TypeDef values. */
  PORT_SPEED_TypeDef PORT_SPEED;         /*!< Specifies the speed for the selected pins.
                                              This parameter is one of @ref PORT_SPEED_TypeDef values. */
  PORT_MODE_TypeDef PORT_MODE;           /*!< Specifies the operating mode for the selected pins.
                                              This parameter is one of @ref PORT_MODE_TypeDef values. */
}PORT_InitTypeDef;

/***************************************************************************************************************/

// Bit_SET and Bit_RESET enumeration


typedef enum
{
  Bit_RESET = 0,
  Bit_SET
}BitAction;

#define IS_PORT_BIT_ACTION(ACTION) (((ACTION) == Bit_RESET) || ((ACTION) == Bit_SET))

//
//
// End of group PORT_Exported_Types
//
//

//
//
//PORT_Exported_Constants PORT Exported Constants
//
//

// PORT_JTAG_define PORT JTAG define

/*
#if defined (USE_JTAG_A)
#define PORT_JTAG                   MDR_PORTB    // Port containing JTAG interface
#define PORT_JTAG_Msk               0x001FU      // JTAG pins

#elif defined (USE_JTAG_B)
#define PORT_JTAG                   MDR_PORTD    // Port containing JTAG interface
#define PORT_JTAG_Msk               0x001FU      // JTAG pins

#endif


#if defined (PORT_JTAG)
#define JTAG_PINS(PORT)             (((PORT) == PORT_JTAG) ? PORT_JTAG_Msk : 0)

#else
#define JTAG_PINS(PORT)             0

#endif

#define IS_NOT_JTAG_PIN(PORT, PIN)  (((PIN) & JTAG_PINS(PORT)) == 0x00)

*/

// End of group PORT_JTAG_define

/***************************************************************************************************************/

// PORT_pins_define PORT pins define

#define PORT_Pin_0                  0x0001U  /*!< Pin 0 selected */
#define PORT_Pin_1                  0x0002U  /*!< Pin 1 selected */
#define PORT_Pin_2                  0x0004U  /*!< Pin 2 selected */
#define PORT_Pin_3                  0x0008U  /*!< Pin 3 selected */
#define PORT_Pin_4                  0x0010U  /*!< Pin 4 selected */
#define PORT_Pin_5                  0x0020U  /*!< Pin 5 selected */
#define PORT_Pin_6                  0x0040U  /*!< Pin 6 selected */
#define PORT_Pin_7                  0x0080U  /*!< Pin 7 selected */
#define PORT_Pin_8                  0x0100U  /*!< Pin 8 selected */
#define PORT_Pin_9                  0x0200U  /*!< Pin 9 selected */
#define PORT_Pin_10                 0x0400U  /*!< Pin 10 selected */
#define PORT_Pin_11                 0x0800U  /*!< Pin 11 selected */
#define PORT_Pin_12                 0x1000U  /*!< Pin 12 selected */
#define PORT_Pin_13                 0x2000U  /*!< Pin 13 selected */
#define PORT_Pin_14                 0x4000U  /*!< Pin 14 selected */
#define PORT_Pin_15                 0x8000U  /*!< Pin 15 selected */
#define PORT_Pin_All                0xFFFFU  /*!< All pins selected */

#define IS_PORT_PIN(PIN)            ((((PIN) & (uint32_t)0xFFFF0000UL) == 0x00) && \
                                     ((PIN) != 0x00))

#define IS_GET_PORT_PIN(PIN)        (((PIN) == PORT_Pin_0 ) || \
                                     ((PIN) == PORT_Pin_1 ) || \
                                     ((PIN) == PORT_Pin_2 ) || \
                                     ((PIN) == PORT_Pin_3 ) || \
                                     ((PIN) == PORT_Pin_4 ) || \
                                     ((PIN) == PORT_Pin_5 ) || \
                                     ((PIN) == PORT_Pin_6 ) || \
                                     ((PIN) == PORT_Pin_7 ) || \
                                     ((PIN) == PORT_Pin_8 ) || \
                                     ((PIN) == PORT_Pin_9 ) || \
                                     ((PIN) == PORT_Pin_10) || \
                                     ((PIN) == PORT_Pin_11) || \
                                     ((PIN) == PORT_Pin_12) || \
                                     ((PIN) == PORT_Pin_13) || \
                                     ((PIN) == PORT_Pin_14) || \
                                     ((PIN) == PORT_Pin_15))

// End of group PORT_pins_define

//
//
// End of group PORT_Exported_Constants
//
//

//
//
// PORT.H ends heres
//
//

// init ports

//
//
// PORT DEFINITION MACRO FUNCTIONS ))))))))
//
//

#define PIN_(pin__,value__,size__) ((int)value << (pin__*size__))
#define PIN1_(pin__,value__) PIN_(pin__,value__,1)
#define PIN2_(pin__,value__) PIN_(pin__,value__,2)

#define PORT_EDIT__(reg__,pins__) reg__ |= pins__
#define PORT_INIT__(reg__, pins__) reg__ = pins__;

// xample:
/*
  MDR_PORTA->OE     = PORT_INIT__(
                                        PIN1_(PORT_Pin_0,       PORT_OE_OUT)    |
                                        PIN1_(PORT_Pin_1,       PORT_OE_IN)     |
                                        PIN1_(PORT_Pin_2,       PORT_OE_OUT)    |
                                        PIN1_(PORT_Pin_13,      PORT_OE_IN)
                                  );
  MDR_PORTA->FUNC   = PORT_INIT__(
                                        PIN2_(PORT_Pin_0,       PORT_FUNC_ALTER)        |
                                        PIN2_(PORT_Pin_1,       PORT_FUNC_MAIN)         |
                                        PIN2_(PORT_Pin_2,       PORT_FUNC_ALTER)        |
                                        PIN2_(PORT_Pin_13,      PORT_FUNC_OVERRID)
                                  );



  MDR_PORTA->ANALOG = PIN1_
  MDR_PORTA->PULL   = PIN2_;
  MDR_PORTA->PD     = PIN2_;
  MDR_PORTA->PWR    = PIN2_;
  MDR_PORTA->GFEN   = PIN1_;

*/

// CAUTION :: no jtag filtering
#define PORT_RESET_PINS(PORT__) PORT__->CLRTX = PORT__ // PORT_Pin_X

#define PORT_SET_BIT(PORT__,Pin__) PORT__->SETTX |= (1 << Pin__)
#define PORT_CLR_BIT(PORT__,Pin__) PORT__->CLRTX |= (1 << Pin__)





















































//
//
// RST CLOCK C DEFINITIONS //// use if possible
//
//

// RST_CLK RST_CLK
// RST_CLK_Private_Constants RST_CLK Private Constants

// RCC_CLK registers bit address in the alias region
#define PERIPH_BASE                 0x40000000
#define PERIPH_BB_BASE              0x42000000
#define RST_CLK_OFFSET              (MDR_RST_CLK_BASE - PERIPH_BASE)
#define BKP_OFFSET                  (MDR_BKP_BASE - PERIPH_BASE)

#define SFR_OFFSET(TP, MOD, SFR)    ((uint32_t)&((TP*)MOD)->SFR)
#define BB_ADDR(TP, MOD, SFR, BIT)  (PERIPH_BB_BASE + SFR_OFFSET(TP, MOD, SFR)*32 + BIT*4)
#define RST_CLK_BB(SFR, BIT)        BB_ADDR(MDR_RST_CLK_TypeDef, RST_CLK_OFFSET, SFR, BIT)
#define BKP_BB(SFR, BIT)            BB_ADDR(MDR_BKP_TypeDef, BKP_OFFSET, SFR, BIT)

#define FLAG_MASK                   ((uint8_t)0x1F)
#define FLAG_SFR_MASK               ((uint8_t)0xE0)

#define HSI_RDY_MASK                (1 << 23)
#define LSI_RDY_MASK                (1 << 21)
#define LSE_RDY_MASK                (1 << 13)
#define HSE_RDY_MASK                (1 << 2)
#define HSE2_RDY_MASK                   (1 << 3)
#define PLLCPU_RDY_MASK             (1 << 1)
#define PLLUSB_RDY_MASK             (1 << 0)
#define PLLCPUMUL_OFFSET            8
#define PLLCPUmulclr                (~(uint32_t)(0x0F << PLLCPUMUL_OFFSET))
#define PLLUSBMUL_OFFSET            4
#define PLLUSBmulclr                (~(uint32_t)(0x0F << PLLUSBMUL_OFFSET))
#define CPU_C1_SELclr               (~(uint32_t)0x03)
#define CPU_C3_SELclr               (~(uint32_t)0x00000F0)
#define CPU_HCLK_SELclr             (~(uint32_t)(0x03 << 8))
#define ADC_C12_SELclr              (~(uint32_t)((0x03 << 4) | 0x03))
#define AUC_C12_SELclr              (~(uint32_t)((0x03 << 20) | (0x03 << 16)))
#define AUC_C3_SELclr                   (~(uint32_t)((0xF<<24)))
#define ADC_C3_SEL_OFFSET           8
#define ADC_C3_SELclr               (~(uint32_t)(0x0F << ADC_C3_SEL_OFFSET))
#define HSI_SEL_OFFSET              4
#define HSI_SELclr                  (~(uint32_t)(0x0F << HSI_SEL_OFFSET))
#define HSE_SEL_OFFSET              0
#define HSE_SELclr                  (~(uint32_t)(0x0F << HSE_SEL_OFFSET))
#define USB_C1_SELclr               (~(uint32_t)0x03)


#define HSITRIM_OFFSET              24
#define HSITRIM_MASK                ((uint32_t)(0x3F << HSITRIM_OFFSET))

#define HSION_OFFSET                22
#define HSION_MASK                  ((uint32_t)(1 << HSION_OFFSET))

#define LSITRIM_OFFSET              16
#define LSITRIM_MASK                ((uint32_t)(0x1F << LSITRIM_OFFSET))

#define LSION_OFFSET                15
#define LSION_MASK                  ((uint32_t)(1 << LSION_OFFSET))






























//
//
// MIL_STD_1553
//
//


//
//
// MIL_STD_1553_Exported_Types MIL_STD_1553 Exported Types
//
//

// MIL_STD_1553 Init Structure definition
typedef struct {
        uint32_t MIL_STD_1553_Mode; // This member configures the MIL_STD_1553 mode.                    This parameter is one of MIL_STD_1553_Mode values
        uint32_t MIL_STD_1553_RERR; // This member configures the resetting of errors in TD mode.       This parameter can be: ENABLE or DISABLE
        uint32_t MIL_STD_1553_DIV;  // This member configures the MIL_STD_1553 clock divider. [0..127] If MAN_CLK not a multiple of 8 then DIV[6:3]=(MAN_CLK/8)+1, DIV[2:0]=0, but the stability of reception is not guaranteed.
        uint32_t MIL_STD_1553_RTA;  // This member configures the address of the terminal device. This parameter is value from 0 to 0x1E
        uint32_t MIL_STD_1553_TRB;  // This member configures the Transmission block the backup channel. This parameter can be: ENABLE or DISABLE.
        uint32_t MIL_STD_1553_TRA;  // This member configures the Transmission block the main channel. This parameter can be: ENABLE or DISABLE.

        // REVISION 3 availability
        FunctionalState MIL_STD_1553_Inversion_Signals;     // This member enables or disables the inversion signals PRD_PRMA, PRD_PRMB, PRD_PRMC, PRD_PRMD. This parameter can be: ENABLE or DISABLE.
        FunctionalState MIL_STD_1553_Filtration_Flow;       // This option enables or disables the filtering flow NRZ, in the case of drivers with nekkorektno duty cycle and pulse width of NRZ code. This parameter can be: ENABLE or DISABLE. */
        FunctionalState MIL_STD_1553_Automatic_Adjustment;  // This member enables or disables the automatic adjustment of the mid bit intervals. This parameter can be: ENABLE or DISABLE. */
} MIL_STD_1553_InitTypeDef;

/***************************************************************************************************************/

// Data Fields Union definition

typedef union {
        uint32_t NumberDataWords        :5; // Specifies the number of data word in a message.
        uint32_t Cmd                    :5; // Specifies the command type.
} Data_FieldsTypeDef;

/***************************************************************************************************************/

// MIL_STD_1553 CommandWord Bit Fields definition
typedef struct {
        //Data_FieldsTypeDef Data;
        uint32_t Data                   :5;     // Specifies the number of data word in a message or command type. This parameter is number from 0 to 0x1F.
        uint32_t Subaddress             :5;     // Specifies the code subaddress OU or code attribute control mode 00000 or 11111. This parameter is number from 0 to 0x1F.
        uint32_t ReadWriteBit           :1;     // Specifies the action to execute TD (receive or transmit DW). This parameter is one of @ref MIL_STD_READ_WRITE_BIT values.
        uint32_t TerminalDeviceAddress  :5;     // Specifies the address of TD, which is intended CW. This parameter is number from 0 to 0x1F.
} MIL_STD_1553_CommandWordBitFields;

/***************************************************************************************************************/

// MIL_STD_1553 CommandWord Unioun definition
typedef union {
        uint32_t                                CommandWord; // Specifies the fully Command Word.
        MIL_STD_1553_CommandWordBitFields       Fields;      // Specifies the particular field of the Command Word.
} MIL_STD_1553_CommandWordTypeDef;

/***************************************************************************************************************/

// MIL_STD_1553 StatusWord Bit Fields definition
typedef struct {
        uint32_t        FaultTDBit                      :1; // Specifies the fault terminal device. This parameter can be: SET or RESET.
        uint32_t        AdoptionControlInterfaceBit     :1; // Specifies the adoption control interface. This parameter can be: SET or RESET.
        uint32_t        AbonentFaultBit                 :1; // Specifies the fault abonent. This parameter can be: SET or RESET.
        uint32_t        BusyBit                         :1; // Specifies the busy abonent. This parameter can be: SET or RESET.
        uint32_t        GroupCommandBit                 :1; // Specifies the group command. This parameter can be: SET or RESET.
        uint32_t        Reserved                        :3; // Reserved
        uint32_t        ServiceRequestBit               :1; // Specifies the service request. This parameter can be: SET or RESET.
        uint32_t        TransferReplyWordBit            :1; // Specifies the transfer replay word. This parameter can be: SET or RESET.
        uint32_t        ErrorBit                        :1; // Specifies the error in the message. This parameter can be: SET or RESET.
        uint32_t        TerminalDeviceAddress           :5; // Specifies the termnal device address. This parameter is number from 0x00 to 0x1F.
} MIL_STD_1553_StatusWordBitFields;

/***************************************************************************************************************/

// MIL_STD_1553 StatusWord Structure definition
typedef union {
        uint32_t                                StatusWord; // Specifies the fully Status Word.
        MIL_STD_1553_StatusWordBitFields        Fields;     // Specifies the particular field of the Status Word.
} MIL_STD_1553_StatusWordTypeDef;

/***************************************************************************************************************/

// Bool Structure definition
typedef enum {
        FALSE = 0,
        TRUE = !DISABLE
} Bool;

//
//
// End of group MIL_STD_1553_Exported_Types
//
//

//
//
// MIL_STD_1553_Exported_Macros MIL_STD_1553 Exported Macros
//
//

#define IS_MIL_STD_1553_ALL_PERIPH(PERIPH)              (((PERIPH) == MDR_MIL_STD_15531) ||\
                                                         ((PERIPH) == MDR_MIL_STD_15532))

#define IS_MIL_STD_1553_DEVIDER(DIVIDER)                ((DIVIDER) <= 0x7F)

#define IS_MIL_STD_1553_RTA(RTA)                        ((RTA) <= 0x1F)

/***************************************************************************************************************/

// MIL_STD_1553_Mode MIL_STD_1553 Mode
#define MIL_STD_1553_ModeBusController                  ((uint32_t)0x01)
#define MIL_STD_1553_ModeTerminal                       ((uint32_t)0x02)
#define MIL_STD_1553_ModeMonitor                        ((uint32_t)0x03)

#define MIL_STD_1553_MODE_Pos                           2

#define IS_MIL_STD_1553_MODE(MODE)                      (((MODE) == MIL_STD_1553_ModeBusController) ||\
                                                         ((MODE) == MIL_STD_1553_ModeMonitor)       ||\
                                                         ((MODE) == MIL_STD_1553_ModeTerminal))

// End of group MIL_STD_1553_Mode

/***************************************************************************************************************/

// MIL_STD_READ_WRITE_BIT MIL_STD_READ_WRITE BIT
#define MIL_STD_1553_TD_TO_BC                           ((uint32_t)0x00000001)
#define MIL_STD_1553_BC_TO_TD                           ((uint32_t)0x00000000)

#define IS_MIL_STD_READ_WRITE_BIT(BIT)                  (((BIT) == MIL_STD_1553_TD_TO_BC) || \
                                                         ((BIT) == MIL_STD_1553_BC_TO_TD))

// End of group MIL_STD_READ_WRITE_BIT

/***************************************************************************************************************/

// MIL_STD_1553_Flags MIL_STD_1553 Flags
#define MIL_STD_1553_FLAG_IDLE                          ((uint32_t)0x00000001)
#define MIL_STD_1553_FLAG_RFLAGN                        ((uint32_t)0x00000002)
#define MIL_STD_1553_FLAG_VALMESS                       ((uint32_t)0x00000004)
#define MIL_STD_1553_FLAG_ERR                           ((uint32_t)0x00000008)
#define MIL_STD_1553_FLAG_RCVA                          ((uint32_t)0x00000010)
#define MIL_STD_1553_FLAG_RCVB                          ((uint32_t)0x00000020)

#define IS_MIL_STD_1553_FLAG(FLAG)                      (((FLAG) == MIL_STD_1553_FLAG_IDLE)     ||\
                                                         ((FLAG) == MIL_STD_1553_FLAG_RFLAGN)   ||\
                                                         ((FLAG) == MIL_STD_1553_FLAG_VALMESS)  ||\
                                                         ((FLAG) == MIL_STD_1553_FLAG_ERR)      ||\
                                                         ((FLAG) == MIL_STD_1553_FLAG_RCVA)     ||\
                                                         ((FLAG) == MIL_STD_1553_FLAG_RCVB))

// End of group MIL_STD_1553_Flags

/***************************************************************************************************************/

// MIL_STD_1553_Interrupt_defintion MIL_STD_1553 Interrupt defintion

#define MIL_STD_1553_IT_IDLEIE                          ((uint32_t)0x00000001)
#define MIL_STD_1553_IT_RFLAGNIE                        ((uint32_t)0x00000002)
#define MIL_STD_1553_IT_VALMESSIE                       ((uint32_t)0x00000004)
#define MIL_STD_1553_IT_ERRIE                           ((uint32_t)0x00000008)

#define MIL_STD_1553_IT_MASK                            (MIL_STD_1553_IT_IDLEIE         |\
                                                         MIL_STD_1553_IT_RFLAGNIE       |\
                                                         MIL_STD_1553_IT_VALMESSIE      |\
                                                         MIL_STD_1553_IT_ERRIE)

#define IS_MIL_STD_1553_IT(IT)                          ((IT) & (~MIL_STD_1553_IT_MASK) == 0)

/*
#define IS_MIL_STD_1553_IT(IT)                          (((IT) == MIL_STD_1553_IT_IDLEIE) ||\
                                                         ((IT) == MIL_STD_1553_IT_RFLAGNIE) ||\
                                                         ((IT) == MIL_STD_1553_IT_VALMESSIE) ||\
                                                         ((IT) == MIL_STD_1553_IT_ERRIE))
*/

// End of group MIL_STD_1553_Interrupt_defintion

/***************************************************************************************************************/

// MIL_STD_1553_Number_CommandWord MIL_STD_1553 Number CommandWord
#define MIL_STD_1553_COMMAND_WORD1                      ((uint32_t)0x00000000)
#define MIL_STD_1553_COMMAND_WORD2                      ((uint32_t)0x00000001)

#define IS_MIL_STD_1553_COMMAND_WORD(COMMAND_WORD)      ((COMMAND_WORD) < 0x02)

// End of group MIL_STD_1553_Number_CommandWord

/***************************************************************************************************************/

// MIL_STD_1553_Number_StatusWord MIL_STD_1553 Number StatusWord
#define MIL_STD_1553_STATUS_WORD1                                       ((uint32_t)0x00000000)
#define MIL_STD_1553_STATUS_WORD2                                       ((uint32_t)0x00000001)

#define IS_MIL_STD_1553_STATUS_WORD(STATUS_WORD)        ((STATUS_WORD) < 0x02)

// End of group MIL_STD_1553_Number_StatusWord

/***************************************************************************************************************/

// MIL_STD_1553_Number_Transmitter MIL_STD_1553 Number Transmitter
#define MIL_STD_1553_TRANSMITTER_MAIN                                   ((uint32_t)0x0000010)
#define MIL_STD_1553_TRANSMITTER_RESERVE                                ((uint32_t)0x0000020)

#define IS_MIL_STD_1553_TRANSMITTER_CHANNEL(CHANNEL)    (((CHANNEL) == MIL_STD_1553_TRANSMITTER_MAIN) ||\
                                                         ((CHANNEL) == MIL_STD_1553_TRANSMITTER_RESERVE))

/***************************************************************************************************************/

// clock brg

#define MIL_STD_1553_HCLKdiv1                                   ((uint32_t)0x00000000)
#define MIL_STD_1553_HCLKdiv2                                   ((uint32_t)0x00000001)
#define MIL_STD_1553_HCLKdiv4                                   ((uint32_t)0x00000002)
#define MIL_STD_1553_HCLKdiv8                                   ((uint32_t)0x00000003)
#define MIL_STD_1553_HCLKdiv16                                  ((uint32_t)0x00000004)
#define MIL_STD_1553_HCLKdiv32                                  ((uint32_t)0x00000005)
#define MIL_STD_1553_HCLKdiv64                                  ((uint32_t)0x00000006)
#define MIL_STD_1553_HCLKdiv128                                 ((uint32_t)0x00000007)

#define IS_MIL_STD_1553_BRG(BRG)                                ((BRG) <= 7)

//
//
// End of group MIL_STD_1553_Exported_Macros MIL_STD_1553 Exported Macros
//
//

//
//
// mil std 1553 c file defines
//
//

#define MR_EN_Set                       ((uint32_t)0x00000001)  /*!< MIL_STD_1553 Enable mask */
#define MR_EN_Reset                     ((uint32_t)0x0000FFFE)  /*!< MIL_STD_1553 Disable mask */
#define MIL_STD_1553_RESET              MR_EN_Set
#define MIL_STD_1553_START              MR_EN_Reset


/***************************************************************************************************************/

// FOR TESTS

#define IS_MIL_STD_1553_SUBADDRES(SUBADDRES)                    (((SUBADDRES) != 0) && \
                                                                 ((SUBADDRES) <= 0x1F))

#define IS_MIL_STD_1553_NUMBER_DATA_WORDS(NUMBER_DATA_WORDS)    (((NUMBER_DATA_WORDS) != 0 ) &&\
                                                                 ((NUMBER_DATA_WORDS) <= 32))

/***************************************************************************************************************/

// Status Word 1 ( Response Word ) Definitions
// MDR_MIL_STD_1553->StatusWord1

#define MIL_STD_1553_SW1_TERMINAL_DEVICE_FAULT                          0x0001
#define MIL_STD_1553_SW1_BUS_CONTROLLER_STATUS_TRANSITION_ACCEPTED      0x0002
#define MIL_STD_1553_SW1_NODE_FAULT                                     0x0004
#define MIL_STD_1553_SW1_NODE_BUSY                                      0x0008
#define MIL_STD_1553_SW1_GROUP_COMMAND_RECEIVED                         0x0010
// RESERVED                                                             0x00E0
#define MIL_STD_1553_SW1_SERVICE_REQUEST                                0x0100
#define MIL_STD_1553_SW1_TRANSMITTING_RESPONSE_WORD                     0x0200
#define MIL_STD_1553_SW1_MESSAGE_ERROR                                  0x0400
#define MIL_STD_1553_SW1_TERMINAL_DEIVICE_ADDRESS_Msk                   0xF800


#define MIL_STD_1553_SW1_TERMINAL_DEVICE_FAULT_Pos                      0
#define MIL_STD_1553_SW1_BUS_CONTROLLER_STATUS_TRANSITION_ACCEPTED_Pos  1
#define MIL_STD_1553_SW1_NODE_FAULT_Pos                                 2
#define MIL_STD_1553_SW1_NODE_BUSY_Pos                                  3
#define MIL_STD_1553_SW1_GROUP_COMMAND_RECEIVED_Pos                     4
// RESERVED                                                             5-7
#define MIL_STD_1553_SW1_SERVICE_REQUEST_Pos                            8
#define MIL_STD_1553_SW1_TRANSMITTING_RESPONSE_WORD_Pos                 9
#define MIL_STD_1553_SW1_MESSAGE_ERROR_Pos                              10
#define MIL_STD_1553_SW1_TERMINAL_DEIVICE_ADDRESS_Pos                   11











































/***************************************************************************************************************/
/***************************************************************************************************************/
/***************************************************************************************************************/
// Convertion :::: FILE MDR32F9Qx_eeprom.h /******************************DONE-100%*****************************/
/***************************************************************************************************************/
/***************************************************************************************************************/
/***************************************************************************************************************/

//
//
// EEPROM_Exported_Constants EEPROM Exported Constants
//
//

// EEPROM_Latency EEPROM Latency

#define EEPROM_Latency_0                ((uint32_t)0x00000000)  // EEPROM 0 Latency cycle  (MCU Clock up to  25 MHz)
#define EEPROM_Latency_1                ((uint32_t)0x00000008)  // EEPROM 1 Latency cycle  (MCU Clock up to  50 MHz)
#define EEPROM_Latency_2                ((uint32_t)0x00000010)  // EEPROM 2 Latency cycles (MCU Clock up to  75 MHz)
#define EEPROM_Latency_3                ((uint32_t)0x00000018)  // EEPROM 3 Latency cycles (MCU Clock up to 100 MHz)
#define EEPROM_Latency_4                ((uint32_t)0x00000020)  // EEPROM 4 Latency cycles (MCU Clock up to 125 MHz)
#define EEPROM_Latency_5                ((uint32_t)0x00000028)  // EEPROM 5 Latency cycles (MCU Clock up to 150 MHz)
#define EEPROM_Latency_6                ((uint32_t)0x00000030)  // EEPROM 6 Latency cycles (MCU Clock up to 175 MHz)
#define EEPROM_Latency_7                ((uint32_t)0x00000038)  // EEPROM 7 Latency cycles (MCU Clock up to 200 MHz)

#define EEPROM_Latency_MSK      ((uint32_t)0x00000038)

#define IS_EEPROM_LATENCY(EEPROM_Latency) (((EEPROM_Latency) & (~EEPROM_Latency_MSK)) == 0x0)

// End of group EEPROM_Latency

/***************************************************************************************************************/

// EEPROM_Bank EEPROM Bank Selector

#define EEPROM_Main_Bank_Select         ((uint32_t)0x00000000)  // EEPROM Main Bank Selector
#define EEPROM_Info_Bank_Select         ((uint32_t)0x00000001)  // EEPROM Information Bank Selector
#define EEPROM_All_Banks_Select         ((uint32_t)0x00000002)  // EEPROM All Banks Selector

#define IS_EEPROM_BANK_SELECTOR(SEL)    (((SEL) == EEPROM_Main_Bank_Select) || \
                                         ((SEL) == EEPROM_Info_Bank_Select))

#define IS_EEPROM_ERASE_SELECTOR(SEL)   (((SEL) == EEPROM_Main_Bank_Select) || \
                                         ((SEL) == EEPROM_All_Banks_Select))

// End of group EEPROM_Bank

//
//
//End of group EEPROM_Exported_Constants
//
//

// from eemrom c file

#define EEPROM_REG_ACCESS_KEY           ((uint32_t)0x8AAA5551)

#define IS_TWO_BYTE_ALLIGNED(ADDR)      ((ADDR & 1) == 0)
#define IS_FOUR_BYTE_ALLIGNED(ADDR)     ((ADDR & 3) == 0)

#define DELAY_LOOP_CYCLES               (8UL)
#define GET_US_LOOPS(N)                 ((uint32_t)((float)(N) * FLASH_PROG_FREQ_MHZ / DELAY_LOOP_CYCLES))





















































/***************************************************************************************************************/
/***************************************************************************************************************/
/***************************************************************************************************************/
// Convertion :::: FILE MDR32F9Qx_timer.h /******************************DONE-100%******************************/
/***************************************************************************************************************/
/***************************************************************************************************************/
/***************************************************************************************************************/

//
//
// TIMER_Exported_Types TIMER Exported Types
//
//

// TIMER Counter Init structure definition

typedef struct {

        uint32_t TIMER_IniCounter;      // Specifies the initial counter value. This parameter can be a number between 0x0000 and 0xFFFFFFFF.
        uint16_t TIMER_Prescaler;       // Specifies the prescaler value used to divide the TIMER clock. This parameter can be a number between 0x0000 and 0xFFFF. CLK = TIMER_CLK/(TIMER_Prescaler + 1)
        uint32_t TIMER_Period;          // Specifies the period value to be loaded into the Auto-Reload Register (ARR) at the next update event. This parameter must be a number between 0x0000 and 0xFFFFFFFF
        uint16_t TIMER_CounterMode;     // Specifies the counter mode. This parameter can be a value of @ref TIMER_Counter_Mode
        uint16_t TIMER_CounterDirection;// Specifies the counter direction. This parameter can be a value of @ref TIMER_Counter_Direction
        uint16_t TIMER_EventSource;     // Specifies the Counter Event source. This parameter can be a value of @ref TIMER_Event_Source
        uint16_t TIMER_FilterSampling;  // Specifies the filter sampling clock (FDTS). This parameter can be a value of @ref TIMER_Filter_Sampling
        uint16_t TIMER_ARR_UpdateMode;  // Specifies the Auto-Reload Register (ARR) updating mode. This parameter can be a value of @ref TIMER_ARR_Update_Mode
        uint16_t TIMER_ETR_FilterConf;  // Specifies the ETR Filter configuration. This parameter can be a value of @ref TIMER_FilterConfiguration
        uint16_t TIMER_ETR_Prescaler;   // Specifies the ETR Prescaler configuration. This parameter can be a value of @ref TIMER_ETR_Prescaler
        uint16_t TIMER_ETR_Polarity;    // Specifies the ETR Polarity configuration. This parameter can be a value of @ref TIMER_ETR_Polarity
        uint16_t TIMER_BRK_Polarity;    // Specifies the BRK Polarity configuration. This parameter can be a value of @ref TIMER_BRK_Polarity
} TIMER_CntInitTypeDef;

/***************************************************************************************************************/

// TIMER Channel Init structure definition
typedef struct
{
        uint16_t TIMER_CH_Number;               // Specifies the TIMER Channel number to be configured. This parameter can be a value of TIMER_CH_Number
        uint16_t TIMER_CH_Mode;                 // Specifies the TIMER Channel mode. This parameter can be a value of TIMER_CH_Mode
        uint16_t TIMER_CH_ETR_Ena;              // Enables or disables ETR. This parameter can be a value of FunctionalState
        uint16_t TIMER_CH_ETR_Reset;            // Enables or disables ETR Reset. This parameter can be a value of TIMER_CH_ETR_Reset
        uint16_t TIMER_CH_BRK_Reset;            // Enables or disables BRK Reset. This parameter can be a value of TIMER_CH_BRK_Reset
        uint16_t TIMER_CH_REF_Format;           // Specifies the REF signal format. This parameter can be a value of @ref TIMER_CH_REF_Format
        uint16_t TIMER_CH_Prescaler;            // Specifies the TIMER Channel Prescaler configuration. This parameter can be a value of TIMER_CH_Prescaler
        uint16_t TIMER_CH_EventSource;          // Specifies the Channel Event source. This parameter can be a value of TIMER_CH_EventSource
        uint16_t TIMER_CH_FilterConf;           // Specifies the TIMER Channel Filter configuration. This parameter can be a value of TIMER_FilterConfiguration
        uint16_t TIMER_CH_CCR_UpdateMode;       // Specifies the TIMER CCR, CCR1 update mode. This parameter can be a value of TIMER_CH_CCR_Update_Mode
        uint16_t TIMER_CH_CCR1_Ena;             // Enables or disables the CCR1 register. This parameter can be a value of FunctionalState
        uint16_t TIMER_CH_CCR1_EventSource;     // Specifies the Channel CCR1 Event source. This parameter can be a value of TIMER_CH_CCR1_EventSource
} TIMER_ChnInitTypeDef;

/***************************************************************************************************************/

// TIMER Channel Output Init structure definition
typedef struct
{
        uint16_t TIMER_CH_Number;               // Specifies the TIMER Channel number to be configured. This parameter can be a value of @ref TIMER_CH_Number
        uint16_t TIMER_CH_DirOut_Polarity;      // Specifies the TIMER CHx output polarity. This parameter can be a value of @ref TIMER_CH_OUT_Polarity
        uint16_t TIMER_CH_DirOut_Source;        // Specifies the TIMER CHx output source. This parameter can be a value of @ref TIMER_CH_OUT_Source
        uint16_t TIMER_CH_DirOut_Mode;          // Specifies the TIMER CHx output enable source. This parameter can be a value of @ref TIMER_CH_OUT_Mode
        uint16_t TIMER_CH_NegOut_Polarity;      // Enables or disables the TIMER CHxN output inversion. This parameter can be a value of @ref TIMER_CH_OUT_Polarity
        uint16_t TIMER_CH_NegOut_Source;        // Specifies the TIMER CHxN output source. This parameter can be a value of @ref TIMER_CH_OUT_Source
        uint16_t TIMER_CH_NegOut_Mode;          // Specifies the TIMER CHxN output enable source. This parameter can be a value of @ref TIMER_CH_OUT_Mode
        uint16_t TIMER_CH_DTG_MainPrescaler;    // Specifies the main prescaler of TIMER DTG. This parameter can be a number between 0x0000 and 0x00FF. Delay DTGdel = TIMER_CH_DTG_MainPrescaler*(TIMER_CH_DTG_AuxPrescaler + 1) clocks
        uint16_t TIMER_CH_DTG_AuxPrescaler;     // Specifies the auxiliary prescaler of TIMER DTG. This parameter can be a number between 0x0000 and 0x000F. Delay DTGdel = TIMER_CH_DTG_MainPrescaler*(TIMER_CH_DTG_AuxPrescaler + 1) clocks
        uint16_t TIMER_CH_DTG_ClockSource;      // Specifies the TIMER DTG clock source. This parameter can be a value of @ref TIMER_CH_DTG_Clock_Source
}TIMER_ChnOutInitTypeDef;

//
//
// End of group TIMER_Exported_Types
//
//

//
//
// TIMER_Exported_Constants TIMER Exported Constants
//
//

#define IS_TIMER_ALL_PERIPH(PERIPH) (((PERIPH) == MDR_TIMER1) || \
                                     ((PERIPH) == MDR_TIMER2) || \
                                     ((PERIPH) == MDR_TIMER3) || \
                                     ((PERIPH) == MDR_TIMER4))

/***************************************************************************************************************/

// TIMER_Counter_Mode TIMER Counter Mode
#define TIMER_CntMode_ClkFixedDir             (((uint32_t)0x0) << TIMER_CNTRL_CNT_MODE_Pos) // The Timer clock changes the TIMERx_CNT value. The count direction is not changed.
#define TIMER_CntMode_ClkChangeDir            (((uint32_t)0x1) << TIMER_CNTRL_CNT_MODE_Pos) // The Timer clock changes the TIMERx_CNT value. The count direction changes.
#define TIMER_CntMode_EvtFixedDir             (((uint32_t)0x2) << TIMER_CNTRL_CNT_MODE_Pos) // The event changes the TIMERx_CNT value. The count direction is not changed.
#define TIMER_CntMode_EvtChangeDir            (((uint32_t)0x3) << TIMER_CNTRL_CNT_MODE_Pos) // The event changes the TIMERx_CNT value. The count direction changes.

#define IS_TIMER_COUNTER_MODE(MODE) (((MODE) == TIMER_CntMode_ClkFixedDir ) || \
                                     ((MODE) == TIMER_CntMode_ClkChangeDir) || \
                                     ((MODE) == TIMER_CntMode_EvtFixedDir ) || \
                                     ((MODE) == TIMER_CntMode_EvtChangeDir))

// End of group TIMER_Counter_Mode

/***************************************************************************************************************/

// TIMER_Counter_Direction TIMER Counter Direction
#define TIMER_CntDir_Up                       (((uint32_t)0x0) << TIMER_CNTRL_DIR_Pos)  // Increments the Timer TIMERx_CNT counter value.
#define TIMER_CntDir_Dn                       (((uint32_t)0x1) << TIMER_CNTRL_DIR_Pos)  // Decrements the Timer TIMERx_CNT counter value.

#define IS_TIMER_COUNTER_DIR(DIR) (((DIR) == TIMER_CntDir_Up) || \
                                   ((DIR) == TIMER_CntDir_Dn))

// End of group TIMER_Counter_Direction

/***************************************************************************************************************/

// TIMER_Event_Source TIMER Event Source
#define TIMER_EvSrc_TM1                       (((uint32_t)0x1) << TIMER_CNTRL_EVENT_SEL_Pos)  // Selects TIMER1 (CNT == ARR) event.
#define TIMER_EvSrc_TM3                       (((uint32_t)0x3) << TIMER_CNTRL_EVENT_SEL_Pos)  // Selects TIMER3 (CNT == ARR) event.
#define TIMER_EvSrc_CH2                       (((uint32_t)0x5) << TIMER_CNTRL_EVENT_SEL_Pos)  // Selects Channel 2 event.
#define TIMER_EvSrc_CH4                       (((uint32_t)0x7) << TIMER_CNTRL_EVENT_SEL_Pos)  // Selects Channel 4 event.

#define IS_TIMER_EVENT_SOURCE(SOURCE) (((SOURCE) == TIMER_EvSrc_None) || \
                                       ((SOURCE) == TIMER_EvSrc_TM1 ) || \
                                       ((SOURCE) == TIMER_EvSrc_TM2 ) || \
                                       ((SOURCE) == TIMER_EvSrc_TM3 ) || \
                                       ((SOURCE) == TIMER_EvSrc_CH1 ) || \
                                       ((SOURCE) == TIMER_EvSrc_CH2 ) || \
                                       ((SOURCE) == TIMER_EvSrc_CH3 ) || \
                                       ((SOURCE) == TIMER_EvSrc_CH4 ) || \
                                       ((SOURCE) == TIMER_EvSrc_ETR ))

// End of group TIMER_Event_Source

/***************************************************************************************************************/

// TIMER_Filter_Sampling TIMER Filter Sampling Clock
#define TIMER_FDTS_TIMER_CLK_div_1              (((uint32_t)0x0) << TIMER_CNTRL_FDTS_Pos) // The FDTS clock occures each TIMER_CLK clock.
#define TIMER_FDTS_TIMER_CLK_div_2              (((uint32_t)0x1) << TIMER_CNTRL_FDTS_Pos) // The FDTS clock occures each 2-nd TIMER_CLK clock.
#define TIMER_FDTS_TIMER_CLK_div_3              (((uint32_t)0x2) << TIMER_CNTRL_FDTS_Pos) // The FDTS clock occures each 3-rd TIMER_CLK clock.
#define TIMER_FDTS_TIMER_CLK_div_4              (((uint32_t)0x3) << TIMER_CNTRL_FDTS_Pos) // The FDTS clock occures each 4-th TIMER_CLK clock.

#define IS_TIMER_FILTER_SAMPLING(CONFIG) (((CONFIG) == TIMER_FDTS_TIMER_CLK_div_1) || \
                                          ((CONFIG) == TIMER_FDTS_TIMER_CLK_div_2) || \
                                          ((CONFIG) == TIMER_FDTS_TIMER_CLK_div_3) || \
                                          ((CONFIG) == TIMER_FDTS_TIMER_CLK_div_4))

// End of group TIMER_Filter_Sampling

/***************************************************************************************************************/

// TIMER_ARR_Update_Mode TIMER ARR Update Mode
#define TIMER_ARR_Update_Immediately          (((uint32_t)0x0) << TIMER_CNTRL_ARRB_EN_Pos)  // The ARR register is updated immediately.
#define TIMER_ARR_Update_On_CNT_Overflow      (((uint32_t)0x1) << TIMER_CNTRL_ARRB_EN_Pos)  // The ARR register is updated at CNT count end.

#define IS_TIMER_ARR_UPDATE_MODE(MODE) (((MODE) == TIMER_ARR_Update_Immediately    ) || \
                                        ((MODE) == TIMER_ARR_Update_On_CNT_Overflow))

// End of group TIMER_ARR_UpdateMode

/***************************************************************************************************************/

// TIMER_FilterConfiguration TIMER Filter configuration
#define TIMER_Filter_1FF_at_TIMER_CLK         ((uint32_t)0x0)  // Signal is latched by 1 trigger  at TIMER_CLK clock frequency.
#define TIMER_Filter_2FF_at_TIMER_CLK         ((uint32_t)0x1)  // Signal is latched by 2 triggers at TIMER_CLK clock frequency.
#define TIMER_Filter_4FF_at_TIMER_CLK         ((uint32_t)0x2)  // Signal is latched by 4 triggers at TIMER_CLK clock frequency.
#define TIMER_Filter_8FF_at_TIMER_CLK         ((uint32_t)0x3)  // Signal is latched by 8 triggers at TIMER_CLK clock frequency.
#define TIMER_Filter_6FF_at_FTDS_div_2        ((uint32_t)0x4)  // Signal is latched by 6 triggers at FDTS/2  clock frequency.
#define TIMER_Filter_8FF_at_FTDS_div_2        ((uint32_t)0x5)  // Signal is latched by 8 triggers at FDTS/2  clock frequency.
#define TIMER_Filter_6FF_at_FTDS_div_4        ((uint32_t)0x6)  // Signal is latched by 6 triggers at FDTS/4  clock frequency.
#define TIMER_Filter_8FF_at_FTDS_div_4        ((uint32_t)0x7)  // Signal is latched by 8 triggers at FDTS/4  clock frequency.
#define TIMER_Filter_6FF_at_FTDS_div_8        ((uint32_t)0x8)  // Signal is latched by 6 triggers at FDTS/8  clock frequency.
#define TIMER_Filter_8FF_at_FTDS_div_8        ((uint32_t)0x9)  // Signal is latched by 8 triggers at FDTS/8  clock frequency.
#define TIMER_Filter_5FF_at_FTDS_div_16       ((uint32_t)0xA)  // Signal is latched by 5 triggers at FDTS/16 clock frequency.
#define TIMER_Filter_6FF_at_FTDS_div_16       ((uint32_t)0xB)  // Signal is latched by 6 triggers at FDTS/16 clock frequency.
#define TIMER_Filter_8FF_at_FTDS_div_16       ((uint32_t)0xC)  // Signal is latched by 8 triggers at FDTS/16 clock frequency.
#define TIMER_Filter_5FF_at_FTDS_div_32       ((uint32_t)0xD)  // Signal is latched by 5 triggers at FDTS/32 clock frequency.
#define TIMER_Filter_6FF_at_FTDS_div_32       ((uint32_t)0xE)  // Signal is latched by 6 triggers at FDTS/32 clock frequency.
#define TIMER_Filter_8FF_at_FTDS_div_32       ((uint32_t)0xF)  // Signal is latched by 8 triggers at FDTS/32 clock frequency.

#define IS_TIMER_FILTER_CONF(CONF) (((CONF) == TIMER_Filter_1FF_at_TIMER_CLK  ) || \
                                    ((CONF) == TIMER_Filter_2FF_at_TIMER_CLK  ) || \
                                    ((CONF) == TIMER_Filter_4FF_at_TIMER_CLK  ) || \
                                    ((CONF) == TIMER_Filter_8FF_at_TIMER_CLK  ) || \
                                    ((CONF) == TIMER_Filter_6FF_at_FTDS_div_2 ) || \
                                    ((CONF) == TIMER_Filter_8FF_at_FTDS_div_2 ) || \
                                    ((CONF) == TIMER_Filter_6FF_at_FTDS_div_4 ) || \
                                    ((CONF) == TIMER_Filter_8FF_at_FTDS_div_4 ) || \
                                    ((CONF) == TIMER_Filter_6FF_at_FTDS_div_8 ) || \
                                    ((CONF) == TIMER_Filter_8FF_at_FTDS_div_8 ) || \
                                    ((CONF) == TIMER_Filter_5FF_at_FTDS_div_16) || \
                                    ((CONF) == TIMER_Filter_6FF_at_FTDS_div_16) || \
                                    ((CONF) == TIMER_Filter_8FF_at_FTDS_div_16) || \
                                    ((CONF) == TIMER_Filter_5FF_at_FTDS_div_32) || \
                                    ((CONF) == TIMER_Filter_6FF_at_FTDS_div_32) || \
                                    ((CONF) == TIMER_Filter_8FF_at_FTDS_div_32))

// End of group TIMER_FilterConfiguration

/***************************************************************************************************************/

// TIMER_ETR_Prescaler TIMER ETR Prescaler
#define TIMER_ETR_Prescaler_None              (((uint32_t)0x0) << TIMER_BRKETR_CNTRL_ETR_PSC_Pos)  // No division of input frequency.
#define TIMER_ETR_Prescaler_div_2             (((uint32_t)0x1) << TIMER_BRKETR_CNTRL_ETR_PSC_Pos)  // Selects input frequency divider by 2.
#define TIMER_ETR_Prescaler_div_4             (((uint32_t)0x2) << TIMER_BRKETR_CNTRL_ETR_PSC_Pos)  // Selects input frequency divider by 4.
#define TIMER_ETR_Prescaler_div_8             (((uint32_t)0x3) << TIMER_BRKETR_CNTRL_ETR_PSC_Pos)  // Selects input frequency divider by 8.

#define IS_TIMER_ETR_PRESCALER(VALUE) (((VALUE) == TIMER_ETR_Prescaler_None ) || \
                                       ((VALUE) == TIMER_ETR_Prescaler_div_2) || \
                                       ((VALUE) == TIMER_ETR_Prescaler_div_4) || \
                                       ((VALUE) == TIMER_ETR_Prescaler_div_8))

// End of group TIMER_ETR_Prescaler

/***************************************************************************************************************/

// TIMER_ETR_Polarity TIMER ETR Polarity
#define TIMER_ETRPolarity_NonInverted         (((uint32_t)0x0) << TIMER_BRKETR_CNTRL_ETR_INV_Pos)  // No inversion of the ETR input.
#define TIMER_ETRPolarity_Inverted            (((uint32_t)0x1) << TIMER_BRKETR_CNTRL_ETR_INV_Pos)  // The ETR input is inverted.

#define IS_TIMER_ETR_POLARITY(STATE) (((STATE) == TIMER_ETRPolarity_NonInverted) || \
                                      ((STATE) == TIMER_ETRPolarity_Inverted   ))

// End of group TIMER_ETR_Polarity

/***************************************************************************************************************/

// TIMER_BRK_Polarity TIMER BRK Polarity
#define TIMER_BRKPolarity_NonInverted         (((uint32_t)0x0) << TIMER_BRKETR_CNTRL_BRK_INV_Pos)  // No inversion of the BRK input.
#define TIMER_BRKPolarity_Inverted            (((uint32_t)0x1) << TIMER_BRKETR_CNTRL_BRK_INV_Pos)  // The BRK input is inverted.

#define IS_TIMER_BRK_POLARITY(STATE) (((STATE) == TIMER_BRKPolarity_NonInverted) || \
                                      ((STATE) == TIMER_BRKPolarity_Inverted   ))

// End of group TIMER_BRK_Polarity

/***************************************************************************************************************/

// TIMER_CH_Number TIMER Channel Number
#define TIMER_CHANNEL1                        ((uint32_t)0x0)  // Specifies the TIMER channel 1.
#define TIMER_CHANNEL2                        ((uint32_t)0x1)  // Specifies the TIMER channel 2.
#define TIMER_CHANNEL3                        ((uint32_t)0x2)  // Specifies the TIMER channel 3.
#define TIMER_CHANNEL4                        ((uint32_t)0x3)  // Specifies the TIMER channel 4.

#define IS_TIMER_CHANNEL_NUMBER(NUMBER) (((NUMBER) == TIMER_CHANNEL1) || \
                                         ((NUMBER) == TIMER_CHANNEL2) || \
                                         ((NUMBER) == TIMER_CHANNEL3) || \
                                         ((NUMBER) == TIMER_CHANNEL4))

// End of group TIMER_CH_Number

/***************************************************************************************************************/

// TIMER_CH_ETR_Reset TIMER Channel ETR Reset configuration
#define TIMER_CH_ETR_RESET_Disable            (((uint32_t)0x0) << TIMER_CH_CNTRL_ETREN_Pos)  // Disables ETR Reset.
#define TIMER_CH_ETR_RESET_Enable             (((uint32_t)0x1) << TIMER_CH_CNTRL_ETREN_Pos)  // Enables ETR Reset.

#define IS_TIMER_CHANNEL_ETR_RESET_CONFIG(CONFIG) (((CONFIG) == TIMER_CH_ETR_RESET_Disable) || \
                                                   ((CONFIG) == TIMER_CH_ETR_RESET_Enable ))

// End of group TIMER_CH_ETR_Reset

/***************************************************************************************************************/

// TIMER_CH_BRK_Reset TIMER Channel BRK Reset configuration
#define TIMER_CH_BRK_RESET_Disable            (((uint32_t)0x0) << TIMER_CH_CNTRL_BRKEN_Pos)   // Disables BRK Reset.
#define TIMER_CH_BRK_RESET_Enable             (((uint32_t)0x1) << TIMER_CH_CNTRL_BRKEN_Pos)   // Enables BRK Reset. /

#define IS_TIMER_CHANNEL_BRK_RESET_CONFIG(CONFIG) (((CONFIG) == TIMER_CH_BRK_RESET_Disable) || \
                                                   ((CONFIG) == TIMER_CH_BRK_RESET_Enable ))

// End of group TIMER_CH_BRK_Reset

/***************************************************************************************************************/

// TIMER_CH_Mode TIMER Channel Mode
#define TIMER_CH_MODE_PWM                     (((uint32_t)0x0) << TIMER_CH_CNTRL_CAP_NPWM_Pos)  // Specifies the PWM channel mode.
#define TIMER_CH_MODE_CAPTURE                 (((uint32_t)0x1) << TIMER_CH_CNTRL_CAP_NPWM_Pos)  // Specifies the Capture channel mode.
#define IS_TIMER_CHANNEL_MODE(MODE) (((MODE) == TIMER_CH_MODE_PWM    ) || \
                                     ((MODE) == TIMER_CH_MODE_CAPTURE))
// End of group TIMER_CH_Mode

/***************************************************************************************************************/

// TIMER_CH_REF_Format TIMER Channel REF Format
#define TIMER_CH_REF_Format0                  (((uint32_t)0x0) << TIMER_CH_CNTRL_OCCM_Pos)  // REF is equal to 0
#define TIMER_CH_REF_Format1                  (((uint32_t)0x1) << TIMER_CH_CNTRL_OCCM_Pos)  // REF is equal to 1 if: (CNT == CCR) or ((CNT == CCR1) and CCR1 enabled), else REF is equal to 0.
#define TIMER_CH_REF_Format2                  (((uint32_t)0x2) << TIMER_CH_CNTRL_OCCM_Pos)  // REF is equal to 0 if: (CNT == CCR) or ((CNT == CCR1) and CCR1 enabled), else REF is equal to 1.
#define TIMER_CH_REF_Format3                  (((uint32_t)0x3) << TIMER_CH_CNTRL_OCCM_Pos)  // Toggle REF state if:  (CNT == CCR) or ((CNT == CCR1) and CCR1 enabled).
#define TIMER_CH_REF_Format4                  (((uint32_t)0x4) << TIMER_CH_CNTRL_OCCM_Pos)  // REF is equal to 0.
#define TIMER_CH_REF_Format5                  (((uint32_t)0x5) << TIMER_CH_CNTRL_OCCM_Pos)  // REF is equal to 1.
#define TIMER_CH_REF_Format6                  (((uint32_t)0x6) << TIMER_CH_CNTRL_OCCM_Pos)  // REF is equal to inverted DIR state if: (CCR1 disabled and (CNT < CCR)) or (CCR1 enabled  and (CCR1 < CNT < CCR)), else REF is equal to DIR state.
#define TIMER_CH_REF_Format7                  (((uint32_t)0x7) << TIMER_CH_CNTRL_OCCM_Pos)  // REF is equal to DIR state if: (CCR1 disabled and (CNT < CCR)) or (CCR1 enabled  and (CCR1 < CNT < CCR)), else REF is equal to inverted DIR state.

#define IS_TIMER_CHANNEL_REF_FORMAT(FORMAT) (((FORMAT) == TIMER_CH_REF_Format0) || \
                                             ((FORMAT) == TIMER_CH_REF_Format1) || \
                                             ((FORMAT) == TIMER_CH_REF_Format2) || \
                                             ((FORMAT) == TIMER_CH_REF_Format3) || \
                                             ((FORMAT) == TIMER_CH_REF_Format4) || \
                                             ((FORMAT) == TIMER_CH_REF_Format5) || \
                                             ((FORMAT) == TIMER_CH_REF_Format6) || \
                                             ((FORMAT) == TIMER_CH_REF_Format7))

// End of group TIMER_CH_REF_Format

/***************************************************************************************************************/

// TIMER_CH_Prescaler TIMER Channel Prescaler
#define TIMER_CH_Prescaler_None               ((uint32_t)0x0) // No division of input frequency.
#define TIMER_CH_Prescaler_div_2              ((uint32_t)0x1) // Selects input frequency divider by 2.
#define TIMER_CH_Prescaler_div_4              ((uint32_t)0x2) // Selects input frequency divider by 4.
#define TIMER_CH_Prescaler_div_8              ((uint32_t)0x3) // Selects input frequency divider by 8.

#define IS_TIMER_CHANNEL_PRESCALER(VALUE) (((VALUE) == TIMER_CH_Prescaler_None ) || \
                                           ((VALUE) == TIMER_CH_Prescaler_div_2) || \
                                           ((VALUE) == TIMER_CH_Prescaler_div_4) || \
                                           ((VALUE) == TIMER_CH_Prescaler_div_8))

// End of group TIMER_CH_Prescaler

// TIMER_CH_EventSource TIMER Channel Event Source
#define TIMER_CH_EvSrc_PE                     (((uint32_t)0x0) << TIMER_CH_CNTRL_CHSEL_Pos)  // Selects positive edge from current TIMER channel.
#define TIMER_CH_EvSrc_NE                     (((uint32_t)0x1) << TIMER_CH_CNTRL_CHSEL_Pos)  // Selects negative edge from current TIMER channel.
#define TIMER_CH_EvSrc_PE_OC1                 (((uint32_t)0x2) << TIMER_CH_CNTRL_CHSEL_Pos)  // Selects positive edge from other TIMER channel (variant 1).
#define TIMER_CH_EvSrc_PE_OC2                 (((uint32_t)0x3) << TIMER_CH_CNTRL_CHSEL_Pos)  // Selects positive edge from other TIMER channel (variant 2).

#define IS_TIMER_CHANNEL_EVENT_SOURCE(SOURCE) (((SOURCE) == TIMER_CH_EvSrc_PE    ) || \
                                               ((SOURCE) == TIMER_CH_EvSrc_NE    ) || \
                                               ((SOURCE) == TIMER_CH_EvSrc_PE_OC1) || \
                                               ((SOURCE) == TIMER_CH_EvSrc_PE_OC2))

// End of group TIMER_CH_EventSource

/***************************************************************************************************************/

// TIMER_CH_CCR1_EventSource TIMER Channel CCR1 Event Source
#define TIMER_CH_CCR1EvSrc_PE                 (((uint32_t)0x0) << TIMER_CH_CNTRL2_CHSEL1_Pos) // Selects positive edge from current TIMER channel.
#define TIMER_CH_CCR1EvSrc_NE                 (((uint32_t)0x1) << TIMER_CH_CNTRL2_CHSEL1_Pos) // Selects negative edge from current TIMER channel.
#define TIMER_CH_CCR1EvSrc_NE_OC1             (((uint32_t)0x2) << TIMER_CH_CNTRL2_CHSEL1_Pos) // Selects negative edge from other TIMER channel (variant 1).
#define TIMER_CH_CCR1EvSrc_NE_OC2             (((uint32_t)0x3) << TIMER_CH_CNTRL2_CHSEL1_Pos) // Selects negative edge from other TIMER channel (variant 2).

#define IS_TIMER_CHANNEL_CCR1_EVENT_SOURCE(SOURCE) (((SOURCE) == TIMER_CH_CCR1EvSrc_PE    ) || \
                                                    ((SOURCE) == TIMER_CH_CCR1EvSrc_NE    ) || \
                                                    ((SOURCE) == TIMER_CH_CCR1EvSrc_NE_OC1) || \
                                                    ((SOURCE) == TIMER_CH_CCR1EvSrc_NE_OC2))

// End of group TIMER_CH_CCR1_EventSource

/***************************************************************************************************************/

// TIMER_CH_CCR_Update_Mode TIMER CCR, CCR1 Update mode
#define TIMER_CH_CCR_Update_Immediately       (((uint32_t)0x0) << TIMER_CH_CNTRL2_CCRRLD_Pos)  // The CCR, CCR1 registers is updated immediately.
#define TIMER_CH_CCR_Update_On_CNT_eq_0       (((uint32_t)0x1) << TIMER_CH_CNTRL2_CCRRLD_Pos)  // The CCR, CCR1 registers is updated at (CNT == 0) condition.

#define IS_TIMER_CHANNEL_CCR_UPDATE_MODE(MODE) (((MODE) == TIMER_CH_CCR_Update_Immediately) || \
                                                ((MODE) == TIMER_CH_CCR_Update_On_CNT_eq_0))

// End of group TIMER_CH_CCR_UpdateMode

/***************************************************************************************************************/

// TIMER_CH_OUT_Polarity TIMER Channel Output Polarity
#define TIMER_CHOPolarity_NonInverted         ((uint32_t)0x0)   // No inversion on the Channel output.
#define TIMER_CHOPolarity_Inverted            ((uint32_t)0x1)   // The Channel output is inverted.

#define IS_TIMER_CHO_POLARITY(STATE) (((STATE) == TIMER_CHOPolarity_NonInverted) || \
                                      ((STATE) == TIMER_CHOPolarity_Inverted   ))

// End of group TIMER_CH_OUT_Polarity

/***************************************************************************************************************/

// TIMER_CH_OUT_Source TIMER Channel Output Source
#define TIMER_CH_OutSrc_Only_0                ((uint32_t)0x0)   // Selects the '0' state on the CHx (or CHxN) line.
#define TIMER_CH_OutSrc_Only_1                ((uint32_t)0x1)   // Selects the '1' state on the CHx (or CHxN) line.
#define TIMER_CH_OutSrc_REF                   ((uint32_t)0x2)   // Selects the REF state on the CHx (or CHxN) line.
#define TIMER_CH_OutSrc_DTG                   ((uint32_t)0x3)   // Selects the DTG output state on the CHx (or CHxN) line.

#define IS_TIMER_CHO_SOURCE(SOURCE) (((SOURCE) == TIMER_CH_OutSrc_Only_0) || \
                                     ((SOURCE) == TIMER_CH_OutSrc_Only_1) || \
                                     ((SOURCE) == TIMER_CH_OutSrc_REF   ) || \
                                     ((SOURCE) == TIMER_CH_OutSrc_DTG   ))

// End of group TIMER_CH_OUT_Source

/***************************************************************************************************************/

// TIMER_CH_OUT_Mode TIMER Channel Output Enable Source
#define TIMER_CH_OutMode_Input                ((uint32_t)0x0)   // Selects the Input mode on the CHx (or CHxN) line.
#define TIMER_CH_OutMode_Output               ((uint32_t)0x1)   // Selects the Output mode on the CHx (or CHxN) line.
#define TIMER_CH_OutMode_REF_as_OE            ((uint32_t)0x2)   // The REF signal specifies the CHx (or CHxN) line mode.
#define TIMER_CH_OutMode_DTG_as_OE            ((uint32_t)0x3)   // The DTG output specifies the CHx (or CHxN) line mode.

#define IS_TIMER_CHO_MODE(MODE) (((MODE) == TIMER_CH_OutMode_Input    ) || \
                                 ((MODE) == TIMER_CH_OutMode_Output   ) || \
                                 ((MODE) == TIMER_CH_OutMode_REF_as_OE) || \
                                 ((MODE) == TIMER_CH_OutMode_DTG_as_OE))

// End of group TIMER_CH_OUT_Mode

/***************************************************************************************************************/

// TIMER_CH_DTG_Prescaler TIMER Channel DTG Prescaler
#define IS_TIMER_CHANNEL_DTG_MAIN_PRESCALER(VALUE) (((VALUE) >> 8) == 0)

#define IS_TIMER_CHANNEL_DTG_AUX_PRESCALER(VALUE) (((VALUE) >> 4) == 0)

// End of group TIMER_CH_DTG_Prescaler

/***************************************************************************************************************/

// TIMER_CH_DTG_Clock_Source TIMER Channel DTG Clock Source
#define TIMER_CH_DTG_ClkSrc_TIMER_CLK         (((uint32_t)0x0) << TIMER_CH_DTG_EDTS_Pos)  // Specifies the TIMER_CLK signal as DTG clock source.
#define TIMER_CH_DTG_ClkSrc_FDTS              (((uint32_t)0x1) << TIMER_CH_DTG_EDTS_Pos)  // Specifies the FDTS signal as DTG clock source.

#define IS_TIMER_CHANNEL_DTG_CLK_SOURCE(SOURCE) (((SOURCE) == TIMER_CH_DTG_ClkSrc_TIMER_CLK) || \
                                                 ((SOURCE) == TIMER_CH_DTG_ClkSrc_FDTS     ))

// End of group TIMER_CH_DTG_Clock_Source

/***************************************************************************************************************/

// TIMER_StatusFlags TIMER Status flags
#define TIMER_STATUS_CNT_ZERO                 (((uint32_t)0x1) <<  0) // The (CNT == 0) condition occured.
#define TIMER_STATUS_CNT_ARR                  (((uint32_t)0x1) <<  1) // The (CNT == ARR) condition occured.
#define TIMER_STATUS_ETR_RISING_EDGE          (((uint32_t)0x1) <<  2) // The ETR rising edge occured.
#define TIMER_STATUS_ETR_FALLING_EDGE         (((uint32_t)0x1) <<  3) // The ETR falling edge occured.
#define TIMER_STATUS_BRK                      (((uint32_t)0x1) <<  4) // The (BRK == 1) condition occured.
#define TIMER_STATUS_CCR_CAP_CH1              (((uint32_t)0x1) <<  5) // The Channel 1 CCR capture condition occured.
#define TIMER_STATUS_CCR_CAP_CH2              (((uint32_t)0x1) <<  6) // The Channel 2 CCR capture condition occured.
#define TIMER_STATUS_CCR_CAP_CH3              (((uint32_t)0x1) <<  7) // The Channel 3 CCR capture condition occured.
#define TIMER_STATUS_CCR_CAP_CH4              (((uint32_t)0x1) <<  8) // The Channel 4 CCR capture condition occured.
#define TIMER_STATUS_CCR_REF_CH1              (((uint32_t)0x1) <<  9) // The Channel 1 (REF == 1) condition occured.
#define TIMER_STATUS_CCR_REF_CH2              (((uint32_t)0x1) << 10) // The Channel 2 (REF == 1) condition occured.
#define TIMER_STATUS_CCR_REF_CH3              (((uint32_t)0x1) << 11) // The Channel 3 (REF == 1) condition occured.
#define TIMER_STATUS_CCR_REF_CH4              (((uint32_t)0x1) << 12) // The Channel 4 (REF == 1) condition occured.
#define TIMER_STATUS_CCR_CAP1_CH1             (((uint32_t)0x1) << 13) // The Channel 1 CCR1 capture condition occured.
#define TIMER_STATUS_CCR_CAP1_CH2             (((uint32_t)0x1) << 14) // The Channel 2 CCR1 capture condition occured.
#define TIMER_STATUS_CCR_CAP1_CH3             (((uint32_t)0x1) << 15) // The Channel 3 CCR1 capture condition occured.
#define TIMER_STATUS_CCR_CAP1_CH4             (((uint32_t)0x1) << 16) // The Channel 4 CCR1 capture condition occured.

#define TIMER_STATUS_Msk                      (TIMER_STATUS_CNT_ZERO         | \
                                               TIMER_STATUS_CNT_ARR          | \
                                               TIMER_STATUS_ETR_RISING_EDGE  | \
                                               TIMER_STATUS_ETR_FALLING_EDGE | \
                                               TIMER_STATUS_BRK              | \
                                               TIMER_STATUS_CCR_CAP_CH1      | \
                                               TIMER_STATUS_CCR_CAP_CH2      | \
                                               TIMER_STATUS_CCR_CAP_CH3      | \
                                               TIMER_STATUS_CCR_CAP_CH4      | \
                                               TIMER_STATUS_CCR_REF_CH1      | \
                                               TIMER_STATUS_CCR_REF_CH2      | \
                                               TIMER_STATUS_CCR_REF_CH3      | \
                                               TIMER_STATUS_CCR_REF_CH4      | \
                                               TIMER_STATUS_CCR_CAP1_CH1     | \
                                               TIMER_STATUS_CCR_CAP1_CH2     | \
                                               TIMER_STATUS_CCR_CAP1_CH3     | \
                                               TIMER_STATUS_CCR_CAP1_CH4)

#define IS_TIMER_STATUS_FLAG(FLAG) (((FLAG) == TIMER_STATUS_CNT_ZERO        ) || \
                                    ((FLAG) == TIMER_STATUS_CNT_ARR         ) || \
                                    ((FLAG) == TIMER_STATUS_ETR_RISING_EDGE ) || \
                                    ((FLAG) == TIMER_STATUS_ETR_FALLING_EDGE) || \
                                    ((FLAG) == TIMER_STATUS_BRK             ) || \
                                    ((FLAG) == TIMER_STATUS_CCR_CAP_CH1     ) || \
                                    ((FLAG) == TIMER_STATUS_CCR_CAP_CH2     ) || \
                                    ((FLAG) == TIMER_STATUS_CCR_CAP_CH3     ) || \
                                    ((FLAG) == TIMER_STATUS_CCR_CAP_CH4     ) || \
                                    ((FLAG) == TIMER_STATUS_CCR_REF_CH1     ) || \
                                    ((FLAG) == TIMER_STATUS_CCR_REF_CH2     ) || \
                                    ((FLAG) == TIMER_STATUS_CCR_REF_CH3     ) || \
                                    ((FLAG) == TIMER_STATUS_CCR_REF_CH4     ) || \
                                    ((FLAG) == TIMER_STATUS_CCR_CAP1_CH1    ) || \
                                    ((FLAG) == TIMER_STATUS_CCR_CAP1_CH2    ) || \
                                    ((FLAG) == TIMER_STATUS_CCR_CAP1_CH3    ) || \
                                    ((FLAG) == TIMER_STATUS_CCR_CAP1_CH4    ))

#define IS_TIMER_STATUS(STATUS) (((STATUS) & TIMER_STATUS_Msk) == (STATUS))

// End of group TIMER_StatusFlags

/***************************************************************************************************************/

// TIMER_DMAChannels TIMER DMAChannels
#define TIMER_DMA_Channel0                                      ((uint32_t)0x00000004)
#define TIMER_DMA_Channel1                                      ((uint32_t)0x00000000)
#define TIMER_DMA_Channel2                                      ((uint32_t)0x00000001)
#define TIMER_DMA_Channel3                                      ((uint32_t)0x00000002)
#define TIMER_DMA_Channel4                                      ((uint32_t)0x00000003)

#define IS_TIMER_DMA_Channel(DMA_Channel)       ((DMA_Channel == TIMER_DMA_Channel0) ||\
                                                 (DMA_CHannel == TIMER_DMA_Channel1) ||\
                                                 (DMA_CHannel == TIMER_DMA_Channel2) ||\
                                                 (DMA_CHannel == TIMER_DMA_Channel3) ||\
                                                 (DMA_CHannel == TIMER_DMA_Channel4))

// End of group TIMER_DMAChannels

/***************************************************************************************************************/

// TIMER_Clock_BRG TIMER Clock BRG
#define TIMER_HCLKdiv1                        ((uint32_t)0x0)
#define TIMER_HCLKdiv2                        ((uint32_t)0x1)
#define TIMER_HCLKdiv4                        ((uint32_t)0x2)
#define TIMER_HCLKdiv8                        ((uint32_t)0x3)
#define TIMER_HCLKdiv16                       ((uint32_t)0x4)
#define TIMER_HCLKdiv32                       ((uint32_t)0x5)
#define TIMER_HCLKdiv64                       ((uint32_t)0x6)
#define TIMER_HCLKdiv128                      ((uint32_t)0x7)

#define IS_TIMER_CLOCK_BRG(BRG) (((BRG) == TIMER_HCLKdiv1  ) || \
                                 ((BRG) == TIMER_HCLKdiv2  ) || \
                                 ((BRG) == TIMER_HCLKdiv4  ) || \
                                 ((BRG) == TIMER_HCLKdiv8  ) || \
                                 ((BRG) == TIMER_HCLKdiv16 ) || \
                                 ((BRG) == TIMER_HCLKdiv32 ) || \
                                 ((BRG) == TIMER_HCLKdiv64 ) || \
                                 ((BRG) == TIMER_HCLKdiv128))

// End of group TIMER_Clock_BRG

//
//
// End of group TIMER_Exported_Constants
//
//


































/***************************************************************************************************************/
/***************************************************************************************************************/
/***************************************************************************************************************/
// Convertion :::: FILE MDR32F9Qx_uart.h /******************************DONE-100%*******************************/
/***************************************************************************************************************/
/***************************************************************************************************************/
/***************************************************************************************************************/

//
//
// UART_Exported_Types UART Exported Types
//
//

typedef enum {BaudRateInvalid = 0, BaudRateValid = !BaudRateInvalid} BaudRateStatus;

/***************************************************************************************************************/

// UART Init Structure definition
typedef struct
{
  uint32_t UART_BaudRate;            // This member configures the UART communication baud rate. The baud rate is computed using the following formula:
                                     //      - IntegerDivider = ((UARTCLK) / (16 * (UART_InitStruct->UART_BaudRate)))
                                     //      - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 64) + 0.5
  uint16_t UART_WordLength;          // Specifies the number of data bits transmitted or received in a frame. This parameter is one of @ref UART_Word_Length values.
  uint16_t UART_StopBits;            // Specifies the number of stop bits transmitted. This parameter is one of @ref UART_Stop_Bits values.
  uint16_t UART_Parity;              // Specifies the parity mode. This parameter is one of @ref UART_Parity values.
  uint16_t UART_FIFOMode;            // Specifies the FIFO mode. This parameter is one of @ref UART_FIFO_Mode values.
  uint16_t UART_HardwareFlowControl; // Specifies whether the hardware flow control mode is enabled or disabled. This parameter is one of @ref UART_Hardware_Flow_Control values.
}UART_InitTypeDef;

//
//
// End of group UART_Exported_Types
//
//

//
//
// UART_Exported_Constants UART Exported Constants
//
//

// UART_Word_Length UART Word Length
#define UART_WordLength5b                   ((uint16_t)0x0000)
#define UART_WordLength6b                   ((uint16_t)0x0020)
#define UART_WordLength7b                   ((uint16_t)0x0040)
#define UART_WordLength8b                   ((uint16_t)0x0060)

#define IS_UART_WORD_LENGTH(LENGTH)         (((LENGTH) == UART_WordLength5b) || \
                                             ((LENGTH) == UART_WordLength6b) || \
                                             ((LENGTH) == UART_WordLength7b) || \
                                             ((LENGTH) == UART_WordLength8b))

// End of group UART_Word_Length

/***************************************************************************************************************/

// UART_Stop_Bits UART Stop Bits
#define UART_StopBits1                      ((uint16_t)0x0000)
#define UART_StopBits2                      ((uint16_t)0x0008)

#define IS_UART_STOPBITS(STOPBITS)          (((STOPBITS) == UART_StopBits1) || \
                                             ((STOPBITS) == UART_StopBits2))

// End of group UART_Stop_Bits

/***************************************************************************************************************/

// UART_Parity UART Parity
#define UART_Parity_No                      ((uint16_t)0x0000)
#define UART_Parity_Even                    ((uint16_t)0x0006)
#define UART_Parity_Odd                     ((uint16_t)0x0002)
#define UART_Parity_1                       ((uint16_t)0x0082)
#define UART_Parity_0                       ((uint16_t)0x0086)

#define IS_UART_PARITY(PARITY)              (((PARITY) == UART_Parity_No)   || \
                                             ((PARITY) == UART_Parity_Even) || \
                                             ((PARITY) == UART_Parity_Odd)  || \
                                             ((PARITY) == UART_Parity_1)    || \
                                             ((PARITY) == UART_Parity_0))

// End of group UART_Parity

/***************************************************************************************************************/

// UART_FIFO_Mode UART FIFO Mode
#define UART_FIFO_OFF                       ((uint16_t)0x0000)
#define UART_FIFO_ON                        ((uint16_t)0x0010)

#define IS_UART_FIFOMODE(FIFOMODE)          (((FIFOMODE) == UART_FIFO_ON) || \
                                             ((FIFOMODE) == UART_FIFO_OFF))

// End of group UART_FIFO_Mode

/***************************************************************************************************************/

//UART_Hardware_Flow_Control UART Hardware Flow Control
#define UART_HardwareFlowControl_None       ((uint16_t)0x0000)
#define UART_HardwareFlowControl_CTSEn      ((uint16_t)0x8000)
#define UART_HardwareFlowControl_RTSEn      ((uint16_t)0x4000)
#define UART_HardwareFlowControl_Out2       ((uint16_t)0x2000)
#define UART_HardwareFlowControl_Out1       ((uint16_t)0x1000)
#define UART_HardwareFlowControl_RTS        ((uint16_t)0x0800)
#define UART_HardwareFlowControl_DTR        ((uint16_t)0x0400)
#define UART_HardwareFlowControl_RXE        ((uint16_t)0x0200)
#define UART_HardwareFlowControl_TXE        ((uint16_t)0x0100)
#define UART_HardwareFlowControl_LBE        ((uint16_t)0x0080)

#define UART_HARDWARE_FLOW_CONTROL_MASK         ((uint16_t)0xFF80)

#define IS_UART_HARDWARE_FLOW_CONTROL(CONTROL)          ((CONTROL&(~(UART_HARDWARE_FLOW_CONTROL_MASK))) == 0)

// End of group UART_Hardware_Flow_Control

/***************************************************************************************************************/

// UART_Interrupt_definition UART Interrupt definition
#define UART_IT_OE                          ((uint32_t)0x00000400)
#define UART_IT_BE                          ((uint32_t)0x00000200)
#define UART_IT_PE                          ((uint32_t)0x00000100)
#define UART_IT_FE                          ((uint32_t)0x00000080)
#define UART_IT_RT                          ((uint32_t)0x00000040)
#define UART_IT_TX                          ((uint32_t)0x00000020)
#define UART_IT_RX                          ((uint32_t)0x00000010)
#define UART_IT_DSR                         ((uint32_t)0x00000008)
#define UART_IT_DCD                         ((uint32_t)0x00000004)
#define UART_IT_CTS                         ((uint32_t)0x00000002)
#define UART_IT_RI                          ((uint32_t)0x00000001)

#define IS_UART_CONFIG_IT(IT)               (((IT) == UART_IT_OE)  || ((IT) == UART_IT_BE)  || \
                                             ((IT) == UART_IT_PE)  || ((IT) == UART_IT_FE)  || \
                                             ((IT) == UART_IT_RT)  || ((IT) == UART_IT_TX)  || \
                                             ((IT) == UART_IT_RX)  || ((IT) == UART_IT_DSR) || \
                                             ((IT) == UART_IT_DCD) || ((IT) == UART_IT_CTS) || \
                                             ((IT) == UART_IT_RI))

// End of group UART_Interrupt_definition

/***************************************************************************************************************/

// UART_DMA_interrupt_definition UART DMA interrupt definition
#define UART_IT_FIFO_LVL_2words             ((uint32_t)0x00000000)
#define UART_IT_FIFO_LVL_4words             ((uint32_t)0x00000001)
#define UART_IT_FIFO_LVL_8words             ((uint32_t)0x00000002)
#define UART_IT_FIFO_LVL_12words            ((uint32_t)0x00000003)
#define UART_IT_FIFO_LVL_14words            ((uint32_t)0x00000004)

#define IS_UART_IT_FIFO_LVL(IT_FIFO_LVL)    (((IT_FIFO_LVL) == UART_IT_FIFO_LVL_2words) || \
                                             ((IT_FIFO_LVL) == UART_IT_FIFO_LVL_4words) || \
                                             ((IT_FIFO_LVL) == UART_IT_FIFO_LVL_8words) || \
                                             ((IT_FIFO_LVL) == UART_IT_FIFO_LVL_12words) || \
                                             ((IT_FIFO_LVL) == UART_IT_FIFO_LVL_14words))

// End of group UART_DMA_interrupt_definition

/***************************************************************************************************************/

// UART_DMA_request UART DMA request
#define UART_DMA_RXE                        ((uint32_t)0x00000001)
#define UART_DMA_TXE                        ((uint32_t)0x00000002)
#define UART_DMA_ONERR                      ((uint32_t)0x00000004)

#define IS_UART_DMAREQ(DMAREQ)              (((DMAREQ) == UART_DMA_RXE) || \
                                             ((DMAREQ) == UART_DMA_TXE) || \
                                             ((DMAREQ) == UART_DMA_ONERR))

// End of group UART_DMA_request

/***************************************************************************************************************/

// UART_IrDA_Low_Power UART IrDA Low Power
#define UART_IrDAMode_LowPower              ((uint32_t)0x00000004)
#define UART_IrDAMode_Normal                ((uint32_t)0x00000000)

#define IS_UART_IRDA_MODE(MODE)             (((MODE) == UART_IrDAMode_LowPower) || \
                                             ((MODE) == UART_IrDAMode_Normal))

// End of group UART_IrDA_Low_Power

/***************************************************************************************************************/

// UART_Flags UART Flags
#define UART_FLAG_RI                        ((uint32_t)0x00000100)
#define UART_FLAG_TXFE                      ((uint32_t)0x00000080)
#define UART_FLAG_RXFF                      ((uint32_t)0x00000040)
#define UART_FLAG_TXFF                      ((uint32_t)0x00000020)
#define UART_FLAG_RXFE                      ((uint32_t)0x00000010)
#define UART_FLAG_BUSY                      ((uint32_t)0x00000008)
#define UART_FLAG_DCD                       ((uint32_t)0x00000004)
#define UART_FLAG_DSR                       ((uint32_t)0x00000002)
#define UART_FLAG_CTS                       ((uint32_t)0x00000001)

#define IS_UART_FLAG(FLAG)                  (((FLAG) == UART_FLAG_RI)   || ((FLAG) == UART_FLAG_TXFE) || \
                                             ((FLAG) == UART_FLAG_RXFF) || ((FLAG) == UART_FLAG_TXFF) || \
                                             ((FLAG) == UART_FLAG_RXFE) || ((FLAG) == UART_FLAG_BUSY) || \
                                             ((FLAG) == UART_FLAG_DCD)  || ((FLAG) == UART_FLAG_DSR)  || \
                                             ((FLAG) == UART_FLAG_CTS))

#define IS_UART_BAUDRATE(BAUDRATE) (((BAUDRATE) > 0) && ((BAUDRATE) <= 921600))

// End of group UART_Flags

/***************************************************************************************************************/

// UART_Data_Status UART Data Status
#define UART_Data_OE                        0x0B
#define UART_Data_BE                        0x0A
#define UART_Data_PE                        0x09
#define UART_Data_FE                        0x08

#define UART_Data_OE_Msk                    ((uint32_t)(1 << UART_Data_OE))
#define UART_Data_BE_Msk                    ((uint32_t)(1 << UART_Data_BE))
#define UART_Data_PE_Msk                    ((uint32_t)(1 << UART_Data_FE))
#define UART_Data_FE_Msk                    ((uint32_t)(1 << UART_Data_PE))

#define UART_Data(DATA)                     ((uint8_t)DATA)
#define UART_Flags(DATA)                    ((uint8_t)(DATA >> 8))
#define UART_CheckDataStatus(DATA, BIT)     ((((uint32_t)DATA) << (31 - BIT)) >> 31)

#define IS_UART_DATA(DATA)                  ((DATA) <= 0xFF)

// End of group UART_Data_Status

/***************************************************************************************************************/

// UART_Clock_BRG UART Clock BRG
#define UART_HCLKdiv1                       ((uint32_t)0x00000000)
#define UART_HCLKdiv2                       ((uint32_t)0x00000001)
#define UART_HCLKdiv4                       ((uint32_t)0x00000002)
#define UART_HCLKdiv8                       ((uint32_t)0x00000003)
#define UART_HCLKdiv16                      ((uint32_t)0x00000004)
#define UART_HCLKdiv32                      ((uint32_t)0x00000005)
#define UART_HCLKdiv64                      ((uint32_t)0x00000006)
#define UART_HCLKdiv128                     ((uint32_t)0x00000007)

#define IS_UART_CLOCK_BRG(BRG)              (((BRG) >= 0) && ((BRG) <= 7))

// End of group UART_Clock_BRG

//
//
// End of group UART_Exported_Constants
//
//

// from file uart.c
#define CR_EN_Set                 ((uint16_t)0x0001)  // UART Enable Mask
#define CR_EN_Reset               ((uint16_t)0xFFFE)  // UART Disable Mask

#define CR_SIREN_Set              ((uint16_t)0x0002)  // UART IrDA mode Enable Mask
#define CR_SIREN_Reset            ((uint16_t)0xFFFD)  // UART IrDA mode Disable Mask

#define CR_FC_Mask                ((uint16_t)0xFF80)  // UART CR Flow control Bits Mask

#define LCR_H_BRK_Set             ((uint16_t)0x0001)  // UART Break Line Set Mask
#define LCR_H_BRK_Reset           ((uint16_t)0xFFFE)  // UART Break Line Reset Mask
#define LCR_H_Clear_Mask          ((uint16_t)0x00FF)  // UART LCR_H Mask

#define FBRD_Fract_Mask           ((uint16_t)0x003F)  // Fractional divider Mask

#define IrLPBaud16                ((uint32_t)1843200) // F_IrLPBaud16 nominal frequency Hz

#define UART1_BRG_Mask            ((uint32_t)0x0007)  // UART1 clock divider Mask
#define UART2_BRG_Mask            ((uint32_t)0x0700)  // UART2 clock divider Mask
#define UART2_BRG_Offs            ((uint32_t)0x0008)  // UART2 clock divider Offset


//
//
// BKP
//
//

// MDR_BKP

// MDR_BKP->REG_0E

/***************************************************************************************************************/

// MDR_BKP->REG_0E->LOW

#define BKP_REG_0E_LOW_LT_10MHz                      0x0
#define BKP_REG_0E_LOW_LT_200KHz                     0x1
#define BKP_REG_0E_LOW_LT_500KHz                     0x2
#define BKP_REG_0E_LOW_LT_1MHz                       0x3
#define BKP_REG_0E_LOW_EQ_NO_CLK                     0x4
#define BKP_REG_0E_LOW_LT_40MHz                      0x5
#define BKP_REG_0E_LOW_LT_80MHz                      0x6
#define BKP_REG_0E_LOW_GE_80MHz                      0x7

/***************************************************************************************************************/

// MDR_BKP->REG_0E->SelectRI

#define BKP_REG_0E_SELECTRI_6KOhm____ADD_300___mkA              0x00
#define BKP_REG_0E_SELECTRI_270KOhm__ADD_6dot6_mkA              0x08
#define BKP_REG_0E_SELECTRI_90KOhm___ADD_20____mkA              0x10
#define BKP_REG_0E_SELECTRI_24KOhm___ADD_80____mkA              0x18
#define BKP_REG_0E_SELECTRI_900KOhm_IADD_2_____mkA              0x20
#define BKP_REG_0E_SELECTRI_2KOhm____ADD_900___mkA              0x28
#define BKP_REG_0E_SELECTRI_400Ohm___ADD_4dot4_mA               0x30
#define BKP_REG_0E_SELECTRI_100Ohm___ADD_19____mA               0x38

/***************************************************************************************************************/

// standalone can be enabled or disabled :3

/***************************************************************************************************************/

// MDR_BKP->REG_0E->TRIM

#define BKP_REG_0E_TRIM_DUcc_PLUS__DOT10V               0x000
#define BKP_REG_0E_TRIM_DUcc_PLUS__DOT06V               0x100
#define BKP_REG_0E_TRIM_DUcc_PLUS__DOT04V               0x200
#define BKP_REG_0E_TRIM_DUcc_PLUS__DOT01V               0x300
#define BKP_REG_0E_TRIM_DUcc_MINUS_DOT01V               0x400
#define BKP_REG_0E_TRIM_DUcc_MINUS_DOT04V               0x500
#define BKP_REG_0E_TRIM_DUcc_MINUS_DOT06V               0x600
#define BKP_REG_0E_TRIM_DUcc_MINUS_DOT10V               0x700

/***************************************************************************************************************/
// MDR_BKP->REG_0E->FPOR

#define BKP_REG_0E_FPOR_OK                              0x800 // Enable/disable >??????? )))))

/***************************************************************************************************************/

// MDR_BKP->REG_0E->TRIM2

#define BKP_REG_0E_TRIM2_1dot8_V        0x0000
#define BKP_REG_0E_TRIM2_1dot6_V        0x1000
#define BKP_REG_0E_TRIM2_1dot4_V        0x2000
#define BKP_REG_0E_TRIM2_1dot2_V        0x3000

/***************************************************************************************************************/

// Allow shielding from current gt 150 mA   enable disable


//
//
// End of BKP
//
//


/***************************************************************************************************************/
/***************************************************************************************************************/
/***************************************************************************************************************/
// Convertion :::: FILE MDR32F9Qx_ebc.h /*******************************DONE-100%*******************************/
/***************************************************************************************************************/
/***************************************************************************************************************/
/***************************************************************************************************************/

//
//
// EBC_Exported_Types EBC Exported Types
//
//

// EBC Init structure definition
typedef struct
{
  uint32_t EBC_Mode;            // Specifies external bus mode. This parameter can be a value of EBC_MODE. uint32_t EBC_Cpol; Specifies CLOCK signal polarity.This parameter can be a value of EBC_CPOL. */
  uint8_t  EBC_WaitState;       // Specifies wait states number. This parameter can be a value of EBC_WAIT_STATE.
  uint8_t  EBC_NandTrc;         // Specifies NAND read cycle time t_rc. This parameter can be a value of EBC_NAND_CYCLES.
  uint8_t  EBC_NandTwc;         // Specifies NAND write cycle time t_wc. This parameter can be a value of EBC_NAND_CYCLES.
  uint8_t  EBC_NandTrea;        // Specifies NAND read access time t_rea. This parameter can be a value of EBC_NAND_CYCLES.
  uint8_t  EBC_NandTwp;         // Specifies NAND write access time t_wp. This parameter can be a value of EBC_NAND_CYCLES.
  uint8_t  EBC_NandTwhr;        // Specifies NAND status register access time t_whr. This parameter can be a value of  EBC_NAND_CYCLES.
  uint8_t  EBC_NandTalea;       // Specifies NAND ID registers access time t_alea. This parameter can be a value of EBC_NAND_CYCLES.
  uint8_t  EBC_NandTrr;         // Specifies NAND delay from Busy release to read operation. This parameter can be a value of EBC_NAND_CYCLES.
  uint8_t EBC_DataAlignment;    // Specifies data Alignment. This parameter can be a value of EBC_DATA_ALIGNMENT.
  uint8_t EBC_UseMemRegion;     // Specifies resolution settings of exchange of the appropriate range of addresses. This parameter can be value of USE_EBC_MEM_REGION.
}EBC_InitTypeDef;

/***************************************************************************************************************/

// EBC RAM RAM_Cycles structure definition
typedef struct
{
        uint8_t Use_Ready;      // Specifies resolution survey of the external signal to the READY output PF [2]. This parameter can be: ENABLE or DISABLE.
        uint8_t WS_Hold;        // Specifies hold time signals nWE / nOE. This parameter can be a value of EBC_WS_HOLD_CYCLE.
        uint8_t WS_Setup;       // Specifies time preset signals nWE / nOE in cycle read / write. This parameter can be a value of @ref EBC_WS_SETUP_CYCLE.
        uint8_t WS_Active;      // Specifies continued low level signals nWE / nOE in cycle read / write. This parameter can be a number between 0x0000 and 0x7F.
        uint8_t Enable_Tune;    // Specifies resolution settings of exchange of the appropriate range of addresses. This parameter can be: ENABLE or DISABLE.
}EBC_MemRegionInitTypeDef;

//
//
// End of group EBC_Exported_Types
//
//

//
//
// EBC_Exported_Constants EBC Exported Constants
//
//

// EBC_MODE EBC mode

#define EBC_MODE_OFF                ((uint32_t)0x0)                 // EBC disabled
#define EBC_MODE_ROM                (((uint32_t)0x1) << 0)          // EBC works with external ROM
#define EBC_MODE_RAM                (((uint32_t)0x1) << 1)          // EBC works with external RAM
#define EBC_MODE_NAND               (((uint32_t)0x1) << 2)          // EBC works with external NAND Flash memory

#define EBC_MODE_MSK                (EBC_MODE_ROM | EBC_MODE_RAM | EBC_MODE_NAND)

#define IS_EBC_MODE(MODE) (((MODE) == EBC_MODE_OFF ) || \
                               ((MODE) == EBC_MODE_ROM ) || \
                               ((MODE) == EBC_MODE_RAM ) || \
                               ((MODE) == EBC_MODE_NAND))

// End of group EBC_MODE

/***************************************************************************************************************/

// EBC_CPOL EBC CLOCK polarity

#define EBC_CPOL_POSITIVE           (((uint32_t)0x0) << 3)         // EBC generates the positive CLOCK signal
#define EBC_CPOL_NEGATIVE           (((uint32_t)0x1) << 3)         // EBC generates the negative CLOCK signal

#define IS_EBC_CPOL(CPOL) (((CPOL) == EBC_CPOL_POSITIVE) || \
                               ((CPOL) == EBC_CPOL_NEGATIVE))

// End of group EBC_CPOL

/***************************************************************************************************************/

// EBC_WAIT_STATE EBC Wait States number

#define EBC_WAIT_STATE_3HCLK        ((uint32_t)0x0)                 // Wait State = 3 HCLK clocks
#define EBC_WAIT_STATE_4HCLK        ((uint32_t)0x1)                 // Wait State = 4 HCLK clocks
#define EBC_WAIT_STATE_5HCLK        ((uint32_t)0x2)                 // Wait State = 5 HCLK clocks
#define EBC_WAIT_STATE_6HCLK        ((uint32_t)0x3)                 // Wait State = 6 HCLK clocks
#define EBC_WAIT_STATE_7HCLK        ((uint32_t)0x4)                 // Wait State = 7 HCLK clocks
#define EBC_WAIT_STATE_8HCLK        ((uint32_t)0x5)                 // Wait State = 8 HCLK clocks
#define EBC_WAIT_STATE_9HCLK        ((uint32_t)0x6)                 // Wait State = 9 HCLK clocks
#define EBC_WAIT_STATE_10HCLK       ((uint32_t)0x7)                 // Wait State = 10 HCLK clocks
#define EBC_WAIT_STATE_11HCLK       ((uint32_t)0x8)                 // Wait State = 11 HCLK clocks
#define EBC_WAIT_STATE_12HCLK       ((uint32_t)0x9)                 // Wait State = 12 HCLK clocks
#define EBC_WAIT_STATE_13HCLK       ((uint32_t)0xA)                 // Wait State = 13 HCLK clocks
#define EBC_WAIT_STATE_14HCLK       ((uint32_t)0xB)                 // Wait State = 14 HCLK clocks
#define EBC_WAIT_STATE_15HCLK       ((uint32_t)0xC)                 // Wait State = 15 HCLK clocks
#define EBC_WAIT_STATE_16HCLK       ((uint32_t)0xD)                 // Wait State = 16 HCLK clocks
#define EBC_WAIT_STATE_17HCLK       ((uint32_t)0xE)                 // Wait State = 17 HCLK clocks
#define EBC_WAIT_STATE_18HCLK       ((uint32_t)0xF)                 // Wait State = 18 HCLK clocks

#define EBC_WAIT_STATE_MSK          ((uint32_t)0xF)                 // Wait State value mask

#define IS_EBC_WAIT_STATE(WAIT_STATE) (((WAIT_STATE) & ~EBC_WAIT_STATE_MSK) == 0 )

// End of group EBC_WAIT_STATE

/***************************************************************************************************************/

// EBC_NAND_CYCLES EBC NAND Cycles

#define EBC_NAND_CYCLES_0HCLK       ((uint32_t)0x0)                 // NAND Cycles = 0 HCLK clocks
#define EBC_NAND_CYCLES_1HCLK       ((uint32_t)0x1)                 // NAND Cycles = 1 HCLK clocks
#define EBC_NAND_CYCLES_2HCLK       ((uint32_t)0x2)                 // NAND Cycles = 2 HCLK clocks
#define EBC_NAND_CYCLES_3HCLK       ((uint32_t)0x3)                 // NAND Cycles = 3 HCLK clocks
#define EBC_NAND_CYCLES_4HCLK       ((uint32_t)0x4)                 // NAND Cycles = 4 HCLK clocks
#define EBC_NAND_CYCLES_5HCLK       ((uint32_t)0x5)                 // NAND Cycles = 5 HCLK clocks
#define EBC_NAND_CYCLES_6HCLK       ((uint32_t)0x6)                 // NAND Cycles = 6 HCLK clocks
#define EBC_NAND_CYCLES_7HCLK       ((uint32_t)0x7)                 // NAND Cycles = 7 HCLK clocks
#define EBC_NAND_CYCLES_8HCLK       ((uint32_t)0x8)                 // NAND Cycles = 8 HCLK clocks
#define EBC_NAND_CYCLES_9HCLK       ((uint32_t)0x9)                 // NAND Cycles = 9 HCLK clocks
#define EBC_NAND_CYCLES_10HCLK      ((uint32_t)0xA)                 // NAND Cycles = 10 HCLK clocks
#define EBC_NAND_CYCLES_11HCLK      ((uint32_t)0xB)                 // NAND Cycles = 11 HCLK clocks
#define EBC_NAND_CYCLES_12HCLK      ((uint32_t)0xC)                 // NAND Cycles = 12 HCLK clocks
#define EBC_NAND_CYCLES_13HCLK      ((uint32_t)0xD)                 // NAND Cycles = 13 HCLK clocks
#define EBC_NAND_CYCLES_14HCLK      ((uint32_t)0xE)                 // NAND Cycles = 14 HCLK clocks
#define EBC_NAND_CYCLES_15HCLK      ((uint32_t)0xF)                 // NAND Cycles = 15 HCLK clocks

#define EBC_NAND_CYCLES_MSK         ((uint32_t)0xF)                 // NAND Cycles value mask

#define IS_EBC_NAND_CYCLES(NAND_CYCLES) (((NAND_CYCLES) & ~EBC_NAND_CYCLES_MSK) == 0 )

// End of group EBC_NAND_CYCLES

/***************************************************************************************************************/

// EBC_DATA_ALIGNMENT EBC DATA ALIGNMENT

#define EBC_EBC_DATA_ALIGNMENT_OFF      ((uint32_t)0x0)              // Not use data alignment
#define EBC_EBC_DATA_ALIGNMENT_8        ((uint32_t)0x20)             // Data alignment to 8 junior ranks EBC
#define EBC_EBC_DATA_ALIGNMENT_16       ((uint32_t)0x40)             // Data alignment to 16 junior ranks EBC

#define IS_EBC_DATA_ALIGNMENT(EBC_DATA_ALIGNMENT)       ((EBC_DATA_ALIGNMENT == EBC_EBC_DATA_ALIGNMENT_OFF) || \
                                                        (EBC_DATA_ALIGNMENT == EBC_EBC_DATA_ALIGNMENT_8)   || \
                                                        (EBC_DATA_ALIGNMENT == EBC_EBC_DATA_ALIGNMENT_16))

// End of group EBC_DATA_ALIGNMENT EBC DATA ALIGNMENT

/***************************************************************************************************************/

// EBC_MEM_REGION EBC MEM REGION

#define EBC_USE_MEM_REGION_NONE                 ((uint32_t)0x0)
#define EBC_USE_MEM_REGION_1                    ((uint32_t)0x1)
#define EBC_USE_MEM_REGION_2                    ((uint32_t)0x2)
#define EBC_USE_MEM_REGION_3                    ((uint32_t)0x4)
#define EBC_USE_MEM_REGION_4                    ((uint32_t)0x8)

#define IS_EBC_USE_MEM_REGION(EBC_USE_MEM_REGION)                       ((EBC_USE_MEM_REGION == EBC_USE_MEM_REGION_NONE) || \
                                                                         (EBC_USE_MEM_REGION == EBC_USE_MEM_REGION_1)    || \
                                                                         (EBC_USE_MEM_REGION == EBC_USE_MEM_REGION_2)    || \
                                                                         (EBC_USE_MEM_REGION == EBC_USE_MEM_REGION_3)    || \
                                                                         (EBC_USE_MEM_REGION == EBC_USE_MEM_REGION_4))

// End of groupe EBC_MEM_REGION EBC MEM REGION

/***************************************************************************************************************/

// EBC_WS_HOLD_CYCLE WS HOLD Cycles

#define EBC_WS_HOLD_CYCLE_1HCLK         ((uint32_t)0x00)                // WS HOLD Cycles = 1 HCLK clocks
#define EBC_WS_HOLD_CYCLE_2HCLK         ((uint32_t)0x01)                // WS HOLD Cycles = 2 HCLK clocks
#define EBC_WS_HOLD_CYCLE_3HCLK         ((uint32_t)0x02)                // WS HOLD Cycles = 3 HCLK clocks
#define EBC_WS_HOLD_CYCLE_4HCLK         ((uint32_t)0x03)                // WS HOLD Cycles = 4 HCLK clocks
#define EBC_WS_HOLD_CYCLE_5HCLK         ((uint32_t)0x04)                // WS HOLD Cycles = 5 HCLK clocks
#define EBC_WS_HOLD_CYCLE_6HCLK         ((uint32_t)0x05)                // WS HOLD Cycles = 6 HCLK clocks
#define EBC_WS_HOLD_CYCLE_7HCLK         ((uint32_t)0x06)                // WS HOLD Cycles = 7 HCLK clocks
#define EBC_WS_HOLD_CYCLE_8HCLK         ((uint32_t)0x07)                // WS HOLD Cycles = 8 HCLK clocks

#define EBC_WS_HOLD_CYCLES_MSK  0x07

#define IS_EBC_EBC_WS_HOLD_CYCLES(EBC_WS_HOLD_CYCLES) (((EBC_WS_HOLD_CYCLES) & ~EBC_WS_HOLD_CYCLES_MSK) == 0 )

// End of groupe EBC_WS_HOLD_CYCLE WS HOLD Cycles

/***************************************************************************************************************/

// EBC_WS_SETUP_CYCLE WS SETUP Cycles

#define EBC_WS_SETUP_CYCLE_1HCLK                ((uint32_t)0x00)                /*!<  WS SETUP Cycles = 1 HCLK clocks */
#define EBC_WS_SETUP_CYCLE_2HCLK                ((uint32_t)0x01)                /*!<  WS SETUP Cycles = 2 HCLK clocks */
#define EBC_WS_SETUP_CYCLE_3HCLK                ((uint32_t)0x02)                /*!<  WS SETUP Cycles = 3 HCLK clocks */
#define EBC_WS_SETUP_CYCLE_4HCLK                ((uint32_t)0x03)                /*!<  WS SETUP Cycles = 4 HCLK clocks */
#define EBC_WS_SETUP_CYCLE_5HCLK                ((uint32_t)0x04)                /*!<  WS SETUP Cycles = 5 HCLK clocks */
#define EBC_WS_SETUP_CYCLE_6HCLK                ((uint32_t)0x05)                /*!<  WS SETUP Cycles = 6 HCLK clocks */
#define EBC_WS_SETUP_CYCLE_7HCLK                ((uint32_t)0x06)                /*!<  WS SETUP Cycles = 7 HCLK clocks */
#define EBC_WS_SETUP_CYCLE_8HCLK                ((uint32_t)0x07)                /*!<  WS SETUP Cycles = 8 HCLK clocks */

#define EBC_WS_SETUP_CYCLES_MSK 0x07

#define IS_EBC_WS_SETUP_CYCLES(EBC_WS_SETUP_CYCLES) (((EBC_WS_SETUP_CYCLES) & ~EBC_WS_SETUP_CYCLES_MSK) == 0 )

// groupe EBC_WS_SETUP_CYCLE WS SETUP Cycles

/***************************************************************************************************************/

// EBC_MEM_REGIONx EBC MEM REGION

#define EBC_MEM_REGION_10000000         (uint32_t)(0x00)
#define EBC_MEM_REGION_50000000         (uint32_t)(0x01)
#define EBC_MEM_REGION_60000000         (uint32_t)(0x02)
#define EBC_MEM_REGION_70000000         (uint32_t)(0x03)

#define IS_EBC_MEM_REGION(EBC_MEM_REGION)         ((EBC_MEM_REGION == EBC_MEM_REGION_10000000) || \
                                                   (EBC_MEM_REGION == EBC_MEM_REGION_50000000) || \
                                                   (EBC_MEM_REGION == EBC_MEM_REGION_60000000) || \
                                                   (EBC_MEM_REGION == EBC_MEM_REGION_70000000))

// End of groupe EBC_MEM_REGIONx EBC MEM REGION

#define IS_EBC_WS_ACTIVE(WS_ACTIVE)                             ((WS_ACTIVE >= 0) && (WS_ACTIVE < 127))

//
//
// End of group EBC_Exported_Constants
//
//

//
// Bonus EBC defines
//
#define EBC_MEM_REGION_ENABLE_TUNE






















































//
//
// MACRO
//
//

#define SETBITS(value__,position__) value__ << position__



//
//
// PAUSE DELAY
//
//

// global pause counter
extern u32 ipause;

// global pause maximum
//int HCLK = HSE_Value*(RST_CLK_CPU_PLLmul6 + 1);
extern const u32 HCLK;
extern u32 maxpause_s;
extern u32 maxpause_ms;
extern u32 maxpause_mks;
extern const u32 PLL_MUL;

// I need pauses :3   approx 25 coeff at 48MHz
#define DELAY_MS(ms) maxpause_ms=(HCLK/20300)*ms;for(ipause = 0; ipause < maxpause_ms; ipause++);
#define DELAY_MKS(mks) maxpause_mks=(HCLK/20300000)*mks;for(ipause = 0; ipause < maxpause_mks; ipause++);
#define DELAY_S(s) maxpause_s=HCLK / 20;for(ipause = 0; ipause < maxpause_s; ipause++);

#endif // End of __MDR_DEFINITIONS_H_INCLUDED__

