
#include <uart.h>

// debug
void putc(void* ptr, char Data )
{
        //short lol;

        UART1_ACTIVITY__ON;
        //DELAY_MS(50);

        //lol = Data;
        while ( ((DEBUG_UART->FR & UART_FR_TXFF) >> UART_FR_TXFF_Pos ) || ((DEBUG_UART->FR & UART_FR_BUSY) >> UART_FR_BUSY_Pos) );  // TODO:::: Macro for uart flags

        //DEBUG_UART->DR = (lol & (uint16_t)0x01FF);
        DEBUG_UART->DR = Data;
        //DELAY_MS(50);
        UART1_ACTIVITY_OFF;
}

// pult
void procUART(void* data){

}


   // UART CLOCK CALCULATION ( CLASSIC )
   // HCLK - cpu clock in Hz
void initUART(MDR_UART_TypeDef* UARTx)
{
        u32 BAUD_RATE = 9600;
        u32 cpuclock = HCLK;

        u32 divider, integerdivider, fractionaldivider;
        // u32 realspeed, speederror;

        if (UARTx == MDR_UART1) {
                cpuclock /= (1 << ((MDR_RST_CLK->UART_CLOCK & UART1_BRG_Mask) >> RST_CLK_UART_CLOCK_UART1_BRG_Pos));
        }

        // INTEGER PART
        divider = cpuclock / (BAUD_RATE >> 2);
        integerdivider = divider >> 6;

        // FRACTIONAL PART
        fractionaldivider = (divider & FBRD_Fract_Mask);

        // SPEED CHECK ???????????????????????????????????????????????????????????????????????????????? WATCH SOMEDAY LOL
        //realspeed = (cpuclock * 4) / ((integerdivider * 64) + fractionaldivider);
        //speederror = ((realspeed - BAUD_RATE) * 128) / BAUD_RATE;
        //if (speederror > 2) {

        //}

        // REGISTER BAUDRATE
        UARTx->IBRD = integerdivider;
        UARTx->FBRD = fractionaldivider;



        // UART LCR_H configuration
        UARTx->LCR_H = 0x0060; //UART_WordLength8b | UART_Parity_No | UART_StopBits1;

        // UART CR configuration
        UARTx->CR = UART_CR_TXE;
        UARTx->CR |= UART_CR_UARTEN; // enable uart



        // printf setup
        init_printf(0,putc);
}


