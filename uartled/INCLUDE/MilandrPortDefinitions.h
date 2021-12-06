
#ifndef __MILANDR_PORT_DEFINITIONS_H_INCLUDED__
#define __MILANDR_PORT_DEFINITIONS_H_INCLUDED__

#include "config.h"
#include "MDR1986VE1T_Add.h"
#include "MDR1986VE1T_helper.h"

// PROTOTYPES
void assemblePorts();





// shift for [00][01][10][11]   ?????????
#define PORT_NUM_MUL_X1         0x0
#define PORT_NUM_MUL_X2         0x1

// shift and mask for preprocessor congiguration

/********************************************************************
**   PREPROCESSOR CONFIG SCHEME                                    **
**                                                                 **
** [OE][FUNC][AD][PULL_DOWN][PULL_UP][PDRIVER][SHHIST][PWR][GFEN]  **
** [0 ][00  ][0 ][0        ][0      ][0      ][0     ][00 ][0   ]  **
********************************************************************/

#define PORTDEF_SHIFT_OE        0x0
#define PORTDEF_SHIFT_FUNC      0x1
#define PORTDEF_SHIFT_AD        0x3
#define PORTDEF_SHIFT_PULL_UP   0x4
#define PORTDEF_SHIFT_PULL_DOWN 0x5
#define PORTDEF_SHIFT_PD        0x6
#define PORTDEF_SHIFT_HIST      0x7
#define PORTDEF_SHIFT_PWR       0x8
#define PORTDEF_SHIFT_GFEN      0xA

#define PORTDEF_MASK_OE         0x001
#define PORTDEF_MASK_FUNC       0x006
#define PORTDEF_MASK_AD         0x008
#define PORTDEF_MASK_PULL_UP    0x010
#define PORTDEF_MASK_PULL_DOWN  0x020
#define PORTDEF_MASK_HIST       0x040
#define PORTDEF_MASK_PD         0x080
#define PORTDEF_MASK_PWR        0x300
#define PORTDEF_MASK_GFEN       0x400

// define separate pins
#define DEFINE_PORT_PIN(IO__, MODE__, AD__, PullUp__, PullDown__, SmidtHist__, PD_, PWR__, GFEN__) (                                                    \
                                                                                                        IO__        << PORTDEF_SHIFT_OE         |       \
                                                                                                        MODE__      << PORTDEF_SHIFT_FUNC       |       \
                                                                                                        AD__        << PORTDEF_SHIFT_AD         |       \
                                                                                                        PullUp__    << PORTDEF_SHIFT_PULL_UP    |       \
                                                                                                        PullDown__  << PORTDEF_SHIFT_PULL_DOWN  |       \
                                                                                                        SmidtHist__ << PORTDEF_SHIFT_HIST       |       \
                                                                                                        PD_         << PORTDEF_SHIFT_PD         |       \
                                                                                                        PWR__       << PORTDEF_SHIFT_PWR        |       \
                                                                                                        GFEN__      << PORTDEF_SHIFT_GFEN)

// local macro for
#define MOVE_BIT_TO_POSITION(port_definition__,mask__,shift__,port_number__) (((port_definition__&mask__) >> shift__) << port_number__)

// Assemble register part from pin defines by mask and shift for all the pins of teh port
#define ASSEMBLE_BITS(ppin_def00,ppin_def01,ppin_def02,ppin_def03,ppin_def04,ppin_def05,ppin_def06,ppin_def07,ppin_def08,ppin_def09,ppin_def10,ppin_def11,ppin_def12,ppin_def13,ppin_def14,ppin_def15,mask__,shift__,port_mul__) \
                MOVE_BIT_TO_POSITION(ppin_def00,mask__,shift__,(PORT_PIN_NUMBER_00 << port_mul__)) |    \
                MOVE_BIT_TO_POSITION(ppin_def01,mask__,shift__,(PORT_PIN_NUMBER_01 << port_mul__)) |    \
                MOVE_BIT_TO_POSITION(ppin_def02,mask__,shift__,(PORT_PIN_NUMBER_02 << port_mul__)) |    \
                MOVE_BIT_TO_POSITION(ppin_def03,mask__,shift__,(PORT_PIN_NUMBER_03 << port_mul__)) |    \
                MOVE_BIT_TO_POSITION(ppin_def04,mask__,shift__,(PORT_PIN_NUMBER_04 << port_mul__)) |    \
                MOVE_BIT_TO_POSITION(ppin_def05,mask__,shift__,(PORT_PIN_NUMBER_05 << port_mul__)) |    \
                MOVE_BIT_TO_POSITION(ppin_def06,mask__,shift__,(PORT_PIN_NUMBER_06 << port_mul__)) |    \
                MOVE_BIT_TO_POSITION(ppin_def07,mask__,shift__,(PORT_PIN_NUMBER_07 << port_mul__)) |    \
                MOVE_BIT_TO_POSITION(ppin_def08,mask__,shift__,(PORT_PIN_NUMBER_08 << port_mul__)) |    \
                MOVE_BIT_TO_POSITION(ppin_def09,mask__,shift__,(PORT_PIN_NUMBER_09 << port_mul__)) |    \
                MOVE_BIT_TO_POSITION(ppin_def10,mask__,shift__,(PORT_PIN_NUMBER_10 << port_mul__)) |    \
                MOVE_BIT_TO_POSITION(ppin_def11,mask__,shift__,(PORT_PIN_NUMBER_11 << port_mul__)) |    \
                MOVE_BIT_TO_POSITION(ppin_def12,mask__,shift__,(PORT_PIN_NUMBER_12 << port_mul__)) |    \
                MOVE_BIT_TO_POSITION(ppin_def13,mask__,shift__,(PORT_PIN_NUMBER_13 << port_mul__)) |    \
                MOVE_BIT_TO_POSITION(ppin_def14,mask__,shift__,(PORT_PIN_NUMBER_14 << port_mul__)) |    \
                MOVE_BIT_TO_POSITION(ppin_def15,mask__,shift__,(PORT_PIN_NUMBER_15 << port_mul__))


// helps to assemble true number to fill register divided into 2 parts ( PULL and PD ) defines half-word ( << 16) shift
#define HALF_WORD  0x10





/*******************************************
//                                        //
//                PORT_FUNC               //
//                PREDEFINED              //
//                DEFINITIONS             //
//                FULL SUITE              //
//                                        //
*******************************************/

//DUMMY
#define PORT_DUMMY_MODE         0x1 // digital

/////////////////////
// DIGITAL 00 MODE //
/////////////////////

#define PA00_M00_CHIP_MODE_REGISTER_BIT_0       0x0
#define PA01_M00_CHIP_MODE_REGISTER_BIT_1       0x0
#define PA02_M00_CHIP_MODE_REGISTER_BIT_2       0x0
#define PA03_15_M00_IO                          0x0

#define PB00_15_M00_IO                          0x0

#define PC00_15_M00_IO                          0x0

#define PD00_15_M00_IO                          0x0

#define PE00_15_M00_IO                          0x0

#define PF00_15_M00_IO                          0x0

/////////////////////
// DIGITAL 01 MODE //
/////////////////////

#define PA00_15_M01_DATA00_15   0x1

#define PB00_15_M01_DATA16_31   0x1

#define PC00_M01_nWR            0x1
#define PC01_M01_nRD            0x1
#define PC02_M01_ALE            0x1
#define PC03_M01_UART_TXD1      0x1
#define PC04_M01_UART_RXD1      0x1
#define PC05_M01_EXTINT1        0x1
#define PC06_M01_EXTINT2        0x1
#define PC07_M01_EXTINT3        0x1
#define PC08_M01_EXTINT4        0x1
#define PC09_M01_SSP2_TXD       0x1
#define PC10_M01_SSP2_RXD       0x1
#define PC11_M01_SSP2_SCK       0x1
#define PC12_M01_SSP2_FSS       0x1
#define PC13_M01_PRMA_PLUS      0x1
#define PC14_M01_PRMA_MINUS     0x1
#define PC15_M01_PRMB_PLUS      0x1

#define PD00_M01_PRMB_MINUS     0x1
#define PD01_M01_PRDA_PLUS      0x1
#define PD02_M01_PRDA_MINUS     0x1
#define PD03_M01_PRDB_PLUS      0x1
#define PD04_M01_PRDB_MINUS     0x1
#define PD05_M01_PRD_PRMA       0x1
#define PD06_M01_PRD_PRMB       0x1
#define PD07_M01_SSP2_TXD       0x1
#define PD08_M01_SSP2_RXD       0x1
#define PD09_M01_SSP2_SCK       0x1
#define PD10_M01_SSP2_FSS       0x1
#define PD11_M01_ADDR_00        0x1
#define PD12_M01_SSP3_TXD       0x1
#define PD13_M01_UART_TXD2      0x1
#define PD14_M01_UART_RXD2      0x1
#define PD15_M01_OUT_3_PLUS     0x1

#define PE00_M01_OUT_4_PLUS     0x1
#define PE01_M01_OUT_3_MINUS    0x1
#define PE02_M01_OUT_4_MINUS    0x1
#define PE03_M01_TMR1_CH1       0x1
#define PE04_M01_TMR1_CH2       0x1
#define PE05_M01_TMR1_CH3       0x1
#define PE06_M01_TMR1_CH4       0x1
#define PE07_M01_TMR2_CH1       0x1
#define PE08_M01_TMR2_CH2       0x1
#define PE09_M01_TMR2_CH3       0x1
#define PE10_M01_TMR2_CH4       0x1
#define PE11_M01_CAN_RX1        0x1
#define PE12_M01_CAN_TX1        0x1
#define PE13_M01_CAN_RX2        0x1
#define PE14_M01_CAN_TX2        0x1
#define PE15_M01_PRD_PRMD       0x1

#define PF00_M01_PRD_PRMA               0x1
#define PF01_M01_PRD_PRMB               0x1
#define PF02_M01_READY_OR_PRD_PRMC      0x1
#define PF03_M01_PRMC_PLUS              0x1
#define PF04_M01_PRMC_MINUS             0x1
#define PF05_M01_PRMD_PLUS              0x1
#define PF06_M01_PRMD_MINUS             0x1
#define PF07_M01_PRDC_PLUS              0x1
#define PF08_M01_PRDC_MINUS             0x1
#define PF09_M01_PRDD_PLUS              0x1
#define PF10_M01_PRDD_MINUS             0x1
#define PF11_M01_PRD_PRMC               0x1
#define PF12_M01_PRD_PRMD               0x1
#define PF13_M01_OUT_2_PLUS             0x1
#define PF14_M01_OUT_2_MINUS            0x1
#define PF15_M01_SSP3_RXD               0x1

/////////////////////
// DIGITAL 10 MODE //
/////////////////////

#define PA00_M10_EXTINT1        0x2
#define PA01_M10_EXTINT2        0x2
#define PA02_M10_EXTINT3        0x2
#define PA03_M10_EXTINT4        0x2
#define PA04_M10_BRK2           0x2
#define PA05_M10_BRK3           0x2
#define PA06_M10_TMR4_CH1       0x2
#define PA07_M10_TMR4_CH1N      0x2
#define PA08_M10_TMR4_CH2       0x2
#define PA09_M10_TMR4_CH2N      0x2
#define PA10_M10_TMR4_CH3       0x2
#define PA11_M10_TMR4_CH3N      0x2
#define PA12_M10_TMR4_CH4       0x2
#define PA13_M10_TMR4_CH4N      0x2
#define PA14_M10_BRK4           0x2
#define PA15_M10_ETR4           0x2

#define PB00_M10_IN_1_PLUS      0x2
#define PB01_M10_IN_1_MINUS     0x2
#define PB02_M10_IN_2_PLUS      0x2
#define PB03_M10_IN_2_MINUS     0x2
#define PB04_M10_IN_3_PLUS      0x2
#define PB05_M10_IN_3_MINUS     0x2
#define PB06_M10_IN_4_PLUS      0x2
#define PB07_M10_IN_4_MINUS     0x2
#define PB08_M10_IN_5_PLUS      0x2
#define PB09_M10_IN_5_MINUS     0x2
#define PB10_M10_IN_6_PLUS      0x2
#define PB11_M10_IN_6_MINUS     0x2
#define PB12_M10_IN_7_PLUS      0x2
#define PB13_M10_IN_7_MINUS     0x2
#define PB14_M10_IN_8_PLUS      0x2
#define PB15_M10_IN_8_MINUS     0x2

#define PC00_M10_ETR1           0x2
#define PC01_M10_ETR2           0x2
#define PC02_M10_CLKO           0x2
#define PC03_M10_CLE            0x2
#define PC04_M10_BUSY           0x2
#define PC05_M10_SSP1_TXD       0x2
#define PC06_M10_SSP1_RXD       0x2
#define PC07_M10_SSP1_SCK       0x2
#define PC08_M10_SSP1_FSS       0x2
#define PC09_M10_BE0            0x2
#define PC10_M10_BE1            0x2
#define PC11_M10_BE2            0x2
#define PC12_M10_BE3            0x2
#define PC13_M10_ADDR_30        0x2
#define PC14_M10_ADDR_31        0x2
#define PC15_M10_BUSY           0x2

#define PD00_M10_ALE            0x2
#define PD01_M10_CLE            0x2
#define PD02_M10_SSP1_TXD       0x2
#define PD03_M10_SSP1_RXD       0x2
#define PD04_M10_SSP1_SCK       0x2
#define PD05_M10_SSP1_FSS       0x2
#define PD06_M10_nUART2RI       0x2
#define PD07_M10_nUART2DCD      0x2
#define PD08_M10_nUART2DTR      0x2
#define PD09_M10_nUART2DSR      0x2
#define PD10_M10_nUART2RTS      0x2
#define PD11_M10_nUART2CTS      0x2
#define PD12_M10_ETR3           0x2
#define PD13_M10_OUT_1_PLUS     0x2
#define PD14_M10_OUT_1_MINUS    0x2
#define PD15_M10_ADDR_13        0x2

#define PE00_15_M10_ADDR_14_29  0x2

#define PF00_M10_READY          0x2
#define PF01_M10_ADDR_30        0x2
#define PF02_M10_ADDR_31        0x2
#define PF03_15_M10_ADDR_00_12  0x2

/////////////////////
// DIGITAL 11 MODE //
/////////////////////

#define PA00_M11_ETR1           0x3
#define PA01_M11_ETR2           0x3
#define PA02_M11_ETR3           0x3
#define PA03_M11_BRK1           0x3
#define PA04_M11_FRX            0x3
#define PA05_M11_FXD            0x3
#define PA06_M11_FXEN           0x3
#define PA07_M11_FTX            0x3
#define PA08_M11_PRMC_PLUS      0x3
#define PA09_M11_PRMC_MINUS     0x3
#define PA10_M11_PRMD_PLUS      0x3
#define PA11_M11_PRMD_MINUS     0x3
#define PA12_M11_PRDC_PLUS      0x3
#define PA13_M11_PRDC_MINUS     0x3
#define PA14_M11_PRDD_PLUS      0x3
#define PA15_M11_PRDD_MINUS     0x3

#define PB00_M11_TMR3_CH1       0x3
#define PB01_M11_TMR3_CH1N      0x3
#define PB02_M11_TMR3_CH2       0x3
#define PB03_M11_TMR3_CH2N      0x3
#define PB04_M11_TMR3_CH3       0x3
#define PB05_M11_TMR3_CH3N      0x3
#define PB06_M11_TMR3_CH4       0x3
#define PB07_M11_TMR3_CH4N      0x3
#define PB08_M11_TMR1_CH1N      0x3
#define PB09_M11_TMR2_CH1N      0x3
#define PB10_M11_TMR1_CH2N      0x3
#define PB11_M11_TMR2_CH2N      0x3
#define PB12_M11_TMR1_CH3N      0x3
#define PB13_M11_TMR2_CH3N      0x3
#define PB14_M11_TMR1_CH4N      0x3
#define PB15_M11_TMR2_CH4N      0x3

#define PC00_M11_BRK1           0x3
#define PC01_M11_BRK2           0x3
#define PC02_M11_BRK3           0x3
#define PC03_M11_SIROUT0        0x3
#define PC04_M11_SIRIN0         0x3
#define PC05_M11_SSP1_RXD       0x3
#define PC06_M11_SSP1_TXD       0x3
#define PC07_M11_FXEN           0x3
#define PC08_M11_FTX            0x3
#define PC09_M11_CAN_RX1        0x3
#define PC10_M11_CAN_TX1        0x3
#define PC11_M11_CAN_RX2        0x3
#define PC12_M11_CAN_TX2        0x3
#define PC13_M11_UART_TXD2      0x3
#define PC14_M11_UART_RXD2      0x3
#define PC15_M11_TMR2_CH1       0x3

#define PD00_10_M11_ADDR_16_00  0x3
#define PD11_M11_FRX            0x3
#define PD12_M11_SSP3_RXD       0x3
#define PD13_M11_SIROUT1        0x3
#define PD14_M11_SIRIN1         0x3
#define PD15_M11_FSD            0x3

#define PE00_M11_MDC            0x3
#define PE01_M11_nUART2RI       0x3
#define PE02_M11_MDIO           0x3
#define PE03_M11_TXD_0          0x3
#define PE04_M11_TXD_1          0x3
#define PE05_M11_TXD_2          0x3
#define PE06_M11_TXD_3          0x3
#define PE07_M11_RXD_0          0x3
#define PE08_M11_RXD_1          0x3
#define PE09_M11_RXD_2          0x3
#define PE10_M11_RXD_3          0x3
#define PE11_M11_TXEN           0x3
#define PE12_M11_TXER           0x3
#define PE13_M11_TXCLK          0x3
#define PE14_M11_RXCLK          0x3
#define PE15_M11_RXDV           0x3

#define PF00_M11_RXER           0x3
#define PF01_M11_CRS            0x3
#define PF02_M11_COL            0x3
#define PF03_M11_TMR1_CH1       0x3
#define PF04_M11_TMR1_CH2       0x3
#define PF05_M11_TMR1_CH3       0x3
#define PF06_M11_TMR1_CH4       0x3
#define PF07_M11_OUT_4_PLUS     0x3
#define PF08_M11_OUT_4_MINUS    0x3
#define PF09_M11_OUT_3_PLUS     0x3
#define PF10_M11_OUT_3_MINUS    0x3
#define PF11_M11_OUT_2_PLUS     0x3
#define PF12_M11_OUT_2_MINUS    0x3
#define PF13_M11_SSP3_FSS       0x3
#define PF14_M11_SSP3_SCK       0x3
#define PF15_M11_SSP3_TXD       0x3

/////////////////
// ANALOG MODE //
/////////////////

//
// For all the others use
// PORT_MODE_DIGITAL

// PORT A is ANALOG FREE

// PORT B is ANALOG FREE

// PORT C is ANALOG FREE

// ...
#define PD07_ANALOG_ADC00_REF_PLUS      0x0
#define PD08_ANALOG_ADC01_REF_MINUS     0x0
#define PD09_ANALOG_ADC02               0x0
#define PD10_ANALOG_ADC03               0x0
#define PD11_ANALOG_ADC04               0x0
#define PD12_ANALOG_ADC05               0x0
#define PD13_ANALOG_ADC06               0x0
#define PD14_ANALOG_ADC07               0x0
#define PD15_ANALOG_DAC1_REF            0x0

#define PE00_ANALOG_DAC2_REF            0x0
#define PE01_ANALOG_DAC1_OUT            0x0
#define PE02_ANALOG_DAC2_OUT            0x0
// ...
#define PE06_ANALOG_OSC_IN32            0x0
#define PE07_ANALOG_OSC_OUT32           0x0
// ...

#define PF00_ANALOG_OSC_IN25            0x0
#define PF01_ANALOG_OSC_OUT25           0x0

#endif // End of __MILANDR_PORT_DEFINITIONS_H_INCLUDED__




