//==================================================================
//==================================================================
//==================================================================
// основной API драйвера ..
//==================================================================
//==================================================================
//==================================================================

#include "usb_functions.h"
#include "usbdesc.h"


/*
__attribute__ section="USB_PACKET_MEMORY"

#pragma location="USB_PACKET_MEMORY"
unsigned int USB_PacketMemory[256];
*/

//==================================================================
//==================================================================
//==================================================================
// internal typedef
//==================================================================
//==================================================================
//==================================================================

typedef union __attribute__ ((packed)) _REQUEST_TYPE
{
    struct __attribute__ ((packed)) _BM
    {
        U8 Recipient : 5;
        U8 Type      : 2;
        U8 Dir       : 1;
    } BM;
    U8 B;
} REQUEST_TYPE;

typedef struct __attribute__ ((packed)) _USB_SETUP_PACKET
{
    REQUEST_TYPE bmRequestType;
    U8           bRequest;
    U16_8        wValue;
    U16_8        wIndex;
    U16          wLength;
} USB_SETUP_PACKET;

typedef struct _USB_EP_DATA
{
    U8 *pData;
    U16 Count;
} USB_EP_DATA;


//==================================================================
//==================================================================
//==================================================================


U8 line_coding[7];
U8  EP0Buf[148];
U8  USB_DeviceAddress;

USB_SETUP_PACKET SetupPacket;
USB_EP_DATA EP0Data;


//==================================================================
//==================================================================
//==================================================================


void USB_SetAddress (U32 adr)
{
    *((U32*)(USB_DADDR)) = (DADDR_EF | adr);
}

void EP_Status (U32 EPNum, U32 stat)
{
    U32 val;
    val=EPxREG(EPNum&0x0F);
    if(EPNum&0x80)
    {
        EPxREG(EPNum&0x0F)=(val^(stat&EP_STAT_TX))&(EP_MASK|EP_STAT_TX);/* IN Endpoint */
    }
    else
    {
        EPxREG(EPNum&0x0F)=(val^(stat&EP_STAT_RX))&(EP_MASK|EP_STAT_RX);/* OUT Endpoint */
    }
}



U32 USB_ReadEP (U32 EPNum, U8 *pData)
{
    U32 num=EPNum&0x0F;
    U32 ss=_pEPRxCount(num);
    U16 c=*(U16*)ss;
    U16 Count=c & 0x3FF;
    ss=(U32)_pEPRxAddr(num);
////	U32 addr=(*(U16*)ss)*2;
    U32 addr=(*(U16*)ss);
    U8 nn=0;
    U8 i=0, j=0;
    while(Count)
    {
        if((nn==0)||(nn==1))
        {
            pData[j]=*(U8*)(PMAAddr+addr+i);
            Count--;
            j++;
        }
        i++;
        if(++nn>=2) nn=0;
    }
    EP_Status(EPNum,EP_RX_VALID);
    return(j);
}





U32 USB_WriteEP (U32 EPNum, U8 *pData, U32 cnt)
{
    U32 num=EPNum&0x0F;
    U32 ss=(U32)_pEPTxCount(num);
    *(U16*)ss=(U16)cnt;
    ss=(U32)_pEPTxAddr(num);
    //*(int*)ss=8;
    U32 addr=(*(U16*)ss);
//	U32 addr=(*(U16*)ss)*2;
    U32 Count=cnt;
    U32 nn=0,i=0,j=0;
    U16 dat;
    U8 c=Count;
    if((Count%2)!=0) Count++;

    while(Count)
    {
        if((nn==0)||(nn==1))
        {
            U16 d=0;
            if(c) d=pData[j];
            if(!nn) dat=d;
            else	*(U16*)(PMAAddr+addr+i-1)=dat|(d<<8);
            Count--;
            if(c)c--;
            j++;
        }
        i++;
        if(++nn>=2) nn=0;
    }

    U16 statusEP;
    statusEP=EPxREG(EPNum&0x0F);
    if((statusEP&EP_STAT_TX)!=EP_TX_STALL)
    {
        EP_Status(EPNum, EP_TX_VALID);                /* do not make EP valid if it is stalled previously */
    }
    return (cnt);
}





void USB_SetupStage(void)
{
    USB_ReadEP(0x00,(U8 *)&SetupPacket);
}




void USB_DataInStage (void)
{
    U32 cnt;

    if (EP0Data.Count > USB_MAX_PACKET0)
    {
        cnt = USB_MAX_PACKET0;
    }
    else
    {
        cnt = EP0Data.Count;
    }
    cnt = USB_WriteEP(0x80, EP0Data.pData, cnt);
    EP0Data.pData += cnt;
    EP0Data.Count -= cnt;
}



void USB_StatusInStage (void)
{
    USB_WriteEP(0x80,0,0);
}




void USB_DataOutStage (void)
{
    U32 cnt;

    cnt = USB_ReadEP(0x00, EP0Data.pData);
    EP0Data.pData += cnt;
    EP0Data.Count -= cnt;
}




void USB_StatusOutStage (void)
{
    USB_ReadEP(0x00, EP0Buf);
}

//
// оригинальное
//
/*
bool USB_ReqGetStatus (void) {
  U32 n, m;

  switch (SetupPacket.bmRequestType.BM.Recipient) {
    case REQUEST_TO_DEVICE:
      EP0Data.pData = (U8 *)&USB_DeviceStatus;
      break;
    case REQUEST_TO_INTERFACE:
      if ((USB_Configuration != 0) && (SetupPacket.wIndex.WB.L < USB_NumInterfaces)) {
        *((__packed U16 *)EP0Buf) = 0;
        EP0Data.pData = EP0Buf;
      } else {
        return (__FALSE);
      }
      break;
    case REQUEST_TO_ENDPOINT:
      n = SetupPacket.wIndex.WB.L & 0x8F;
      m = (n & 0x80) ? ((1 << 16) << (n & 0x0F)) : (1 << n);
      if (((USB_Configuration != 0) || ((n & 0x0F) == 0)) && (USB_EndPointMask & m)) {
        *((__packed U16 *)EP0Buf) = (USB_EndPointHalt & m) ? 1 : 0;
        EP0Data.pData = EP0Buf;
      } else {
        return (__FALSE);
      }
      break;
    default:
      return (__FALSE);
  }
  return (__TRUE);
}
*/
int nd=0;
int sbmr=0;
bool USB_ReqGetDescriptor (void)
{
    U8  *pD;
    U32 len, n;

    switch (SetupPacket.bmRequestType.BM.Recipient)
    {
    case REQUEST_TO_DEVICE:
    {
        switch (SetupPacket.wValue.WB.H)
        {
        case USB_DEVICE_DESCRIPTOR_TYPE:
        {
            EP0Data.pData = (U8 *)USB_DeviceDescriptor_cdc;
            len = USB_DEVICE_DESC_SIZE;
            break;
        }
        case USB_CONFIGURATION_DESCRIPTOR_TYPE:
        {
            nd=1;
            pD=(U8 *)USB_ConfigDescriptor_cdc;
            for (n=0; n!=SetupPacket.wValue.WB.L; n++)
            {
                if(((USB_CONFIGURATION_DESCRIPTOR *)pD)->bLength!=0)
                {
                    pD+=((USB_CONFIGURATION_DESCRIPTOR *)pD)->wTotalLength;
                }
            }
            if(((USB_CONFIGURATION_DESCRIPTOR *)pD)->bLength==0) return(false);
            EP0Data.pData = pD;
            len=((USB_CONFIGURATION_DESCRIPTOR *)pD)->wTotalLength;
            break;
        }
        case USB_STRING_DESCRIPTOR_TYPE:
        {
            //return(false);

            pD=(U8 *)USB_StringDescriptor;
            for (n = 0; n != SetupPacket.wValue.WB.L; n++)
            {
                if (((USB_STRING_DESCRIPTOR *)pD)->bLength != 0)
                {
                    pD += ((USB_STRING_DESCRIPTOR *)pD)->bLength;
                }
            }
            if (((USB_STRING_DESCRIPTOR *)pD)->bLength == 0) return (false);
            EP0Data.pData = pD;
            len = ((USB_STRING_DESCRIPTOR *)pD)->bLength;
            break;

        }
        default:
        {
            if(nd==1)
            {
                sbmr=SetupPacket.bmRequestType.BM.Recipient;
            }
            return (false);
        }
        }
        break;
    }
    case REQUEST_TO_INTERFACE:
    {
        switch(SetupPacket.wValue.WB.H)
        {
        case 0x22:
        {
            EP0Data.pData = (U8 *)ReportDescriptor;
            len = 63;
            break;
        }
        default:
        {
            return (false);
        }
        }
        break;
    }

    default:
        return (false);
    }
    if (EP0Data.Count > len) EP0Data.Count = len;
    return (true);
}







bool USB_ReqSetAddress (void)
{
    switch (SetupPacket.bmRequestType.BM.Recipient)
    {
    case REQUEST_TO_DEVICE:
    {
        USB_DeviceAddress = 0x80 | SetupPacket.wValue.WB.L;
        break;
    }
    default:
        return(false);
    }
    return (true);
}





void USB_DisableEP (U32 EPNum)
{
    EP_Status(EPNum, EP_TX_DIS | EP_RX_DIS);
}




void USB_EnableEP (U32 EPNum)
{
    EP_Status(EPNum, EP_TX_NAK | EP_RX_VALID);
}





void USB_ResetEP(U32 EPNum)
{
    U32 num, val;
    num = EPNum & 0x0F;
    val = EPxREG(num);
    if (EPNum & 0x80)
    {
        EPxREG(num) = val & (EP_MASK | EP_DTOG_TX);/* IN Endpoint */
    }
    else
    {
        EPxREG(num) = val & (EP_MASK | EP_DTOG_RX);/* OUT Endpoint */
    }
}





bool USB_ReqSetConfiguration(void)
{
    if((SetupPacket.bmRequestType.BM.Recipient==REQUEST_TO_DEVICE)&&(SetupPacket.wValue.WB.L==1))//хост выбрал конфигурацию №1
    {
        //установка конфигурации, инициализация конечных точек
        U32 ss=_pEPTxCount(1);
        *(U16*)ss=0;
        ss=_pEPTxAddr(1);
        *(U16*)ss=0x88;

        EPxREG(1)=1;
        USB_ResetEP(0x80|1);
        USB_EnableEP(0x80|1);

        ss=_pEPRxCount(2);
        *(U16*)ss=(((64 << 5) - 1) | 0x8000)&0xFC00;//(32<<9);
        ss=_pEPRxAddr(2);
        *(U16*)ss=0xE8;

        EPxREG(2)=2;
        USB_ResetEP(2);
        USB_EnableEP(2);

        ss=_pEPTxCount(3);
        *(U16*)ss=0;
        ss=_pEPTxAddr(3);
        *(U16*)ss=0x148;

        EPxREG(3)=0x0603;
        USB_ResetEP(0x80|3);
        USB_EnableEP(0x80|3);
/*
        line_coding[0] = 0x00;
        line_coding[1] = 0x96;
        line_coding[2] = 0;
        line_coding[3] = 0;
        line_coding[4] = 0;
        line_coding[5] = 0;
        line_coding[6] = 8;
*/
        return(true);
    }
    return(false);
}






/*
unsigned short SCLST=0;
bool lc=false;
bool sc=false;
*/
bool lc=0;
void EP0_SETUP(void)
{
    USB_SetupStage(); //чтение пакета с установкой бита подтверждения стате_рх = 3
    EP0Data.Count = SetupPacket.wLength;     /* Number of bytes to transfer */
    switch (SetupPacket.bmRequestType.BM.Type)
    {
    case REQUEST_STANDARD:
    {
        switch (SetupPacket.bRequest)
        {
        case USB_REQUEST_GET_STATUS:
        {
//					if (!USB_ReqGetStatus()) goto stall_i;
            USB_DataInStage();//передача дескриптора с установкой стате_тх = 3
            break;
        }
        case USB_REQUEST_CLEAR_FEATURE:
        {
//				if (!USB_ReqSetClrFeature(0)) goto stall_i;
            USB_StatusInStage();//отправка пустого пакета
            break;
        }
        case USB_REQUEST_SET_FEATURE:
        {
//					if (!USB_ReqSetClrFeature(1)) goto stall_i;
            USB_StatusInStage();
            break;
        }
        case USB_REQUEST_SET_ADDRESS:
        {
//					if (!USB_ReqSetAddress()) goto stall_i;//проверка устройству ли предназначен пакет, запись адреса в временную переменную
            USB_ReqSetAddress();
            USB_StatusInStage();//отправка пустого пакета
            break;
        }
        case USB_REQUEST_GET_DESCRIPTOR:
        {
            if(!USB_ReqGetDescriptor())USB_StatusInStage();
            else
                //if (!USB_ReqGetDescriptor()) goto stall_i;
                USB_DataInStage();
            break;
        }
        case USB_REQUEST_SET_DESCRIPTOR:
        {
            //USB_SetStallEP(0x00);            /* not supported */
            EP0Data.Count = 0;
            break;
        }
        case USB_REQUEST_GET_CONFIGURATION:
        {
//					if (!USB_ReqGetConfiguration()) goto stall_i;
            USB_DataInStage();
            break;
        }
        case USB_REQUEST_SET_CONFIGURATION:
        {
//					if (!USB_ReqSetConfiguration()) goto stall_i;
            USB_ReqSetConfiguration();
            USB_StatusInStage();
            break;
        }
        case USB_REQUEST_GET_INTERFACE:
        {
//					if (!USB_ReqGetInterface()) goto stall_i;
            USB_DataInStage();
            break;
        }
        case USB_REQUEST_SET_INTERFACE:
        {
//					if (!USB_ReqSetInterface()) goto stall_i;
            USB_StatusInStage();
            break;
        }
        default:
            break;// goto stall_i;
        }
        break;  /* end case REQUEST_STANDARD */
    }
    case REQUEST_CLASS:
    {
        switch(SetupPacket.bRequest)
        {
        case 0x20://SET_LINE_CODING
        {
            USB_StatusInStage();
            break;
        }
        case 0x21://GET_LINE_CODING
        {
					line_coding[0] = 0x80;
					line_coding[1] = 0x25;
					line_coding[2] = 0;
					line_coding[3] = 0;
					line_coding[4] = 0;    /* stop bit  */
					line_coding[5] = 0;    /* parity    */
					line_coding[6] = 8;    /* data bits */

					EP0Data.pData=(U8*)line_coding;
					EP0Data.Count=7;
					USB_DataInStage();
          break;
        }
        case 0x22://SET_CONTROL_LINE_STATE
        {
            USB_StatusInStage();
            break;
        }
        default:
        {
            break;
        }
        }
    }
    break;
    }
}









BYTE EP0_Data[100];
void EP0_OUT(void)
{
    if (SetupPacket.bmRequestType.BM.Dir == REQUEST_HOST_TO_DEVICE)
    {
        if (EP0Data.Count)
        {
            EP0Data.pData=EP0_Data;                            /* still data to receive ? */
            USB_DataOutStage();                                            /* receive data */
            if (EP0Data.Count == 0)
            {
                /* data complete ? */
                switch (SetupPacket.bmRequestType.BM.Type)
                {
                case REQUEST_STANDARD:
                    break;// goto stall_i;                                            /* not supported */
                case REQUEST_TO_ENDPOINT:
                {
                    USB_StatusInStage();
                    break;  /* end case REQUEST_VENDOR */
                }
                case REQUEST_CLASS:
                {
                    USB_StatusInStage();
                    break;
                }
                default:
                    break;
                }
            }
        }
    }
    else   USB_StatusOutStage();                                              /* receive Acknowledge */
}




void EP0_IN(void)
{
    if (SetupPacket.bmRequestType.BM.Dir == REQUEST_DEVICE_TO_HOST)
    {
        USB_DataInStage();                                               /* send data */
    }
    else
    {
        if (USB_DeviceAddress & 0x80)
        {
            USB_DeviceAddress &= 0x7F;
            USB_SetAddress(USB_DeviceAddress);
        }
    }
}

