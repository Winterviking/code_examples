//==================================================================
//==================================================================
//==================================================================
// ¬спомогательный канал
//==================================================================
//==================================================================
//==================================================================


#include "usb_cdc.h"
#include "usb_functions.h"
#include "drv_serial_port.h"
#include "drv_clock.h"


unsigned char line_coding[7];

//==================================================================
// EP SETUPS
//==================================================================

void EP1_SETUP(void) {}
void EP2_SETUP(void) {}
void EP3_SETUP(void) {}

//==================================================================
// EP OUTS
//==================================================================

void EP1_OUT(void) {}

//прин€тые данные от PC
unsigned char pDataRX[64];
unsigned char pDataTX[64];//={1};
/*
unsigned long int loadaddr=0x8000000;
unsigned long int curaddr=0;
unsigned long int loadlength=0;
unsigned long int crc;
unsigned long int crc_check;
*/
//BYTE buf[256];
//unsigned int addrinbuf=0;
//bool usb_hid=false;
void EP2_OUT(void)
{
    unsigned char cnt=USB_ReadEP(2, pDataRX);
    for(int i=0; i<cnt; i++)
    {
        com_serial_rx_irq_USB(&COM1, pDataRX[i]);
    }
}

void EP3_OUT(void) {}

//==================================================================
// EP INS
//==================================================================

volatile bool EP1_busy = false;
volatile DWORD ep1_busy_timer;
volatile bool sendempty = false;
//volatile BYTE key_ready=false;
bool f=false;

void EP1_IN(void)
{
    BYTE d[32];
    BYTE count=0;

    BYTE b;
    while(count < 32)
    {
        if(com_serial_tx_irq_USB(&COM1, &b))
            d[count] = b;
        else break;
        //d[count]=0xAA;
        count++;
    }

    if (count) {
        EP1_busy=true;
        USB_WriteEP(0x81,d,count);
        if(count==32)sendempty=true;
        else sendempty=false;
        CLEAR_TIMER(ep1_busy_timer);
    } else {
        if (sendempty)
        {
            sendempty=false;
            USB_WriteEP(0x81,d,0);
            CLEAR_TIMER(ep1_busy_timer);
        }
        else EP1_busy=false;
    }
}



void EP2_IN(void) {}
void EP3_IN(void) {}



//==================================================================
//
//==================================================================






