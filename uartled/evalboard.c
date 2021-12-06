
#include <evalboard.h>

void initClockEvalboard();
void initPortEvalboard();


void initEvalboard(){
        // base
        initClockEvalboard();
        initPortEvalboard();

        // drivers
        initUART(MDR_UART1);

}




void initPortEvalboard(){
        assemblePorts();
}

void initClockEvalboard(){



   MDR_RST_CLK->HS_CONTROL = RST_CLK_HSE_ON; // ok 0x01

   // HSE ON >>>> USELESS and never working as expected :D
   //while ((MDR_RST_CLK->CLOCK_STATUS&RST_CLK_CLOCK_STATUS_HSE_RDY_Pos)==0);

   // pre pll start))
   MDR_RST_CLK->CPU_CLOCK = RST_CLK_CPU_PLLsrcHSEdiv1                                           |
                            RST_CLK_CPU_C2_SRC_CPU_C1                                           |
                            RST_CLK_CPUclkCPU_C3                                                |
                            SETBITS(RST_CLK_CPUclkDIV1, RST_CLK_CPU_CLOCK_CPU_C3_SEL_Pos); // ok 0x0102

   // Init PLL
   MDR_RST_CLK->PLL_CONTROL = RST_CLK_PLL_CONTROL_PLL_CPU_ON                                    |
                              SETBITS(PLL_MUL_LABEL, RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Pos); // ok 0x0504

   // Reboot CPU PLL
   MDR_RST_CLK->PLL_CONTROL |= RST_CLK_PLL_CONTROL_PLL_CPU_PLD;
   MDR_RST_CLK->PLL_CONTROL &= ~RST_CLK_PLL_CONTROL_PLL_CPU_PLD;

   // PLL init routine
   DELAY_MKS(40);// wtf )
   while ((MDR_RST_CLK->CLOCK_STATUS&RST_CLK_CLOCK_STATUS_PLL_CPU_RDY)==0);

   // EEPROM START ????
   // пусть будет, лол)))))
   MDR_RST_CLK->PER_CLOCK|=RST_CLK_PCLK_EEPROM; // EEPROM_CTRL Clock enable

#if (PLL_MULL < 3)                              //Freqency < 25MHz
   MDR_EEPROM->CMD = EEPROM_Latency_0;
#elif (PLL_MULL > 2) && (PLL_MULL < 6)          //25 <= Freqency < 50MHz
   MDR_EEPROM->CMD=EEPROM_Latency_1;
#elif (PLL_MULL > 5) && (PLL_MULL < 9)          //50 <= Freqency < 75MHz
   MDR_EEPROM->CMD=EEPROM_Latency_2;
#elif (PLL_MULL > 8) && (PLL_MULL < 12)         //75 <= Freqency < 100MHz
   MDR_EEPROM->CMD=EEPROM_Latency_3;
#elif (PLL_MULL > 11) && (PLL_MULL < 14)        //100 <= Freqency < 125MHz
   MDR_EEPROM->CMD=EEPROM_Latency_4;
#else
   MDR_EEPROM->CMD=EEPROM_Latency_7;
#endif  //PLL_MULL<3

   MDR_RST_CLK->PER_CLOCK&=(~RST_CLK_PCLK_EEPROM);  // EEPROM_CTRL Clock disable

   // switch CPU to PLL >>>>>
   MDR_RST_CLK->CPU_CLOCK = RST_CLK_CPU_PLLsrcHSEdiv1                                           | // pll source
                            RST_CLK_CPU_C2_SRC_CPU_PLL0                                         |
                            RST_CLK_CPUclkCPU_C3                                                |
                            SETBITS(RST_CLK_CPUclkDIV1, RST_CLK_CPU_CLOCK_CPU_C3_SEL_Pos); // ok 0x0106

   // Start periphetal clocks x__x
   MDR_RST_CLK->PER_CLOCK = //RST_CLK_PCLK_CAN1                 |
                            //RST_CLK_PCLK_CAN2                 |
                            //RST_CLK_PCLK_USB                  |
                            RST_CLK_PCLK_EEPROM                 |
                            RST_CLK_PCLK_RST_CLK                |
                            //RST_CLK_PCLK_DMA                    |
                            RST_CLK_PCLK_UART1                  |
                            //RST_CLK_PCLK_UART2                |
                            //RST_CLK_PCLK_SSP1                 |
                            //RST_CLK_PCLK_MIL_STD_15531          |
                            //RST_CLK_PCLK_MIL_STD_15532          |
                            //RST_CLK_PCLK_POWER                  |
                            //RST_CLK_PCLK_WWDG                   |
                            //RST_CLK_PCLK_IWDG                   |
                            RST_CLK_PCLK_TIMER1                 |
                            RST_CLK_PCLK_TIMER2                 |
                            //RST_CLK_PCLK_TIMER3                 |
                            //RST_CLK_PCLK_ADC                  |
                            //RST_CLK_PCLK_DAC                  |
                            RST_CLK_PCLK_TIMER4                 |
                            //RST_CLK_PCLK_SSP2                 |
                            //RST_CLK_PCLK_PORTA                  |
                            //RST_CLK_PCLK_PORTB                  |
                            RST_CLK_PCLK_PORTC                  |
                            RST_CLK_PCLK_PORTD                  |
                            RST_CLK_PCLK_PORTE                  |
                            //RST_CLK_PCLK_ARINC429R            |
                            //RST_CLK_PCLK_BKP                    |
                            //RST_CLK_PCLK_ARINC429T            |
                            RST_CLK_PCLK_PORTF                  //|
                            //RST_CLK_PCLK_EBC                    |
                            //RST_CLK_PCLK_SSP3
                            ;
        //MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;




        MDR_RST_CLK->UART_CLOCK =       SETBITS(UART_HCLKdiv2,RST_CLK_UART_CLOCK_UART1_BRG_Pos) |
                                        SETBITS(ENABLE,RST_CLK_UART_CLOCK_UART1_CLK_EN_Pos);

}






