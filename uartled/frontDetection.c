
#include <includer.h>
#include <frontDetection.h>

//
// Возможно будут добавлены ещё фазы : может быть пару оборотов дать стартёру покрутиться
//
//
//




//
//
// Определения
//
//
 typedef enum{
  ECSS_IDLE             = 0,
  ECSS_INIT_SYNC        = 1,
  ECSS_PRE_SYNC         = 2,
  ECSS_EMERGENCY_SYNC   = 3,
  ECSS_PRIMARY_SYNC     = 4,
  ECSS_SECONDARY_SYNC   = 5,
  ECSS_NORMAL_OPERATION = 6
} E_CRANKSHAFT_SENSOR_STATUS;



//
//
// Базовая конфигурация
//


#define CRANKSHAFT_BUFFER 60

// игнорируем помехи
#define CRANKSHAFT_TEETH 34
#define CRANKSHAFT_TEETH_MIN 32
#define CRANKSHAFT_TEETH_MAX 36

#define CRANKSHAFT_MAX_INTEGRAL_ERROR 3600

//
//
// Переменные счётчика
//
//

u32 CTz; // счётчик зубчиков
u32 TZp; // расстояние между последними зубками
u32 ZCC; // счётчик зубок в режиме синхронизации
u32 SRCntr; // служебный счётчик оборотов ( переход в рабочий режим )


u32 Zaccum[CRANKSHAFT_BUFFER]; // буфер почти кольцевой >> затираем напрямую
u32 Zptr; // указатель кольцевого буфера

u32 Zperiod; // последний зафиксированный период ()
u32 lastTooth;

// основной регистр состояния автомата
E_CRANKSHAFT_SENSOR_STATUS  ecss_status;
u32 integral_error;


//
//
// Синхронизация >> >> >>
//
//

// инициализация синхронизации ( включаем прерывания по 1му каналу )
#define INIT_SYNC       MDR_TIMER1->IE = 0x0020

// REF вывод, передний фронт, 2 канал  ( прерывания по 1 и 2 каналам включены )
#define INIT_PRIMARY_SYNC     MDR_TIMER1->IE = 0x0420




//
//
// главный обработчик прерывания
// определяем источник и реализуем текущую фазу
//

void Timer1_IRQHandler(void) {
    u32 bufZ;
    u32 istantPERIOD; // correction
    // сохраняем и сбрасываем текущий статус
    u32 INTERRUPT_TIMER_STATUS = MDR_TIMER1->STATUS;
    MDR_TIMER1->STATUS&=~1;

    if ( (INTERRUPT_TIMER_STATUS & TIMER_STATUS_CCR_CAP_CH1) > 0 )
    {
        // всегда не зависимо от состояния считаем величину зуба)
        // тут же перенастраиваем второй канал на 1.5 длины последнего зуба
        bufZ = MDR_TIMER1->CCR1 - TZp;

        Zaccum[Zptr] = bufZ;
        MDR_TIMER1->CCR2 = TZp + bufZ + (bufZ >> 1);
        TZp = MDR_TIMER1->CCR1;

        Zptr++;


        switch ( ecss_status ){
            case ECSS_IDLE:
                // ignore or error
            break;
            case ECSS_INIT_SYNC:
                ZCC = 0;
                ecss_status = ECSS_PRE_SYNC;
            break;
            case ECSS_PRE_SYNC:
                ZCC++;
                if ( ZCC == 2 ){
                    INIT_PRIMARY_SYNC;// запуск прерывания по пропущеным зубкам
                    ecss_status = ECSS_PRIMARY_SYNC;
                }

            break;
            case ECSS_EMERGENCY_SYNC:// сброс ШИМа
                MDR_TIMER1->CCR3 = 0;
                MDR_TIMER1->CCR4 = 0;
                MDR_TIMER1->CCR31 = 0;
                MDR_TIMER1->CCR41 = 0;

                MDR_TIMER2->CCR1 = 0;
                MDR_TIMER2->CCR2 = 0;
                MDR_TIMER2->CCR3 = 0;
                MDR_TIMER2->CCR4 = 0;
                MDR_TIMER2->CCR11 = 0;
                MDR_TIMER2->CCR21 = 0;
                MDR_TIMER2->CCR31 = 0;
                MDR_TIMER2->CCR41 = 0;

                SRCntr = 0;
                ecss_status = ECSS_PRIMARY_SYNC;
                integral_error = 0;

            break;
            case ECSS_PRIMARY_SYNC:

            break;
            case ECSS_SECONDARY_SYNC:
                CTz++;

            break;
            case ECSS_NORMAL_OPERATION:
                CTz++;
            break;
        };



    }else if ( (MDR_TIMER1->STATUS & TIMER_STATUS_CCR_REF_CH2) > 0 ){



        istantPERIOD = (Zaccum[Zptr - 1] - lastTooth)*36;
        lastTooth = Zaccum[Zptr - 1];
        Zptr = 0;

        // period estimation
        Zperiod = MDR_TIMER1->CCR1 + ((istantPERIOD>0)?(1):(-1))*(((istantPERIOD>0)?(istantPERIOD):(-istantPERIOD))>>1);

        SRCntr++;

        switch ( ecss_status ){
            case ECSS_IDLE:
                // ignore or error
            break;
            case ECSS_INIT_SYNC:
                // ignore or error
            break;
            case ECSS_PRIMARY_SYNC:
                // ignore or error
            break;
            case ECSS_SECONDARY_SYNC:
                if (SRCntr == 3) ecss_status = ECSS_NORMAL_OPERATION;
            break;
            case ECSS_NORMAL_OPERATION:
                ecss_status = ( ((CRANKSHAFT_TEETH_MIN <= CTz) && (CTz <= CRANKSHAFT_TEETH_MAX)) || (CTz == 0) ) ? ECSS_NORMAL_OPERATION : ECSS_EMERGENCY_SYNC; // защита от помех ( кулибин эдишн )

                if ( CRANKSHAFT_TEETH != CTz ) integral_error++;
                else integral_error = 0;

                if (CRANKSHAFT_MAX_INTEGRAL_ERROR < integral_error ) ecss_status = ECSS_EMERGENCY_SYNC;

                // базовое вычисление ШИМ - периодов на следующий цикл .. соотв. переинициализация таймеров :)
                MDR_TIMER2->CNT = 0x00000000;

                // ШИМ ТЕСТОВЫЙ
                MDR_TIMER1->CCR3 = Zperiod >>1;
                MDR_TIMER1->CCR4 = Zperiod >>1;
                MDR_TIMER1->CCR31 = Zperiod >>1 + Zperiod >>2;
                MDR_TIMER1->CCR41 = Zperiod >>1 + Zperiod >>2;

                MDR_TIMER2->CCR1 = Zperiod >>1;
                MDR_TIMER2->CCR2 = Zperiod >>1;
                MDR_TIMER2->CCR3 = Zperiod >>1;
                MDR_TIMER2->CCR4 = Zperiod >>1;
                MDR_TIMER2->CCR11 = Zperiod >>1 + Zperiod >>2;
                MDR_TIMER2->CCR21 = Zperiod >>1 + Zperiod >>2;
                MDR_TIMER2->CCR31 = Zperiod >>1 + Zperiod >>2;
                MDR_TIMER2->CCR41 = Zperiod >>1 + Zperiod >>2;

            break;
        };
        CTz = 0;// сбрасываем счётчик зубьев
        MDR_TIMER1->CNT = 0x00000000; // сбрасываем первый таймер в 0
    }
}















//
//
// Вызвать до зажигания
//
//

void initFrontDetectionModule(){
        u32 i;

        // обнуляем служебные переменные
        CTz = 0;
        TZp = 0;
        ZCC = 0;
        SRCntr = 0;

        for ( i = 0; i < CRANKSHAFT_BUFFER; i++ ) {Zaccum[i] = 0;}

        Zptr = 0;

        Zperiod = 0;
        lastTooth = 0;

        ecss_status = ECSS_INIT_SYNC;
        integral_error = 0;

        //
        // если нужно дать стартёру раскрутиться, стоит это убрать. начинает искать сразу
        //
        INIT_SYNC;
}






