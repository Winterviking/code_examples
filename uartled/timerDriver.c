
#include <timerDriver.h>

int TC_Timer1;       // ������� ���������� Timer1
int TC_Timer2;       // ������� ���������� Timer2
int TC_Timer3;       // ������� ���������� Timer3
int TC_Timer4;       // ������� ���������� Timer4

int M128Mark;

// M4
/*
void Timer2Start(void)
{

//    MDR_RST_CLK->TIM_CLOCK = 0x07000000;
    MDR_RST_CLK->TIM_CLOCK |= RST_CLK_TIM_CLOCK_TIM2_CLK_EN;

    MDR_TIMER2->CNTRL = 0x00000000; //����� ������������� �������

    MDR_TIMER2->STATUS = 0x00000000; //

    //����������� ������ ��������� ��������
    MDR_TIMER2->CNT = 0x00000000; //��������� �������� ��������
    MDR_TIMER2->PSG = 48-1;       //������������ ������� (�� 1 ���) 0x2F
    MDR_TIMER2->ARR = 4096;       //��������� ����� (1 ��) 0x1068

//    MDR_TIMER2->IE = 0x00000000;
    MDR_TIMER2->IE = 0x00000001;

    //���������� ������ �������.
    MDR_TIMER2->CNTRL = 0x00000001; //���� ����� �� TIM_CLK

    NVIC_EnableIRQ(TIMER2_IRQn); // 15




   // DEBUG :::: fill fancy buffer

}*/

// TIMER 4 >> MARK 4

// TIMER 1/2 JOB






//
// �������� ������
//

//
// ��������� �������������� : �������� ENUM ��� ���������� ������ ���������.
//
 typedef enum{
  EPLM_SWITCH_OFF = 0,
  EPLM_WIRE_INTEGRITY_CHECK = 1,
  EPLM_NORMAL_OPERATION = 2
} E_PWM_LOAD_MODE;




void Timer1Select(E_PWM_LOAD_MODE Select)
{
   switch (Select) {
      case EPLM_SWITCH_OFF: {
         // � ������ �������� ����������� ����� ������� ��������� ��� ����������� ���������
         // ������ ����������
         MDR_TIMER1->CH3_CNTRL1 = 0x0001;
         MDR_TIMER1->CH4_CNTRL1 = 0x0001;
         break;
      }

      case EPLM_WIRE_INTEGRITY_CHECK: {
         // � ������ �������� ����������� ����� ������� ��������� ��� ����������� ���������
         // ������ ����������
         MDR_TIMER1->CH3_CNTRL1 = 0x0005;
         MDR_TIMER1->CH4_CNTRL1 = 0x0005;
         break;
      }

      case EPLM_NORMAL_OPERATION: {
         // � ������ ���������� ����������
         // ���������� ������ ������� REF �� ��������������� ������ ��, ��������� � ��������
         MDR_TIMER1->CH3_CNTRL1 = 0x0009;
         MDR_TIMER1->CH4_CNTRL1 = 0x0009;
         break;
      }
   }
}





void Timer1Start(void)
//=================================================
{
    MDR_TIMER1->CNTRL = 0x00000000;  // 1) ���������� ������
    MDR_TIMER1->STATUS = 0x00000000; // 2) ����������� ������� �������

    //����������� ������ ��������� ��������
    MDR_TIMER1->PSG = 0x002F;        // 3) ����������� ������� 48 ��� ��������� �������� ������� ��������� �������� ������� 1 ���
    MDR_TIMER1->CNT = 0x00000001;    // 4) ��������� �������� ��������
    MDR_TIMER1->ARR = 0xFFFFFFFF;    // 5) ��������� ����� (������������ ������)

    //6)
    MDR_TIMER1->CCR2 =  0x00000000;
    MDR_TIMER1->CCR3 =  0x00000000;
    MDR_TIMER1->CCR31 = 0x00000000;
    MDR_TIMER1->CCR4  = 0x00000000;
    MDR_TIMER1->CCR41 = 0x00000000;

    MDR_TIMER1->CH1_CNTRL = 0x8000;  // 7) ��������� ������ 1 ������� 1 � ������ �������
    MDR_TIMER1->CH1_CNTRL1 = 0x0000; // 8) ������ ������ ���-�������� �� ������ ������ 1 �������
    MDR_TIMER1->CH1_CNTRL2 = 0x0;    // 9) ������ ������������� CCR1

    MDR_TIMER1->CH2_CNTRL = 0x0200;  // 10) ��������� ������ 2 ������� 1 � ������ ���, REF=1 ��� CNT=CCR
    MDR_TIMER1->CH2_CNTRL1 = 0x0000; // 11) ������ ������ ���-�������� �� ������ ������ 2 �������
    MDR_TIMER1->CH2_CNTRL2 = 0x0;    // 12) ������ ������������� CCR1

    MDR_TIMER1->CH3_CNTRL = 0x0E00;  // 13) ��������� ������ 3 ������� 1 � ������ ���, REF=1 ��� CCR< CNT< CCR1
    MDR_TIMER1->CH4_CNTRL = 0x0E00;  // 13) ��������� ������ 4 ������� 1 � ������ ���, REF=1 ��� CCR< CNT< CCR1

    MDR_TIMER1->CH3_CNTRL1 = 0x0001; // 14) ��������� ������������� ������� (������ ����������- 0x0001)
    MDR_TIMER1->CH4_CNTRL1 = 0x0001; // 14) ��������� ������������� ������� (������ ����������- 0x0001)

    MDR_TIMER1->CH3_CNTRL2 = 0x4;    // 15) ���������� ������������� CCR1, ���������� ���������� CCR � CCR1 � ����� ������ �������
    MDR_TIMER1->CH4_CNTRL2 = 0x4;    // 15) ���������� ������������� CCR1, ���������� ���������� CCR � CCR1 � ����� ������ �������

    MDR_TIMER1->IE = 0x00000;        // 16) ������ ���������� �� ������� 1
    MDR_TIMER1->DMA_RE = 0x00000;    // 11) ������ �������� �� ��� �� ������� 1
    MDR_TIMER1->CNTRL = 0x00000001;  // 16) ��������� ������ �������

    NVIC_EnableIRQ(TIMER1_IRQn); // 14
}





//=================================================
// ������������� ������� 2
// INPUT:  -                                                       // ������� ���������
// OUTPUT: MDR_TIMER2(CNTRL, CNT, PSG, ARR, STATUS, IE,
//         CH1_CNTRL-CH4_CNTRL, CH1_CNTRL1-CH4_CNTRL1, CH1_CNTRL2-CH4_CNTRL2,
//         CCR1-CCR4, CCR11-CCR31                                  // �������� ���������
// TMP:                                                            // ���������� ������
void Timer2Start(void)
//=================================================
{
    MDR_TIMER2->CNTRL = 0x00000000;  // 1) ���������� ������
    MDR_TIMER2->STATUS = 0x00000000; // 2) c������� ����������� ������� �������

    //����������� ������ ��������� ��������
    MDR_TIMER2->PSG = 0x002F;        // 3) ����������� ������� 48 ��� ��������� �������� ������� ��������� �������� ������� 1 ���
    MDR_TIMER2->CNT = 0x00000000;    // 4) ��������� �������� ��������
    MDR_TIMER2->ARR = 0xFFFFFFF0;    // 5) ��������� �����

    // 6)
    MDR_TIMER2->CCR1  = 0xFFFFFFFF;
    MDR_TIMER2->CCR11 = 0xFFFFFFFF;

    MDR_TIMER2->CCR2  = 0xFFFFFFFF;
    MDR_TIMER2->CCR21 = 0xFFFFFFFF;

    MDR_TIMER2->CCR3  = 0xFFFFFFFF;
    MDR_TIMER2->CCR31 = 0xFFFFFFFF;

    MDR_TIMER2->CCR4  = 0xFFFFFFFF;
    MDR_TIMER2->CCR41 = 0xFFFFFFFF;

    // 7) ��������� ���� ������� ������� 2 � ������ ���, REF=1 ��� CCR< CNT< CCR1
    MDR_TIMER2->CH1_CNTRL = 0x0E00;
    MDR_TIMER2->CH2_CNTRL = 0x0E00;
    MDR_TIMER2->CH3_CNTRL = 0x0E00;
    MDR_TIMER2->CH4_CNTRL = 0x0E00;

    // 8) ��� ��������� ������������� ������� - 0x0005 (������ ����������)
    MDR_TIMER2->CH1_CNTRL1 = 0x0005;
    MDR_TIMER2->CH2_CNTRL1 = 0x0005;
    MDR_TIMER2->CH3_CNTRL1 = 0x0005;
    MDR_TIMER2->CH4_CNTRL1 = 0x0005;

    // 9) ���������� ������������� CCR1, ���������� ���������� CCR � CCR1 � ����� �����
    MDR_TIMER2->CH1_CNTRL2 = 0x4;
    MDR_TIMER2->CH2_CNTRL2 = 0x4;
    MDR_TIMER2->CH3_CNTRL2 = 0x4;
    MDR_TIMER2->CH4_CNTRL2 = 0x4;

    MDR_TIMER2->IE = 0x00000000;     // 10) ������ ���� ���������� ������� 2
    MDR_TIMER2->DMA_RE = 0x00000;    // 11) ������ �������� �� ��� �� ������� 2

//    MDR_TIMER2->CNTRL = 0x00000001;  // ��������� ������ �������

//    NVIC_EnableIRQ(TIMER2_IRQn); // 15
}





void Timer2Select(E_PWM_LOAD_MODE Select)
{
   switch (Select) {
      case EPLM_SWITCH_OFF: {
         // ��� �������� ����������� ����� ��������������� �������� �������� ��� ����������� ���������
         // ������ ����������
         MDR_TIMER2->CH1_CNTRL1 = 0x0005;
         MDR_TIMER2->CH2_CNTRL1 = 0x0005;
         MDR_TIMER2->CH3_CNTRL1 = 0x0005;
         MDR_TIMER2->CH4_CNTRL1 = 0x0005;
         break;
      }

      case EPLM_WIRE_INTEGRITY_CHECK: {
         // ��� �������� ����������� ����� ��������������� �������� �������� ��� ����������� ���������
         // ������ ����������
         MDR_TIMER2->CH1_CNTRL1 = 0x0001;
         MDR_TIMER2->CH2_CNTRL1 = 0x0001;
         MDR_TIMER2->CH3_CNTRL1 = 0x0001;
         MDR_TIMER2->CH4_CNTRL1 = 0x0001;
         break;
      }

      case EPLM_NORMAL_OPERATION: {
         // � ������ ���������� ����������
         // ���������� ������ ���-�������� � ��������� �� ��������������� ������ ��
         MDR_TIMER2->CH1_CNTRL1 = 0x0019;
         MDR_TIMER2->CH2_CNTRL1 = 0x0019;
         MDR_TIMER2->CH3_CNTRL1 = 0x0019;
         MDR_TIMER2->CH4_CNTRL1 = 0x0019;
        break;
      }
   }
}


//=================================================
// ������������� ������� 4
// INPUT:  -                                                       // ������� ���������
// OUTPUT: MDR_TIMER4(CNTRL, CNT, PSG, ARR, STATUS, IE,
//         CH1_CNTRL-CH4_CNTRL, CH1_CNTRL1-CH4_CNTRL1, CH1_CNTRL2-CH4_CNTRL2,
//         CCR1-CCR4, CCR11-CCR31,
//         CNTM4                                                   // �������� ���������
// TMP:                                                            // ���������� ������
void Timer4Start(void)
//=================================================
{
    MDR_TIMER4->CNTRL = 0x00000000;  // 1) ���������� ������

    //����������� ������ ��������� ��������
    MDR_TIMER4->PSG = 0x002F;        // 2) ������������ ������� =48 (1 ���);
    MDR_TIMER4->CNT = 0x00000002;    // 3) ��������� �������� �������� (����� ������ ����� ���� �� � "00" � ��� ������ ����� �� ����������� ���� "CNT ZERO EVENT")
    MDR_TIMER4->ARR = 0x00001FF;     // 4) ��������� ����� (512 �������� �� 1 ��� = 512 ���, ��� ������������� ������� ������� ������� ���-1716 � 1,95 ���)

    // 5) ��������� ���������������� ������ ������� 4 � ������ ���, OCCM=7
    MDR_TIMER4->CH1_CNTRL = 0x0E00;
    MDR_TIMER4->CH2_CNTRL = 0x0E00;
    MDR_TIMER4->CH3_CNTRL = 0x0E00;
    MDR_TIMER4->CH4_CNTRL = 0x0E00;

    // 6) ���������� ������ ���-�������� �� ��������������� ������ ��
    MDR_TIMER4->CH1_CNTRL1 = 0x0009;
    MDR_TIMER4->CH2_CNTRL1 = 0x0009;
    MDR_TIMER4->CH3_CNTRL1 = 0x0009;
    MDR_TIMER4->CH4_CNTRL1 = 0x0009;

    // 7) ���������� ������������� CCR1, ���������� ���������� CCR � CCR1 ������ ��� CNT=0
    MDR_TIMER4->CH1_CNTRL2 = 0xC;
    MDR_TIMER4->CH2_CNTRL2 = 0xC;
    MDR_TIMER4->CH3_CNTRL2 = 0xC;
    // 8) ������ ������������� CCR1, ���������� ���������� CCR � CCR1 � ����� ������ �������
    MDR_TIMER4->CH4_CNTRL2 = 0x0;

    MDR_TIMER4->CCR1  = 0x00000040;  //  9) �����  64 ���
    MDR_TIMER4->CCR2  = 0x00000080;  // 10) ����� 128 ���
    MDR_TIMER4->CCR3  = 0x000000C0;  // 11) ����� 192 ���
    MDR_TIMER4->CCR11 = 0x00000140;  // 12) ����� 320 ���
    MDR_TIMER4->CCR21 = 0x00000180;  // 13) ����� 384 ���
    MDR_TIMER4->CCR31 = 0x000001C0;  // 14) ����� 448 ���

    MDR_TIMER4->CCR4 = 0x00000000;   // 16) ����� 0 ��� ��������������� ������ ������� ����� 128 ��� � �������� ����� 4 ��

    MDR_TIMER4->IE = 0x00001001;     // 17) ���������� ���������� ������� 4 �� ����������� ��������� ������ REF ������ 4 � ��� CNT=0
    MDR_TIMER4->CNTRL = 0x0001;      // 18) ��������� ������ �������

    MDR_TIMER4->STATUS = 0x00000000; // 19) �������� ����������� ������� �������

    NVIC_EnableIRQ(TIMER4_IRQn);     // 1.2.2.2 ���������������� ���������� ����������.
}




//=================================================
// ���������� ���������� Timer1
//=================================================
//void Timer1_IRQHandler(void) {
//    MDR_TIMER1->STATUS&=~1;
//
//    TC_Timer1++;
//}



//=================================================
// ���������� ���������� Timer2
//=================================================
void Timer2_IRQHandler(void) {
    MDR_TIMER2->STATUS&=~1;

    TC_Timer2++;
}



//=================================================
// ���������� ���������� Timer3
//=================================================
void Timer3_IRQHandler(void) {
    MDR_TIMER3->STATUS&=~1;

    TC_Timer3++;
}

//=================================================
// ���������� ���������� Timer4
//=================================================
void Timer4_IRQHandler(void)
{
    // 128 mks
    MDR_TIMER4->STATUS&=~1;

    M128Mark = 1;

    TC_Timer4++;
}















































