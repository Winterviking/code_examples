















 
 
 

 
 
 


 typedef signed char int8_t;
 typedef signed short int int16_t;
 typedef signed int int32_t;

 typedef unsigned char uint8_t;
 typedef unsigned short int uint16_t;
 typedef unsigned int uint32_t;

 typedef signed char int_least8_t;
 typedef signed short int int_least16_t;
 typedef signed int int_least32_t;

 typedef unsigned char uint_least8_t;
 typedef unsigned short int uint_least16_t;
 typedef unsigned int uint_least32_t;

 typedef signed int int_fast8_t;
 typedef signed int int_fast16_t;
 typedef signed int int_fast32_t;

 typedef unsigned int uint_fast8_t;
 typedef unsigned int uint_fast16_t;
 typedef unsigned int uint_fast32_t;

 typedef signed int intptr_t;
 typedef unsigned int uintptr_t;




















 
 
 

 
 
 

typedef signed char s8;
typedef signed short int s16;
typedef signed int s32;

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned int u32;




 









































































 


 



 







 
 


 

 

 





 

typedef enum IRQn
{
 
 NonMaskableInt_IRQn = -14, 
 HardFault_IRQn = -13, 
 SVCall_IRQn = -5, 
 PendSV_IRQn = -2, 
 SysTick_IRQn = -1, 

 
 MIL_STD_1553B2_IRQn = 0, 
 MIL_STD_1553B1_IRQn = 1, 
 USB_IRQn = 2, 
 CAN1_IRQn = 3, 
 CAN2_IRQn = 4, 
 DMA_IRQn = 5, 
 UART1_IRQn = 6, 
 UART2_IRQn = 7, 
 SSP1_IRQn = 8, 
 BUSY_IRQn = 9, 
 ARINC429R_IRQn = 10, 
 POWER_IRQn = 11, 
 WWDG_IRQn = 12, 
 TIMER4_IRQn = 13, 
 TIMER1_IRQn = 14, 
 TIMER2_IRQn = 15, 
 TIMER3_IRQn = 16, 
 ADC_IRQn = 17, 
 ETHERNET_IRQn = 18, 
 SSP3_IRQn = 19, 
 SSP2_IRQn = 20, 
 ARINC429T1_IRQn = 21, 
 ARINC429T2_IRQn = 22, 
 ARINC429T3_IRQn = 23, 
 ARINC429T4_IRQn = 24, 
 BKP_IRQn = 27, 
 EXT_INT1_IRQn = 28, 
 EXT_INT2_IRQn = 29, 
 EXT_INT3_IRQn = 30, 
 EXT_INT4_IRQn = 31 
}IRQn_Type;

 
 

 

 






 







 




 



 

 

 

 
 
 
 
 
 
 
 


 







 


 









 






 
 

 
typedef union {
 struct {

 uint32_t _reserved0 :28; 
 uint32_t V :1; 
 uint32_t C :1; 
 uint32_t Z :1; 
 uint32_t N :1; 
 } b; 
 uint32_t w; 
} APSR_Type;


 
typedef union {
 struct {
 uint32_t ISR :6; 
 uint32_t _reserved0 :26; 
 } b; 
 uint32_t w; 
} IPSR_Type;


 
typedef union {
 struct {
 uint32_t _reserved0 :24; 
 uint32_t T :1; 
 } b; 
 uint32_t w; 
} xPSR_Type;

 

 
typedef struct
{
 volatile uint32_t ISER; 
 uint32_t RESERVED0[31];
 volatile uint32_t ICER; 
 uint32_t RSERVED1[31];
 volatile uint32_t ISPR; 
 uint32_t RESERVED2[31];
 volatile uint32_t ICPR; 
 uint32_t RESERVED3[95];
 volatile uint32_t IP[8]; 
} NVIC_Type;
 


 
typedef struct
{
 volatile const uint32_t CPUID; 
 volatile uint32_t ICSR; 
 uint32_t RESERVED0;
 volatile uint32_t AIRCR; 
 uint32_t RESERVED1;
 volatile uint32_t CCR; 
 uint32_t RESERVED2;
 volatile uint32_t SHP2; 
 volatile uint32_t SHP3; 
 volatile uint32_t SHCSR; 
 uint32_t RESERVED3; 
 uint32_t RESERVED4; 
 volatile uint32_t DFSR; 
} SCB_Type;

 




 










 




 


 

 





 


 
typedef struct
{
 volatile uint32_t CTRL; 
 volatile uint32_t LOAD; 
 volatile uint32_t VAL; 
 volatile const uint32_t CALIB; 
} SysTick_Type;

 




 

 

 


 

 
typedef struct
{
 uint32_t RESERVED0;
 uint32_t RESERVED1;

 volatile uint32_t ACTLR; 

} InterruptType_Type;

 


 

 
typedef struct
{
 volatile uint32_t DHCSR; 
 volatile uint32_t DCRSR; 
 volatile uint32_t DCRDR; 
 volatile uint32_t DEMCR; 
} CoreDebug_Type;

 









 


 


 



 




 


 






 



 


 


 


 


 


 


 


 




 


 


 


 


 

 
 

 




 
 


 
 
static __inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
 ((NVIC_Type *) ((0xE000E000) + 0x0100))->ISER = (1 << ((uint32_t)(IRQn) & 0x1F)); 
}

 
static __inline void NVIC_DisableIRQ(IRQn_Type IRQn)
{
 ((NVIC_Type *) ((0xE000E000) + 0x0100))->ICER = (1 << ((uint32_t)(IRQn) & 0x1F)); 
}

 
static __inline uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
 return((uint32_t) ((((NVIC_Type *) ((0xE000E000) + 0x0100))->ISPR & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0)); 
}

 
static __inline void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
 ((NVIC_Type *) ((0xE000E000) + 0x0100))->ISPR = (1 << ((uint32_t)(IRQn) & 0x1F)); 
}

 
static __inline void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
 ((NVIC_Type *) ((0xE000E000) + 0x0100))->ICPR = (1 << ((uint32_t)(IRQn) & 0x1F)); 
}

 
static __inline void NVIC_SetPriority ( IRQn_Type IRQn, uint32_t priority )
{
 if(IRQn < 0) {
 
 switch (IRQn){
 case SysTick_IRQn:
 ((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP2 = (priority&0x3) << 30;
 break;
 case PendSV_IRQn:
 ((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP2 = (priority&0x3) << 22;
 break;
 case SVCall_IRQn:
 ((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP3 = (priority&0x3) << 30;
 break;
 default:
 break;
 }
 }
 else {
 ((NVIC_Type *) ((0xE000E000) + 0x0100)) ->IP[(uint32_t) (IRQn) >> 2] = ((priority << (31 - 2))>> ((31 - 2))) << (((IRQn & 0x03) << 3) + 6); 
 }
}

 
static __inline uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

 if(IRQn < 0) {
 
 switch (IRQn){
 case SysTick_IRQn:
 return ((((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP2&(0x3ul << 30)) >> 30);
 case PendSV_IRQn:
 return ((((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP2&(0x3ul << 22)) >> 22);
 case SVCall_IRQn:
 return ((((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP3&(0x3ul << 30)) >> 30);
 default:
 return (0);
 }
 }
 else {
 return((uint32_t)(((NVIC_Type *) ((0xE000E000) + 0x0100))->IP[(uint32_t)(IRQn)>>2] >> (((IRQn & 0x03) << 3) + 6))); 
 }
}


 
static __inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
 uint32_t PriorityGroupTmp = (PriorityGroup & 0x07); 
 uint32_t PreemptPriorityBits;
 uint32_t SubPriorityBits;

 PreemptPriorityBits = ((7 - PriorityGroupTmp) > 2) ? 2 : 7 - PriorityGroupTmp;
 SubPriorityBits = ((PriorityGroupTmp + 2) < 7) ? 0 : PriorityGroupTmp - 7 + 2;

 return (
 ((PreemptPriority & ((1 << (PreemptPriorityBits)) - 1)) << SubPriorityBits) |
 ((SubPriority & ((1 << (SubPriorityBits )) - 1)))
 );
}

 



 
static __inline uint32_t SysTick_Config(uint32_t ticks)
{
 if (ticks > (0xFFFFFFul << 0)) return (1); 

 ((SysTick_Type *) ((0xE000E000) + 0x0010))->LOAD = (ticks & (0xFFFFFFul << 0)) - 1; 
 NVIC_SetPriority (SysTick_IRQn, (1<<2) - 1); 
 ((SysTick_Type *) ((0xE000E000) + 0x0010))->VAL = 0; 
 ((SysTick_Type *) ((0xE000E000) + 0x0010))->CTRL = (1ul << 2) |
 (1ul << 1) |
 (1ul << 0); 
 return (0); 
}




 

 
static __inline void NVIC_SystemReset(void)
{
 ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR = ((0x5FA << 16) |
 (1ul << 2)); 
 __DSB(); 
 while(1); 
}
 


 

 

 

 

 




 
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus, BitStatus;


typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

 

 

 

 
typedef struct
{
 volatile uint32_t ID;
 volatile uint32_t DLC;
 volatile uint32_t DATAL;
 volatile uint32_t DATAH;
}MDR_CAN_BUF_TypeDef;

 
typedef struct
{
 volatile uint32_t MASK;
 volatile uint32_t FILTER;
}MDR_CAN_BUF_FILTER_TypeDef;

 
typedef struct
{
 volatile uint32_t CONTROL;
 volatile uint32_t STATUS;
 volatile uint32_t BITTMNG;
 uint32_t RESERVED0;
 volatile uint32_t INT_EN;
 uint32_t RESERVED1[2];
 volatile uint32_t OVER;
 volatile uint32_t RXID;
 volatile uint32_t RXDLC;
 volatile uint32_t RXDATAL;
 volatile uint32_t RXDATAH;
 volatile uint32_t TXID;
 volatile uint32_t TXDLC;
 volatile uint32_t DATAL;
 volatile uint32_t DATAH;
 volatile uint32_t BUF_CON[32];
 volatile uint32_t INT_RX;
 volatile uint32_t RX;
 volatile uint32_t INT_TX;
 volatile uint32_t TX;
 uint32_t RESERVED2[76];
 MDR_CAN_BUF_TypeDef CAN_BUF[32];
 uint32_t RESERVED3[64];
 MDR_CAN_BUF_FILTER_TypeDef CAN_BUF_FILTER[32];
}MDR_CAN_TypeDef;

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 
 
 

 

 

 

 
 
 
 

 

 

 

 
 
 
 

 

 

 

 
 
 
 

 

 

 

 
 

 

 

 

 

 

 

 
typedef struct
{
 volatile uint32_t CTRL;
 volatile uint32_t STS;
 volatile uint32_t TS;
 volatile uint32_t NTS;
}MDR_USB_SEP_TypeDef;

 
typedef struct
{
 volatile uint32_t RXFD;
 uint32_t RESERVED0;
 volatile uint32_t RXFDC_L;
 volatile uint32_t RXFDC_H;
 volatile uint32_t RXFC;
 uint32_t RESERVED1[11];
 volatile uint32_t TXFD;
 uint32_t RESERVED2[3];
 volatile uint32_t TXFDC;
 uint32_t RESERVED3[11];
}MDR_USB_SEP_FIFO_TypeDef;

 
typedef struct
{
 volatile uint32_t HTXC;
 volatile uint32_t HTXT;
 volatile uint32_t HTXLC;
 volatile uint32_t HTXSE;
 volatile uint32_t HTXA;
 volatile uint32_t HTXE;
 volatile uint32_t HFN_L;
 volatile uint32_t HFN_H;
 volatile uint32_t HIS;
 volatile uint32_t HIM;
 volatile uint32_t HRXS;
 volatile uint32_t HRXP;
 volatile uint32_t HRXA;
 volatile uint32_t HRXE;
 volatile uint32_t HRXCS;
 volatile uint32_t HSTM;
 uint32_t RESERVED0[16];
 volatile uint32_t HRXFD;
 uint32_t RESERVED1;
 volatile uint32_t HRXFDC_L;
 volatile uint32_t HRXFDC_H;
 volatile uint32_t HRXFC;
 uint32_t RESERVED2[11];
 volatile uint32_t HTXFD;
 uint32_t RESERVED3[3];
 volatile uint32_t HTXFC;
 uint32_t RESERVED4[11];
 MDR_USB_SEP_TypeDef USB_SEP[4];
 volatile uint32_t SC;
 volatile uint32_t SLS;
 volatile uint32_t SIS;
 volatile uint32_t SIM;
 volatile uint32_t SA;
 volatile uint32_t SFN_L;
 volatile uint32_t SFN_H;
 uint32_t RESERVED5[9];
 MDR_USB_SEP_FIFO_TypeDef USB_SEP_FIFO[4];
 volatile uint32_t HSCR;
 volatile uint32_t HSVR;
}MDR_USB_TypeDef;

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 


 

 

 
typedef struct
{
 volatile uint32_t CMD;
 volatile uint32_t ADR;
 volatile uint32_t DI;
 volatile uint32_t DO;
 volatile uint32_t KEY;
}MDR_EEPROM_TypeDef;

 

 

 

 
 

 

 

 

 

 

 

 
typedef struct {
 volatile uint32_t CLOCK_STATUS;
 volatile uint32_t PLL_CONTROL;
 volatile uint32_t HS_CONTROL;
 volatile uint32_t CPU_CLOCK;
 volatile uint32_t USB_CLOCK;
 volatile uint32_t ADC_MCO_CLOCK;
 volatile uint32_t RTC_CLOCK;
 volatile uint32_t PER_CLOCK;
 volatile uint32_t CAN_CLOCK;
 volatile uint32_t TIM_CLOCK;
 volatile uint32_t UART_CLOCK;
 volatile uint32_t SSP_CLOCK;
 uint32_t RESERVED;
 volatile uint32_t ETH_CLOCK;
} MDR_RST_CLK_TypeDef;

 

 

 

 
 

 

 


 

 
 

 

 


 

 
 

 

 

 

 
 

 

 


 

 
 

 

 


 

 
 

 

 


 

 
 

 

 


 

 
 

 

 


 

 
 

 

 


 

 
 

 

 


 

 
 

 

 



 

 
 

 

 

 

 


 

 

 
typedef struct
{
 volatile uint32_t STATUS;
 volatile uint32_t CFG;
 volatile uint32_t CTRL_BASE_PTR;
 volatile uint32_t ALT_CTRL_BASE_PTR;
 volatile uint32_t WAITONREQ_STATUS;
 volatile uint32_t CHNL_SW_REQUEST;
 volatile uint32_t CHNL_USEBURST_SET;
 volatile uint32_t CHNL_USEBURST_CLR;
 volatile uint32_t CHNL_REQ_MASK_SET;
 volatile uint32_t CHNL_REQ_MASK_CLR;
 volatile uint32_t CHNL_ENABLE_SET;
 volatile uint32_t CHNL_ENABLE_CLR;
 volatile uint32_t CHNL_PRI_ALT_SET;
 volatile uint32_t CHNL_PRI_ALT_CLR;
 volatile uint32_t CHNL_PRIORITY_SET;
 volatile uint32_t CHNL_PRIORITY_CLR;
 uint32_t RESERVED0[3];
 volatile uint32_t ERR_CLR;
}MDR_DMA_TypeDef;

 

 

 

 
 

 

 

 

 
 

 

 

 

 


 

 

 

typedef struct {
 volatile uint32_t DR;
 volatile uint32_t RSR_ECR;
 uint32_t RESERVED0[4];
 volatile uint32_t FR;
 uint32_t RESERVED1;
 volatile uint32_t ILPR;
 volatile uint32_t IBRD;
 volatile uint32_t FBRD;
 volatile uint32_t LCR_H;
 volatile uint32_t CR;
 volatile uint32_t IFLS;
 volatile uint32_t IMSC;
 volatile uint32_t RIS;
 volatile uint32_t MIS;
 volatile uint32_t ICR;
 volatile uint32_t DMACR;
 volatile uint32_t UARTTCR;
} MDR_UART_TypeDef;

 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 


 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 


 

 

 

 
typedef struct
{
 volatile uint32_t CR0;
 volatile uint32_t CR1;
 volatile uint32_t DR;
 volatile uint32_t SR;
 volatile uint32_t CPSR;
 volatile uint32_t IMSC;
 volatile uint32_t RIS;
 volatile uint32_t MIS;
 volatile uint32_t ICR;
 volatile uint32_t DMACR;
}MDR_SSP_TypeDef;


 

 

 

 

 
 

 

 


 

 

 

 
 

 

 



 

 

 

 
 

 

 



 

 

 

 
 

 

 


 

 

 

 
 

 

 


 

 

 

 
 

 

 


 

 

 

 
 

 

 

 

 

 

 
 

 

 

 

 
 

 

 


 

 

 

 

 
typedef struct {
 uint32_t RESERVED0[1024];
 volatile uint32_t CONTROL;
 volatile uint32_t STATUS;
 volatile uint32_t ERROR;
 volatile uint32_t CommandWord1;
 volatile uint32_t CommandWord2;
 volatile uint32_t ModeData;
 volatile uint32_t StatusWord1;
 volatile uint32_t StatusWord2;
 volatile uint32_t INTEN;
 volatile uint32_t MSG;
} MDR_MIL_STD_1553_TypeDef;

 

 
 

 
 

 

 


 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 


 

 

 
typedef struct
{
 volatile uint32_t PVDCS;
}MDR_POWER_TypeDef;

 

 

 

 
 

 

 

 

 

 

 

 
typedef struct
{
 volatile uint32_t CR;
 volatile uint32_t CFR;
 volatile uint32_t SR;
}MDR_WWDG_TypeDef;

 

 

 

 
 

 

 

 

 
 

 

 

 

 

 

 

 
typedef struct
{
 volatile uint32_t KR;
 volatile uint32_t PR;
 volatile uint32_t RLR;
 volatile uint32_t SR;
}MDR_IWDG_TypeDef;

 

 

 

 
 

 

 

 

 


 

 

 

typedef struct {
 volatile uint32_t CNT;
 volatile uint32_t PSG;
 volatile uint32_t ARR;
 volatile uint32_t CNTRL;
 volatile uint32_t CCR1;
 volatile uint32_t CCR2;
 volatile uint32_t CCR3;
 volatile uint32_t CCR4;
 volatile uint32_t CH1_CNTRL;
 volatile uint32_t CH2_CNTRL;
 volatile uint32_t CH3_CNTRL;
 volatile uint32_t CH4_CNTRL;
 volatile uint32_t CH1_CNTRL1;
 volatile uint32_t CH2_CNTRL1;
 volatile uint32_t CH3_CNTRL1;
 volatile uint32_t CH4_CNTRL1;
 volatile uint32_t CH1_DTG;
 volatile uint32_t CH2_DTG;
 volatile uint32_t CH3_DTG;
 volatile uint32_t CH4_DTG;
 volatile uint32_t BRKETR_CNTRL;
 volatile uint32_t STATUS;
 volatile uint32_t IE;
 volatile uint32_t DMA_RE;
 volatile uint32_t CH1_CNTRL2;
 volatile uint32_t CH2_CNTRL2;
 volatile uint32_t CH3_CNTRL2;
 volatile uint32_t CH4_CNTRL2;
 volatile uint32_t CCR11;
 volatile uint32_t CCR21;
 volatile uint32_t CCR31;
 volatile uint32_t CCR41;
 volatile uint32_t DMA_REChx[4];
} MDR_TIMER_TypeDef;


 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 

 

 

 

typedef struct {
 volatile uint32_t ADC1_CFG; 
 volatile uint32_t ADC2_CFG; 
 volatile uint32_t ADC1_H_LEVEL; 
 volatile uint32_t RESERVED0; 
 volatile uint32_t ADC1_L_LEVEL; 
 volatile uint32_t RESERVED1; 
 volatile uint32_t ADC1_RESULT; 
 volatile uint32_t RESERVED2; 
 volatile uint32_t ADC1_STATUS; 
 volatile uint32_t RESERVED3; 
 volatile uint32_t ADC1_CHSEL; 
 volatile uint32_t RESERVED4; 
 volatile uint32_t ADC1_TRIM; 
} MDR_ADC_TypeDef;

 

 

 

 

 
 

 

 


 

 
 

 

 


 

 


 


 

 
 

 

 

 

 
 

 

 

 

 

 

 

 

typedef struct {
 volatile uint32_t CFG;
 volatile uint32_t DAC1_DATA;
 volatile uint32_t DAC2_DATA;
} MDR_DAC_TypeDef;

 

 

 

 

 
 

 

 


 

 

 

 
 

 

 



 

 

 

 
 

 

 



 

 

 

 

 

typedef struct {
 volatile uint32_t RXTX;
 volatile uint32_t OE;
 volatile uint32_t FUNC;
 volatile uint32_t ANALOG;
 volatile uint32_t PULL;
 volatile uint32_t PD;
 volatile uint32_t PWR;
 volatile uint32_t GFEN;
 volatile uint32_t SETTX;
 volatile uint32_t CLRTX;
 volatile uint32_t RDTX;
} MDR_PORT_TypeDef;


 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 

 

 

 
typedef struct
{
 volatile uint32_t CONTROL1;
 volatile uint32_t CONTROL2;
 volatile uint32_t CONTROL3;
 volatile uint32_t STATUS1;
 volatile uint32_t STATUS2;
 volatile uint32_t CONTROL4;
 volatile uint32_t CONTROL5;
 volatile uint32_t CHANNEL;
 volatile uint32_t LABEL;
 volatile uint32_t DATA_R;
 uint32_t RESERVED1[2];
 volatile uint32_t DATA_R_Direct[8];
 uint32_t RESERVED2[6];
 volatile uint32_t INTMASK;
}MDR_ARINC429R_TypeDef;

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 

 

 

 
typedef struct
{
 volatile uint32_t CONTROL1;
 volatile uint32_t CONTROL2;
 volatile uint32_t STATUS;
 volatile uint32_t DATA1_T;
 volatile uint32_t DATA2_T;
 volatile uint32_t DATA3_T;
 volatile uint32_t DATA4_T;
 volatile uint32_t CONTROL3;
}MDR_ARINC429T_TypeDef;

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 

 

 

 
typedef struct
{
 volatile uint32_t REG_00;
 volatile uint32_t REG_01;
 volatile uint32_t REG_02;
 volatile uint32_t REG_03;
 volatile uint32_t REG_04;
 volatile uint32_t REG_05;
 volatile uint32_t REG_06;
 volatile uint32_t REG_07;
 volatile uint32_t REG_08;
 volatile uint32_t REG_09;
 volatile uint32_t REG_0A;
 volatile uint32_t REG_0B;
 volatile uint32_t REG_0C;
 volatile uint32_t REG_0D;
 volatile uint32_t REG_0E;
 volatile uint32_t REG_0F;
 volatile uint32_t RTC_CNT;
 volatile uint32_t RTC_DIV;
 volatile uint32_t RTC_PRL;
 volatile uint32_t RTC_ALRM;
 volatile uint32_t RTC_CS;
}MDR_BKP_TypeDef;

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 

 

 

 
typedef struct
{
 uint32_t RESERVED0[20];
 volatile uint32_t NAND_CYCLES;
 volatile uint32_t CONTROL;
 volatile uint32_t MEM_REGION[4];
}MDR_EBC_TypeDef;

 

 

 

 
 

 

 


 

 
 

 

 


 

 
 

 

 

 

 

 

 

typedef struct {
 volatile uint16_t ETH_Dilimiter; 
 volatile uint16_t ETH_MAC_T; 
 volatile uint16_t ETH_MAC_M; 
 volatile uint16_t ETH_MAC_H; 
 volatile uint16_t ETH_HASH0; 
 volatile uint16_t ETH_HASH1; 
 volatile uint16_t ETH_HASH2; 
 volatile uint16_t ETH_HASH3; 
 volatile uint16_t ETH_IPG; 
 volatile uint16_t ETH_PSC; 
 volatile uint16_t ETH_BAG; 
 volatile uint16_t ETH_JitterWnd; 
 volatile uint16_t ETH_R_CFG; 
 volatile uint16_t ETH_X_CFG; 
 volatile uint16_t ETH_G_CFGl; 
 volatile uint16_t ETH_G_CFGh; 
 volatile uint16_t ETH_IMR; 
 volatile uint16_t ETH_IFR; 
 volatile uint16_t ETH_MDIO_CTRL; 
 volatile uint16_t ETH_MDIO_DATA; 
 volatile uint16_t ETH_R_Head; 
 volatile uint16_t ETH_X_Tail; 
 volatile uint16_t ETH_R_Tail; 
 volatile uint16_t ETH_X_Head; 
 volatile uint16_t ETH_STAT; 
 volatile uint16_t Reserved; 
 volatile uint16_t PHY_Control; 
 volatile uint16_t PHY_Status; 
} MDR_ETHERNET_TypeDef;

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 
 

 

 

 

 




 


 

 


 

 

 

 

 

 

 
 









 







 




 
 
 

 



 
 
 

 
 
 









typedef struct
{
 uint32_t CPU_CLK_Frequency;
 uint32_t USB_CLK_Frequency;
 uint32_t ADC_CLK_Frequency;
 uint32_t RTCHSI_Frequency;
 uint32_t RTCHSE_Frequency;
} RST_CLK_FreqTypeDef;

 



typedef struct
{
 uint32_t REG_0F;
} Init_NonVolatile_RST_CLK_TypeDef;













 








 









 








 








 




 









 









 








 








 








 








 








 







 







 










 








 


 








 













 
 
 

 
 
 

 
 
 








 



typedef enum
{
 PORT_OE_IN = 0x0,
 PORT_OE_OUT = 0x1
}PORT_OE_TypeDef;


 



typedef enum
{
 PORT_MODE_ANALOG = 0x0,
 PORT_MODE_DIGITAL = 0x1
}PORT_MODE_TypeDef;


 



typedef enum
{
 PORT_PULL_UP_OFF = 0x0,
 PORT_PULL_UP_ON = 0x1
}PORT_PULL_UP_TypeDef;


 



typedef enum
{
 PORT_PULL_DOWN_OFF = 0x0,
 PORT_PULL_DOWN_ON = 0x1
}PORT_PULL_DOWN_TypeDef;


 



typedef enum
{
 PORT_PD_SHM_OFF = 0x0,
 PORT_PD_SHM_ON = 0x1
}PORT_PD_SHM_TypeDef;


 



typedef enum
{
 PORT_PD_DRIVER = 0x0,
 PORT_PD_OPEN = 0x1
}PORT_PD_TypeDef;


 



typedef enum
{
 PORT_GFEN_OFF = 0x0,
 PORT_GFEN_ON = 0x1
}PORT_GFEN_TypeDef;


 



typedef enum
{
 PORT_FUNC_PORT = 0x0,
 PORT_FUNC_MAIN = 0x1,
 PORT_FUNC_ALTER = 0x2,
 PORT_FUNC_OVERRID = 0x3
}PORT_FUNC_TypeDef;


 



typedef enum
{
 PORT_OUTPUT_OFF = 0x0,
 PORT_SPEED_SLOW = 0x1,
 PORT_SPEED_FAST = 0x2,
 PORT_SPEED_MAXFAST = 0x3
}PORT_SPEED_TypeDef;


 



typedef struct
{
 uint16_t PORT_Pin; 
 PORT_OE_TypeDef PORT_OE; 
 PORT_PULL_UP_TypeDef PORT_PULL_UP; 
 PORT_PULL_DOWN_TypeDef PORT_PULL_DOWN; 
 PORT_PD_SHM_TypeDef PORT_PD_SHM; 
 PORT_PD_TypeDef PORT_PD; 
 PORT_GFEN_TypeDef PORT_GFEN; 
 PORT_FUNC_TypeDef PORT_FUNC; 
 PORT_SPEED_TypeDef PORT_SPEED; 
 PORT_MODE_TypeDef PORT_MODE; 
}PORT_InitTypeDef;

 




typedef enum
{
 Bit_RESET = 0,
 Bit_SET
}BitAction;
















 



 































 






















































































































typedef struct {
 uint32_t MIL_STD_1553_Mode; 
 uint32_t MIL_STD_1553_RERR; 
 uint32_t MIL_STD_1553_DIV; 
 uint32_t MIL_STD_1553_RTA; 
 uint32_t MIL_STD_1553_TRB; 
 uint32_t MIL_STD_1553_TRA; 

 
 FunctionalState MIL_STD_1553_Inversion_Signals; 
 FunctionalState MIL_STD_1553_Filtration_Flow; 
 FunctionalState MIL_STD_1553_Automatic_Adjustment; 
} MIL_STD_1553_InitTypeDef;

 



typedef union {
 uint32_t NumberDataWords :5; 
 uint32_t Cmd :5; 
} Data_FieldsTypeDef;

 


typedef struct {
 
 uint32_t Data :5; 
 uint32_t Subaddress :5; 
 uint32_t ReadWriteBit :1; 
 uint32_t TerminalDeviceAddress :5; 
} MIL_STD_1553_CommandWordBitFields;

 


typedef union {
 uint32_t CommandWord; 
 MIL_STD_1553_CommandWordBitFields Fields; 
} MIL_STD_1553_CommandWordTypeDef;

 


typedef struct {
 uint32_t FaultTDBit :1; 
 uint32_t AdoptionControlInterfaceBit :1; 
 uint32_t AbonentFaultBit :1; 
 uint32_t BusyBit :1; 
 uint32_t GroupCommandBit :1; 
 uint32_t Reserved :3; 
 uint32_t ServiceRequestBit :1; 
 uint32_t TransferReplyWordBit :1; 
 uint32_t ErrorBit :1; 
 uint32_t TerminalDeviceAddress :5; 
} MIL_STD_1553_StatusWordBitFields;

 


typedef union {
 uint32_t StatusWord; 
 MIL_STD_1553_StatusWordBitFields Fields; 
} MIL_STD_1553_StatusWordTypeDef;

 


typedef enum {
 FALSE = 0,
 TRUE = !DISABLE
} Bool;
















 







 






 






 






 



 






 






 




 



















 





 



















































 
 
 

 
 
 














 







































































 
 
 

 
 
 









typedef struct {

 uint32_t TIMER_IniCounter; 
 uint16_t TIMER_Prescaler; 
 uint32_t TIMER_Period; 
 uint16_t TIMER_CounterMode; 
 uint16_t TIMER_CounterDirection;
 uint16_t TIMER_EventSource; 
 uint16_t TIMER_FilterSampling; 
 uint16_t TIMER_ARR_UpdateMode; 
 uint16_t TIMER_ETR_FilterConf; 
 uint16_t TIMER_ETR_Prescaler; 
 uint16_t TIMER_ETR_Polarity; 
 uint16_t TIMER_BRK_Polarity; 
} TIMER_CntInitTypeDef;

 


typedef struct
{
 uint16_t TIMER_CH_Number; 
 uint16_t TIMER_CH_Mode; 
 uint16_t TIMER_CH_ETR_Ena; 
 uint16_t TIMER_CH_ETR_Reset; 
 uint16_t TIMER_CH_BRK_Reset; 
 uint16_t TIMER_CH_REF_Format; 
 uint16_t TIMER_CH_Prescaler; 
 uint16_t TIMER_CH_EventSource; 
 uint16_t TIMER_CH_FilterConf; 
 uint16_t TIMER_CH_CCR_UpdateMode; 
 uint16_t TIMER_CH_CCR1_Ena; 
 uint16_t TIMER_CH_CCR1_EventSource; 
} TIMER_ChnInitTypeDef;

 


typedef struct
{
 uint16_t TIMER_CH_Number; 
 uint16_t TIMER_CH_DirOut_Polarity; 
 uint16_t TIMER_CH_DirOut_Source; 
 uint16_t TIMER_CH_DirOut_Mode; 
 uint16_t TIMER_CH_NegOut_Polarity; 
 uint16_t TIMER_CH_NegOut_Source; 
 uint16_t TIMER_CH_NegOut_Mode; 
 uint16_t TIMER_CH_DTG_MainPrescaler; 
 uint16_t TIMER_CH_DTG_AuxPrescaler; 
 uint16_t TIMER_CH_DTG_ClockSource; 
}TIMER_ChnOutInitTypeDef;














 






 






 






 






 






 






 






 






 






 






 






 






 




 






 











 






 






 






 






 






 






 






 








 






 













































 
 
 

 
 
 







typedef enum {BaudRateInvalid = 0, BaudRateValid = !BaudRateInvalid} BaudRateStatus;

 


typedef struct
{
 uint32_t UART_BaudRate; 
 
 
 uint16_t UART_WordLength; 
 uint16_t UART_StopBits; 
 uint16_t UART_Parity; 
 uint16_t UART_FIFOMode; 
 uint16_t UART_HardwareFlowControl; 
}UART_InitTypeDef;


















 






 






 






 







 






 






 






 






 







 








 































 




 




 



 




 



 




 











 
 
 

 
 
 








typedef struct
{
 uint32_t EBC_Mode; 
 uint8_t EBC_WaitState; 
 uint8_t EBC_NandTrc; 
 uint8_t EBC_NandTwc; 
 uint8_t EBC_NandTrea; 
 uint8_t EBC_NandTwp; 
 uint8_t EBC_NandTwhr; 
 uint8_t EBC_NandTalea; 
 uint8_t EBC_NandTrr; 
 uint8_t EBC_DataAlignment; 
 uint8_t EBC_UseMemRegion; 
}EBC_InitTypeDef;

 


typedef struct
{
 uint8_t Use_Ready; 
 uint8_t WS_Hold; 
 uint8_t WS_Setup; 
 uint8_t WS_Active; 
 uint8_t Enable_Tune; 
}EBC_MemRegionInitTypeDef;




















 







 








 








 







 







 








 








 























































































extern u32 ipause;



extern const u32 HCLK;
extern u32 maxpause_s;
extern u32 maxpause_ms;
extern u32 maxpause_mks;
extern const u32 PLL_MUL;



 

 










 

 















 







 







 
 
 

 

 
 

 

 

 

 





 












extern int Num_dv; 






 




 





 
 
 
 
 
 



typedef void * va_list;
 




 


void init_printf(void* putp,void (*putf) (void*,char));

void tfp_printf(char *fmt, ...);
void tfp_sprintf(char* s,char *fmt, ...);

void tfp_format(void* putp,void (*putf) (void*,char),char *fmt, va_list va);


















 







 













 









 







 












 







 







 
 
 

 

 
 

 

 

 

 





 





 




 














enum E_LED_PINS {
 LED1_pin = (1 << 0x7),
 LED2_pin = (1 << 0x8),
 LED3_pin = (1 << 0x9),
 LED4_pin = (1 << 0xA),
 LED5_pin = (1 << 0xB),
 LED6_pin = (1 << 0xC),
 LED7_pin = (1 << 0xD),
 LED8_pin = (1 << 0xE)
 };













 
typedef enum {
 LED0_OFS = 7,
 LED1_OFS = 8,
 LED2_OFS = 9,
 LED3_OFS = 10,
 LED4_OFS = 11,
 LED0_MASK = (1 << LED0_OFS),
 LED1_MASK = (1 << LED1_OFS),
 LED2_MASK = (1 << LED2_OFS),
 LED3_MASK = (1 << LED3_OFS),
 LED4_MASK = (1 << LED4_OFS),
 LEDS_MASK = (LED0_MASK | LED1_MASK | LED2_MASK | LED3_MASK | LED4_MASK)
} LEDS_Masks;

 

 
extern u32 CurrentLights;

 
void InitPortLED(void);
void ShiftLights(void);
void Lights(u32 mask);

 












 







 












 







 







 
 
 

 

 
 

 

 

 

 





 





 




 












 






void readButtonStates();

void mapFileProc();

void buttonLedsDemo();

void init_joystick_hw();

void prepareMapFile();


















extern u8 BUTTON_STATE_REGISTER;

enum E_BUTTON_PINS {
 RIGHT__BUTTON = (1 << 0x5),
 TOP____BUTTON = (1 << 0x8),
 SELECT_BUTTON = (1 << 0x9),
 LEFT___BUTTON = (1 << 0xA),
 BACK___BUTTON = (1 << 0xB),
 BOTTOM_BUTTON = (1 << 0xF),
 };



enum E_BUTTON_STATUS{
EBS_RELEASED = 0,
EBS_PRESSED = 1
};

















 















 







 












 







 







 
 
 

 

 
 

 

 

 

 





 





 




 












 






void procUART(void* data);

void initUART(MDR_UART_TypeDef* UARTx);



 











 







 







 
 
 

 

 
 

 

 

 

 





 





 








extern int M128Mark;

void Timer2Start();






 











 







 




 

 



 




void assemblePorts();









 
















 































































 






void initEvalboard();


 





 










 




void ClockInit();


void PortInit ();




 



void ClockInit(){


}


void PortInit (){

 ((MDR_PORT_TypeDef *)(0x400A8000) )->OE = 0x1540;
 ((MDR_PORT_TypeDef *)(0x400A8000) )->FUNC = 0x02222000;
 ((MDR_PORT_TypeDef *)(0x400A8000) )->ANALOG = 0xFFFF;
 ((MDR_PORT_TypeDef *)(0x400A8000) )->PULL = 0x0000EAB8;
 ((MDR_PORT_TypeDef *)(0x400A8000) )->PD = 0x00000000;
 ((MDR_PORT_TypeDef *)(0x400A8000) )->PWR = 0x02222000;
 ((MDR_PORT_TypeDef *)(0x400A8000) )->GFEN = 0x0000;


 ((MDR_PORT_TypeDef *)(0x400B0000) )->OE = 0x0000;
 ((MDR_PORT_TypeDef *)(0x400B0000) )->FUNC = 0x000AAAAA;
 ((MDR_PORT_TypeDef *)(0x400B0000) )->ANALOG = 0xFFFF;
 ((MDR_PORT_TypeDef *)(0x400B0000) )->PULL = 0x0000FC00;
 ((MDR_PORT_TypeDef *)(0x400B0000) )->PD = 0x03FF0000;
 ((MDR_PORT_TypeDef *)(0x400B0000) )->PWR = 0x00000000;
 ((MDR_PORT_TypeDef *)(0x400B0000) )->GFEN = 0x0000;


 ((MDR_PORT_TypeDef *)(0x400B8000) )->OE = 0x0E08;
 ((MDR_PORT_TypeDef *)(0x400B8000) )->FUNC = 0x00000140;
 ((MDR_PORT_TypeDef *)(0x400B8000) )->ANALOG = 0xFFFF;
 ((MDR_PORT_TypeDef *)(0x400B8000) )->PULL = 0x000001E7;
 ((MDR_PORT_TypeDef *)(0x400B8000) )->PD = 0x00100000;
 ((MDR_PORT_TypeDef *)(0x400B8000) )->PWR = 0x00A80080;
 ((MDR_PORT_TypeDef *)(0x400B8000) )->GFEN = 0x0000;


 ((MDR_PORT_TypeDef *)(0x400C0000) )->OE = 0x0000;
 ((MDR_PORT_TypeDef *)(0x400C0000) )->FUNC = 0x00000000;
 ((MDR_PORT_TypeDef *)(0x400C0000) )->ANALOG = 0x807F;
 ((MDR_PORT_TypeDef *)(0x400C0000) )->PULL = 0x0000807F;
 ((MDR_PORT_TypeDef *)(0x400C0000) )->PD = 0x00000000;
 ((MDR_PORT_TypeDef *)(0x400C0000) )->PWR = 0x00000000;
 ((MDR_PORT_TypeDef *)(0x400C0000) )->GFEN = 0x0000;


 ((MDR_PORT_TypeDef *)(0x400C8000) )->RXTX = 0x0000;
 ((MDR_PORT_TypeDef *)(0x400C8000) )->OE = 0x87E5;
 ((MDR_PORT_TypeDef *)(0x400C8000) )->FUNC = 0x00155551;
 ((MDR_PORT_TypeDef *)(0x400C8000) )->ANALOG = 0xFFFF;
 ((MDR_PORT_TypeDef *)(0x400C8000) )->PULL = 0x00007802;
 ((MDR_PORT_TypeDef *)(0x400C8000) )->PD = 0x00180000;
 ((MDR_PORT_TypeDef *)(0x400C8000) )->PWR = 0x802AA822;
 ((MDR_PORT_TypeDef *)(0x400C8000) )->GFEN = 0x0000;


 ((MDR_PORT_TypeDef *)(0x400E8000) )->RXTX = 0x0001;
 ((MDR_PORT_TypeDef *)(0x400E8000) )->OE = 0x1E01;
 ((MDR_PORT_TypeDef *)(0x400E8000) )->FUNC = 0x03FC0000;
 ((MDR_PORT_TypeDef *)(0x400E8000) )->ANALOG = 0xFFFF;
 ((MDR_PORT_TypeDef *)(0x400E8000) )->PULL = 0x0000E1FE;
 ((MDR_PORT_TypeDef *)(0x400E8000) )->PD = 0x00000000;
 ((MDR_PORT_TypeDef *)(0x400E8000) )->PWR = 0x02A80002;
 ((MDR_PORT_TypeDef *)(0x400E8000) )->GFEN = 0x0000;



}



