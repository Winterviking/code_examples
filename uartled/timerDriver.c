
#include <timerDriver.h>

int TC_Timer1;       // Счетчик прерываний Timer1
int TC_Timer2;       // Счетчик прерываний Timer2
int TC_Timer3;       // Счетчик прерываний Timer3
int TC_Timer4;       // Счетчик прерываний Timer4

int M128Mark;

// M4
/*
void Timer2Start(void)
{

//    MDR_RST_CLK->TIM_CLOCK = 0x07000000;
    MDR_RST_CLK->TIM_CLOCK |= RST_CLK_TIM_CLOCK_TIM2_CLK_EN;

    MDR_TIMER2->CNTRL = 0x00000000; //Режим инициализации таймера

    MDR_TIMER2->STATUS = 0x00000000; //

    //Настраиваем работу основного счетчика
    MDR_TIMER2->CNT = 0x00000000; //Начальное значение счетчика
    MDR_TIMER2->PSG = 48-1;       //Предделитель частоты (по 1 мкс) 0x2F
    MDR_TIMER2->ARR = 4096;       //Основание счета (1 мс) 0x1068

//    MDR_TIMER2->IE = 0x00000000;
    MDR_TIMER2->IE = 0x00000001;

    //Разрешение работы таймера.
    MDR_TIMER2->CNTRL = 0x00000001; //Счет вверх по TIM_CLK

    NVIC_EnableIRQ(TIMER2_IRQn); // 15




   // DEBUG :::: fill fancy buffer

}*/

// TIMER 4 >> MARK 4

// TIMER 1/2 JOB






//
// ИСХОДНЫЕ ДАННЫЕ
//

//
// Программа модифицирована : добавлен ENUM для унификации старта двигателя.
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
         // в режиме контроля целостности цепей катушек зажигания при выключенном двигателе
         // снятие напряжения
         MDR_TIMER1->CH3_CNTRL1 = 0x0001;
         MDR_TIMER1->CH4_CNTRL1 = 0x0001;
         break;
      }

      case EPLM_WIRE_INTEGRITY_CHECK: {
         // в режиме контроля целостности цепей катушек зажигания при выключенном двигателе
         // подача напряжения
         MDR_TIMER1->CH3_CNTRL1 = 0x0005;
         MDR_TIMER1->CH4_CNTRL1 = 0x0005;
         break;
      }

      case EPLM_NORMAL_OPERATION: {
         // в режиме управления двигателем
         // разрешение выдачи сигнала REF на соответствующие выводы ЦП, связанные с таймером
         MDR_TIMER1->CH3_CNTRL1 = 0x0009;
         MDR_TIMER1->CH4_CNTRL1 = 0x0009;
         break;
      }
   }
}





void Timer1Start(void)
//=================================================
{
    MDR_TIMER1->CNTRL = 0x00000000;  // 1) Остановить таймер
    MDR_TIMER1->STATUS = 0x00000000; // 2) запомненные события таймера

    //Настраиваем работу основного счетчика
    MDR_TIMER1->PSG = 0x002F;        // 3) коэффициент деления 48 для получения тактовой частоты основного счётчика таймера 1 МГц
    MDR_TIMER1->CNT = 0x00000001;    // 4) Начальное значение счетчика
    MDR_TIMER1->ARR = 0xFFFFFFFF;    // 5) Основание счета (максимальный период)

    //6)
    MDR_TIMER1->CCR2 =  0x00000000;
    MDR_TIMER1->CCR3 =  0x00000000;
    MDR_TIMER1->CCR31 = 0x00000000;
    MDR_TIMER1->CCR4  = 0x00000000;
    MDR_TIMER1->CCR41 = 0x00000000;

    MDR_TIMER1->CH1_CNTRL = 0x8000;  // 7) включение канала 1 Таймера 1 в режиме захвата
    MDR_TIMER1->CH1_CNTRL1 = 0x0000; // 8) запрет выдачи ШИМ-сигналов на выводы канала 1 таймера
    MDR_TIMER1->CH1_CNTRL2 = 0x0;    // 9) запрет использования CCR1

    MDR_TIMER1->CH2_CNTRL = 0x0200;  // 10) включение канала 2 Таймера 1 в режиме ШИМ, REF=1 при CNT=CCR
    MDR_TIMER1->CH2_CNTRL1 = 0x0000; // 11) запрет выдачи ШИМ-сигналов на выводы канала 2 таймера
    MDR_TIMER1->CH2_CNTRL2 = 0x0;    // 12) запрет использования CCR1

    MDR_TIMER1->CH3_CNTRL = 0x0E00;  // 13) включение канала 3 Таймера 1 в режиме ШИМ, REF=1 при CCR< CNT< CCR1
    MDR_TIMER1->CH4_CNTRL = 0x0E00;  // 13) включение канала 4 Таймера 1 в режиме ШИМ, REF=1 при CCR< CNT< CCR1

    MDR_TIMER1->CH3_CNTRL1 = 0x0001; // 14) начальная инициализация таймера (снятие напряжения- 0x0001)
    MDR_TIMER1->CH4_CNTRL1 = 0x0001; // 14) начальная инициализация таймера (снятие напряжения- 0x0001)

    MDR_TIMER1->CH3_CNTRL2 = 0x4;    // 15) разрешение использования CCR1, разрешение обновления CCR и CCR1 в любой момент времени
    MDR_TIMER1->CH4_CNTRL2 = 0x4;    // 15) разрешение использования CCR1, разрешение обновления CCR и CCR1 в любой момент времени

    MDR_TIMER1->IE = 0x00000;        // 16) запрет прерываний от Таймера 1
    MDR_TIMER1->DMA_RE = 0x00000;    // 11) запрет запросов на ПДП от Таймера 1
    MDR_TIMER1->CNTRL = 0x00000001;  // 16) Разрешить работу таймера

    NVIC_EnableIRQ(TIMER1_IRQn); // 14
}





//=================================================
// Инициализация Таймера 2
// INPUT:  -                                                       // Входные параметры
// OUTPUT: MDR_TIMER2(CNTRL, CNT, PSG, ARR, STATUS, IE,
//         CH1_CNTRL-CH4_CNTRL, CH1_CNTRL1-CH4_CNTRL1, CH1_CNTRL2-CH4_CNTRL2,
//         CCR1-CCR4, CCR11-CCR31                                  // Выходные параметры
// TMP:                                                            // Глобальные данные
void Timer2Start(void)
//=================================================
{
    MDR_TIMER2->CNTRL = 0x00000000;  // 1) Остановить таймер
    MDR_TIMER2->STATUS = 0x00000000; // 2) cбросить запомненные события таймера

    //Настраиваем работу основного счетчика
    MDR_TIMER2->PSG = 0x002F;        // 3) коэффициент деления 48 для получения тактовой частоты основного счётчика таймера 1 МГц
    MDR_TIMER2->CNT = 0x00000000;    // 4) Начальное значение счетчика
    MDR_TIMER2->ARR = 0xFFFFFFF0;    // 5) Основание счета

    // 6)
    MDR_TIMER2->CCR1  = 0xFFFFFFFF;
    MDR_TIMER2->CCR11 = 0xFFFFFFFF;

    MDR_TIMER2->CCR2  = 0xFFFFFFFF;
    MDR_TIMER2->CCR21 = 0xFFFFFFFF;

    MDR_TIMER2->CCR3  = 0xFFFFFFFF;
    MDR_TIMER2->CCR31 = 0xFFFFFFFF;

    MDR_TIMER2->CCR4  = 0xFFFFFFFF;
    MDR_TIMER2->CCR41 = 0xFFFFFFFF;

    // 7) включение всех каналов Таймера 2 в режиме ШИМ, REF=1 при CCR< CNT< CCR1
    MDR_TIMER2->CH1_CNTRL = 0x0E00;
    MDR_TIMER2->CH2_CNTRL = 0x0E00;
    MDR_TIMER2->CH3_CNTRL = 0x0E00;
    MDR_TIMER2->CH4_CNTRL = 0x0E00;

    // 8) при начальной инициализации таймера - 0x0005 (снятие напряжения)
    MDR_TIMER2->CH1_CNTRL1 = 0x0005;
    MDR_TIMER2->CH2_CNTRL1 = 0x0005;
    MDR_TIMER2->CH3_CNTRL1 = 0x0005;
    MDR_TIMER2->CH4_CNTRL1 = 0x0005;

    // 9) разрешение использования CCR1, разрешение обновления CCR и CCR1 в любое время
    MDR_TIMER2->CH1_CNTRL2 = 0x4;
    MDR_TIMER2->CH2_CNTRL2 = 0x4;
    MDR_TIMER2->CH3_CNTRL2 = 0x4;
    MDR_TIMER2->CH4_CNTRL2 = 0x4;

    MDR_TIMER2->IE = 0x00000000;     // 10) запрет всех прерываний таймера 2
    MDR_TIMER2->DMA_RE = 0x00000;    // 11) запрет запросов на ПДП от Таймера 2

//    MDR_TIMER2->CNTRL = 0x00000001;  // Разрешить работу таймера

//    NVIC_EnableIRQ(TIMER2_IRQn); // 15
}





void Timer2Select(E_PWM_LOAD_MODE Select)
{
   switch (Select) {
      case EPLM_SWITCH_OFF: {
         // при контроле целостности цепей электромагнитов клапанов форсунок при выключенном двигателе
         // снятие напряжения
         MDR_TIMER2->CH1_CNTRL1 = 0x0005;
         MDR_TIMER2->CH2_CNTRL1 = 0x0005;
         MDR_TIMER2->CH3_CNTRL1 = 0x0005;
         MDR_TIMER2->CH4_CNTRL1 = 0x0005;
         break;
      }

      case EPLM_WIRE_INTEGRITY_CHECK: {
         // при контроле целостности цепей электромагнитов клапанов форсунок при выключенном двигателе
         // подача напряжения
         MDR_TIMER2->CH1_CNTRL1 = 0x0001;
         MDR_TIMER2->CH2_CNTRL1 = 0x0001;
         MDR_TIMER2->CH3_CNTRL1 = 0x0001;
         MDR_TIMER2->CH4_CNTRL1 = 0x0001;
         break;
      }

      case EPLM_NORMAL_OPERATION: {
         // в режиме управления двигателем
         // разрешение выдачи ШИМ-сигналов с инверсией на соответствующие выводы ЦП
         MDR_TIMER2->CH1_CNTRL1 = 0x0019;
         MDR_TIMER2->CH2_CNTRL1 = 0x0019;
         MDR_TIMER2->CH3_CNTRL1 = 0x0019;
         MDR_TIMER2->CH4_CNTRL1 = 0x0019;
        break;
      }
   }
}


//=================================================
// Инициализация Таймера 4
// INPUT:  -                                                       // Входные параметры
// OUTPUT: MDR_TIMER4(CNTRL, CNT, PSG, ARR, STATUS, IE,
//         CH1_CNTRL-CH4_CNTRL, CH1_CNTRL1-CH4_CNTRL1, CH1_CNTRL2-CH4_CNTRL2,
//         CCR1-CCR4, CCR11-CCR31,
//         CNTM4                                                   // Выходные параметры
// TMP:                                                            // Глобальные данные
void Timer4Start(void)
//=================================================
{
    MDR_TIMER4->CNTRL = 0x00000000;  // 1) Остановить таймер

    //Настраиваем работу основного счетчика
    MDR_TIMER4->PSG = 0x002F;        // 2) Предделитель частоты =48 (1 МГц);
    MDR_TIMER4->CNT = 0x00000002;    // 3) Начальное значение счетчика (чтобы таймер начал счёт не с "00" и при начале счёта не установился флаг "CNT ZERO EVENT")
    MDR_TIMER4->ARR = 0x00001FF;     // 4) Основание счета (512 отсчётов по 1 мкс = 512 мкс, что соответствует частоте питания датчика ЛДТ-1716 в 1,95 кГц)

    // 5) включение соответствующего канала Таймера 4 в режиме ШИМ, OCCM=7
    MDR_TIMER4->CH1_CNTRL = 0x0E00;
    MDR_TIMER4->CH2_CNTRL = 0x0E00;
    MDR_TIMER4->CH3_CNTRL = 0x0E00;
    MDR_TIMER4->CH4_CNTRL = 0x0E00;

    // 6) разрешение выдачи ШИМ-сигналов на соответствующие выводы ЦП
    MDR_TIMER4->CH1_CNTRL1 = 0x0009;
    MDR_TIMER4->CH2_CNTRL1 = 0x0009;
    MDR_TIMER4->CH3_CNTRL1 = 0x0009;
    MDR_TIMER4->CH4_CNTRL1 = 0x0009;

    // 7) разрешение использования CCR1, разрешение обновления CCR и CCR1 только при CNT=0
    MDR_TIMER4->CH1_CNTRL2 = 0xC;
    MDR_TIMER4->CH2_CNTRL2 = 0xC;
    MDR_TIMER4->CH3_CNTRL2 = 0xC;
    // 8) запрет использования CCR1, разрешение обновления CCR и CCR1 в любой момент времени
    MDR_TIMER4->CH4_CNTRL2 = 0x0;

    MDR_TIMER4->CCR1  = 0x00000040;  //  9) точка  64 мкс
    MDR_TIMER4->CCR2  = 0x00000080;  // 10) точка 128 мкс
    MDR_TIMER4->CCR3  = 0x000000C0;  // 11) точка 192 мкс
    MDR_TIMER4->CCR11 = 0x00000140;  // 12) точка 320 мкс
    MDR_TIMER4->CCR21 = 0x00000180;  // 13) точка 384 мкс
    MDR_TIMER4->CCR31 = 0x000001C0;  // 14) точка 448 мкс

    MDR_TIMER4->CCR4 = 0x00000000;   // 16) точка 0 мкс соответствующая началу первого цикла 128 мкс в пределах метки 4 мс

    MDR_TIMER4->IE = 0x00001001;     // 17) разрешение прерываний таймера 4 по обнаружению переднего фронта REF канала 4 и при CNT=0
    MDR_TIMER4->CNTRL = 0x0001;      // 18) Разрешить работу таймера

    MDR_TIMER4->STATUS = 0x00000000; // 19) сбросить запомненные события таймера

    NVIC_EnableIRQ(TIMER4_IRQn);     // 1.2.2.2 Инициализировать контроллер прерываний.
}




//=================================================
// Обработчик прерывания Timer1
//=================================================
//void Timer1_IRQHandler(void) {
//    MDR_TIMER1->STATUS&=~1;
//
//    TC_Timer1++;
//}



//=================================================
// Обработчик прерывания Timer2
//=================================================
void Timer2_IRQHandler(void) {
    MDR_TIMER2->STATUS&=~1;

    TC_Timer2++;
}



//=================================================
// Обработчик прерывания Timer3
//=================================================
void Timer3_IRQHandler(void) {
    MDR_TIMER3->STATUS&=~1;

    TC_Timer3++;
}

//=================================================
// Обработчик прерывания Timer4
//=================================================
void Timer4_IRQHandler(void)
{
    // 128 mks
    MDR_TIMER4->STATUS&=~1;

    M128Mark = 1;

    TC_Timer4++;
}















































