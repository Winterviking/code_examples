#ifndef __USB_FUNCTIONS_H_INCLUDED__
#define __USB_FUNCTIONS_H_INCLUDED__

#include "includer_hw.h"




//#define U32 unsigned int
//#define U16 unsigned short
//#define U8 unsigned char

typedef unsigned int    U32;
typedef unsigned short  U16;
typedef unsigned char   U8;

typedef  union  __attribute__ ((packed))
{
    U16 W;
    struct __attribute__ ((packed))
    {
        U8 L;
        U8 H;
    } WB;
} U16_8;













/* USB Descriptor Types */
//типы стандартных дескрипторов
#define USB_DEVICE_DESCRIPTOR_TYPE                  1
#define USB_CONFIGURATION_DESCRIPTOR_TYPE           2
#define USB_STRING_DESCRIPTOR_TYPE                  3
#define USB_INTERFACE_DESCRIPTOR_TYPE               4
#define USB_ENDPOINT_DESCRIPTOR_TYPE                5

#define USB_HID_DESCRIPTOR_TYPE                     0x21
#define USB_HID_REPORT_DESCRIPTOR_TYPE              0x22

//максимальный размер буфера 0 конечной точки
#define USB_MAX_PACKET0                         64


/* bmRequestType.Dir */
#define REQUEST_HOST_TO_DEVICE                  0
#define REQUEST_DEVICE_TO_HOST                  1

/* bmRequestType.Type */
#define REQUEST_STANDARD                        0
#define REQUEST_CLASS                           1
#define REQUEST_VENDOR                          2
#define REQUEST_RESERVED                        3

/* USB Standard Request Codes */
//типы стандартных команд/запросов
#define USB_REQUEST_GET_STATUS                  0
#define USB_REQUEST_CLEAR_FEATURE               1
#define USB_REQUEST_SET_FEATURE                 3
#define USB_REQUEST_SET_ADDRESS                 5
#define USB_REQUEST_GET_DESCRIPTOR              6
#define USB_REQUEST_SET_DESCRIPTOR              7
#define USB_REQUEST_GET_CONFIGURATION           8
#define USB_REQUEST_SET_CONFIGURATION           9
#define USB_REQUEST_GET_INTERFACE               10
#define USB_REQUEST_SET_INTERFACE               11
#define USB_REQUEST_SYNC_FRAME                  12

/* bmRequestType.Recipient */
//кому предназначается команда/запрос
#define REQUEST_TO_DEVICE                       0
#define REQUEST_TO_INTERFACE                    1
#define REQUEST_TO_ENDPOINT                     2
#define REQUEST_TO_OTHER                        3








#define PMAAddr  (0x40006000L)  /* USB_IP Packet Memory Area base address   */

#define _pEPTxAddr(bEpNum)  ( ((*(U32*)(USB_BTABLE))+((U32)(bEpNum&0xF))*8   )+ (U32)PMAAddr)
#define _pEPTxCount(bEpNum) ( ((*(U32*)(USB_BTABLE))+((U32)(bEpNum&0xF))*8+2 )+ (U32)PMAAddr)
#define _pEPRxAddr(bEpNum)  ( ((*(U32*)(USB_BTABLE))+((U32)(bEpNum&0xF))*8+4 )+ (U32)PMAAddr)
#define _pEPRxCount(bEpNum) ( ((*(U32*)(USB_BTABLE))+((U32)(bEpNum&0xF))*8+6 )+ (U32)PMAAddr)
/*
#define _pEPTxAddr(bEpNum)  (((*(U16*)(USB_BTABLE))+((U32)bEpNum&0xF)*8  )*2 + (U32)PMAAddr)
#define _pEPTxCount(bEpNum) (((*(U16*)(USB_BTABLE))+((U32)bEpNum&0xF)*8+2)*2 + (U32)PMAAddr)
#define _pEPRxAddr(bEpNum)  (((*(U16*)(USB_BTABLE))+((U32)bEpNum&0xF)*8+4)*2 + (U32)PMAAddr)
#define _pEPRxCount(bEpNum) (((*(U16*)(USB_BTABLE))+((U32)bEpNum&0xF)*8+6)*2 + (U32)PMAAddr)
*/

/* ISTR: Interrupt Status Register Bit Definitions */
#define ISTR_CTR                                0x8000      /* Correct Transfer */
#define ISTR_PMAOVR                             0x4000      /* Packet Memory Aerea Over/underrun */
#define ISTR_ERR                                0x2000      /* Error */
#define ISTR_WKUP                               0x1000      /* Wake-up */
#define ISTR_SUSP                               0x0800      /* Suspend Mode */
#define ISTR_RESET                              0x0400      /* USB Reset */
#define ISTR_SOF                                0x0200      /* Start of Frame */
#define ISTR_ESOF                               0x0100      /* Expected Start of Frame */
#define ISTR_DIR                                0x0010      /* Direction of Transaction */
#define ISTR_EP_ID                              0x000F      /* EndPoint Identifier */


/* DADDR: Device Address Register Bit Definitions */
#define DADDR_EF                                0x0080      /* Enable Function */
#define DADDR_ADD                               0x007F      /* Device Address */


/* EndPoint Registers */
#define EPxREG(x) (*(volatile unsigned int *)(0x40005C00+4*(x)))

/* EPxREG: EndPoint Registers Bit Definitions */
#define EP_CTR_RX                               0x8000      /* Correct RX Transfer */
#define EP_DTOG_RX                              0x4000      /* RX Data Toggle */
#define EP_STAT_RX                              0x3000      /* RX Status */
#define EP_SETUP                                0x0800      /* EndPoint Setup */
#define EP_TYPE                                 0x0600      /* EndPoint Type */
#define EP_KIND                                 0x0100      /* EndPoint Kind */
#define EP_CTR_TX                               0x0080      /* Correct TX Transfer */
#define EP_DTOG_TX                              0x0040      /* TX Data Toggle */
#define EP_STAT_TX                              0x0030      /* TX Status */
#define EP_EA                                   0x000F      /* EndPoint Address */

/* EndPoint Register Mask (No Toggle Fields) */
#define EP_MASK                                 (EP_CTR_RX|EP_SETUP|EP_TYPE|EP_KIND|EP_CTR_TX|EP_EA)

/* EP_TYPE: EndPoint Types */
#define EP_BULK                                 0x0000      /* BULK EndPoint */
#define EP_CONTROL                              0x0200      /* CONTROL EndPoint */
#define EP_ISOCHRONOUS                          0x0400      /* ISOCHRONOUS EndPoint */
#define EP_INTERRUPT                            0x0600      /* INTERRUPT EndPoint */

/* EP_KIND: EndPoint Kind */
#define EP_DBL_BUF                              EP_KIND     /* Double Buffer for Bulk Endpoint */
#define EP_STATUS_OUT                           EP_KIND     /* Status Out for Control Endpoint */

/* EP_STAT_TX: TX Status */
#define EP_TX_DIS                               0x0000      /* Disabled */
#define EP_TX_STALL                             0x0010      /* Stalled */
#define EP_TX_NAK                               0x0020      /* NAKed */
#define EP_TX_VALID                             0x0030      /* Valid */

/* EP_STAT_RX: RX Status */
#define EP_RX_DIS                               0x0000      /* Disabled */
#define EP_RX_STALL                             0x1000      /* Stalled */
#define EP_RX_NAK                               0x2000      /* NAKed */
#define EP_RX_VALID                             0x3000      /* Valid */


/* bmAttributes in Configuration Descriptor */

#define USB_CONFIG_POWERED_MASK                 0x40
#define USB_CONFIG_POWER_MA(mA)                 ((mA)/2)

#define USB_GETSTATUS_SELF_POWERED              0x01








//===============================================================================================
// functions
//
void EP0_SETUP(void);
void EP0_OUT(void);
void EP0_IN(void);

void USB_ResetEP(unsigned int num);
void USB_EnableEP(unsigned int num);

U32 USB_ReadEP (U32 EPNum, U8 *pData);
U32 USB_WriteEP (U32 EPNum, U8 *pData, U32 cnt);





#endif /* __USB_FUNCTIONS_H_INCLUDED__ */
