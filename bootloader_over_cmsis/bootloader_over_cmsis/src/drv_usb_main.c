
#include "drv_usb_main.h"
#include "usb_functions.h"
#include "usb_utilities.h"
#include "usb_cdc.h"

//Дисконект для USB (Выводы данных на 10мс в 0)
void drv_usb_disconnect(void)
{
    RCC_PeriphCLKInitTypeDef PeriphClkInit;

    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;//выбрали в качестве usb clock - pll
    //PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
    PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;

    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

    HAL_NVIC_DisableIRQ((IRQn_Type) USB_IRQn);

    U32 bcdr            = *(U32*)(USB_BCDR);
    *(U32*)(USB_BCDR)   = (bcdr&~USB_BCDR_DPPU);

    *(U32*)(USB_CNTR)   = 0;

    __USB_FORCE_RESET();

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.Pin      = USB_START_PIN;
    GPIO_InitStructure.Mode     = GPIO_MODE_ANALOG;
    GPIO_InitStructure.Pull     = GPIO_NOPULL;
    GPIO_InitStructure.Speed    = GPIO_SPEED_LOW;

    HAL_GPIO_Init(USB_START_PORT, &GPIO_InitStructure);
    //USB_START_PORT->BRR=USB_START_PIN;

    __HAL_RCC_HSI48_DISABLE();
    RCC->APB1ENR &= ~(RCC_APB1ENR_USBEN);

    GPIO_InitStructure.Pin      = USB_DP_PIN;
    GPIO_InitStructure.Mode     = GPIO_MODE_ANALOG;
    GPIO_InitStructure.Pull     = GPIO_NOPULL;
    GPIO_InitStructure.Speed    = GPIO_SPEED_LOW;

    HAL_GPIO_Init(USB_DP_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin      = USB_DM_PIN;
    GPIO_InitStructure.Mode     = GPIO_MODE_ANALOG;
    GPIO_InitStructure.Pull     = GPIO_NOPULL;
    GPIO_InitStructure.Speed    = GPIO_SPEED_LOW;

    HAL_GPIO_Init(USB_DM_PORT, &GPIO_InitStructure);

    //GPIOA->BRR=GPIO_PIN_11 | GPIO_PIN_12;
}

void drv_usb_detect_init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.Pin      = USB_DETECT_PIN;
    GPIO_InitStructure.Mode     = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull     = GPIO_NOPULL;// GPIO_PULLDOWN;
    GPIO_InitStructure.Speed    = GPIO_SPEED_LOW;

    HAL_GPIO_Init(USB_DETECT_PORT, &GPIO_InitStructure);
}
void drv_usb_detect_deinit()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.Pin      = USB_DETECT_PIN;
    GPIO_InitStructure.Mode     = GPIO_MODE_ANALOG;
    GPIO_InitStructure.Pull     = GPIO_NOPULL;
    GPIO_InitStructure.Speed    = GPIO_SPEED_LOW;

    HAL_GPIO_Init(USB_DETECT_PORT, &GPIO_InitStructure);
}
bool drv_usb_detected()
{
    return((USB_DETECT_PORT->IDR&USB_DETECT_PIN) == USB_DETECT_PIN);
}

void drv_usb_init(void)
{
    drv_usb_disconnect();

//подать частоту
    RCC->APB1ENR |= (RCC_APB1ENR_USBEN);//клоки на шину для работы с регистрами usb
    __USB_RELEASE_RESET();
/*
      __HAL_RCC_HSI48_ENABLE();
      while((RCC->CRRCR&RCC_CRRCR_HSI48RDY)!=RCC_CRRCR_HSI48RDY){};
*/

    RCC_PeriphCLKInitTypeDef PeriphClkInit;

    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;//выбрали в качестве usb clock - pll
    //PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
    PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLLCLK;

    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

    //__HAL_RCC_USB_CONFIG(RCC_USBCLKSOURCE_PLLCLK);
    //RCC_APB2PeriphResetCmd(RCC_APB2Periph_AFIO, DISABLE);
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    // Set Buffer table address
    *(U32*)(USB_BTABLE) = 0;//0xF8;//0x1F0;//
    // Set device address
    *(U32*)(USB_DADDR) = 0x80;
    // Set control reg usb
    *(U32*)(USB_CNTR) = 0x9E00;//0x8400;//
    // Clear spurious pending interrupt
    *(U32*)(USB_ISTR) = 0;


    U32 ss;
    ss = _pEPTxAddr(0);
    int i;

    for(i = 0; i < 512; i++)
    {
        *(U16*)ss = 0x00;
        ss += 2;
    }

    ss = _pEPTxAddr(0);
    *(U16*)ss = 0x40;
    ss = _pEPTxCount(0);
    *(U16*)ss = 0;

    ss = _pEPRxAddr(0);
    *(U16*)ss = 32;
    ss = _pEPRxCount(0);
    if (USB_MAX_PACKET0 > 62)
    {
        *(U16*)ss = (((USB_MAX_PACKET0 << 5) - 1) | 0x8000) & 0xFC00;
    }
    else
    {
        *(U16*)ss =   USB_MAX_PACKET0 << 9;
    }

    //*(unsigned short*)ss=8;
    // USB interrupt connect to NVIC

    HAL_NVIC_SetPriority((IRQn_Type) USB_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ((IRQn_Type) USB_IRQn);
    // Configure PA11, PA12 as USB lines
    //RCC->APB1ENR |= (RCC_APB1ENR_USBEN);

    //GPIO_InitTypeDef GPIO_InitStructure;
    /*
      GPIO_InitStructure.Pin = GPIO_PIN_11;
    	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
    	GPIO_InitStructure.Pull = GPIO_NOPULL;
    	GPIO_InitStructure.Alternate = GPIO_AF2_USB;
    	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
    	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

      GPIO_InitStructure.Pin = GPIO_PIN_12;
    	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
    	GPIO_InitStructure.Pull = GPIO_NOPULL;
    	GPIO_InitStructure.Alternate =  GPIO_AF2_USB;
    	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
    	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
    */
    /*
      GPIO_InitStructure.Pin = USB_START_PIN;
    	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    	GPIO_InitStructure.Pull = GPIO_NOPULL;
    	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
    	HAL_GPIO_Init(USB_START_PORT, &GPIO_InitStructure);
    	USB_START_PORT->BSRR=USB_START_PIN;
    */
    U32 bcdr = *(U32*)(USB_BCDR);
    *(U32*)(USB_BCDR) = (bcdr|USB_BCDR_DPPU);
}

void USB_IRQHandler(void)
{

    int inter_stat=*(U32*)(USB_ISTR);

    // Device reset
    if(inter_stat&(1<<10))
    {
        *(U32*)(USB_ISTR) = ~(1<<10);

        unsigned int reg=*(U32*)(USB_EP0R);
        reg&=~0x8080;
        reg|=(1<<9);//ep type control
        reg&=~(1<<10);//ep type control
        reg&=~(1<<6);
        reg&=~(1<<14);
        reg|=(1<<5);
        reg|=(1<<4);
        reg|=(1<<13);
        reg|=(1<<12);

        /*
        if(!(reg&(1<<5))) reg|=(1<<5); else reg&=~(1<<5);
        if(!(reg&(1<<4))) reg|=(1<<4); else reg&=~(1<<4);
        if(!(reg&(1<<13))) reg|=(1<<13); else reg&=~(1<<13);
        if(!(reg&(1<<12))) reg|=(1<<12); else reg&=~(1<<12);
        */
        *(U32*)(USB_EP0R) = reg;

        //EPxREG(0)=0x0200;
        USB_ResetEP(0);
        USB_EnableEP(0);

        *(U32*)(USB_DADDR) = 0x80;
    }
    //
    if(inter_stat & (1 << 9))
    {
        *(U32*)(USB_ISTR) = ~(1 << 9);
    }
    // Err interrupt
    if(inter_stat & (1 << 13))
    {
        *(U32*)(USB_ISTR) = ~(1 << 13);
    }
    // Wake-up interrupt
    if(inter_stat & (1 << 12))
    {
        *(U32*)(USB_ISTR) = ~(1 << 12);
    }
    // Device suspend
    if(inter_stat & (1 << 11))
    {
        *(U32*)(USB_ISTR) = ~(1 << 11);
    }
    // Expected Frame interrupt
    if(inter_stat & (1 << 8))
    {
        *(U32*)(USB_ISTR) = ~(1 << 8);
    }

    // Low priority EP interrupt
    if(inter_stat & (1 << 15)) {
        BYTE num = inter_stat & 0x0F;

        unsigned short reg = EPxREG(num);

        if(reg & EP_CTR_RX) {
            reg |= 0x0080;
            reg &= ~0x8000;
            reg |= (1 << 9);
            reg &= ~(1 << 10);
            reg &= ~(1 << 6);
            reg &= ~(1 << 14);
            reg &= ~(1 << 13);
            reg &= ~(1 << 12);
            reg &= ~(1 << 5);
            reg &= ~(1 << 4);

            EPxREG(num) = reg;
            if(reg & EP_SETUP)
            {
                switch(num)
                {
                case 0:
                    EP0_SETUP();
                    break;
                }
            }
            else
            {
                switch(num)
                {
                case 0:
                    EP0_OUT();
                    break;
                case 2:
                    EP2_OUT();
                    break;
                }
            }
        } else if(reg & EP_CTR_TX) {
            reg |= 0x8000;
            reg &= ~0x0080;
            reg |= (1<<9);
            reg &= ~(1<<10);
            reg &= ~(1<<6);
            reg &= ~(1<<14);
            reg &= ~(1<<13);
            reg &= ~(1<<12);
            reg &= ~(1<<5);
            reg &= ~(1<<4);

            EPxREG(num)=reg;

            switch(num)
            {
            case 0:
                EP0_IN();
                break;
            case 1:
                EP1_IN();
                break;
            }
        }
    }
}








