
#ifndef __TIMER_DRIVER_H_INCLUDED__
#define __TIMER_DRIVER_H_INCLUDED__

#include <includer.h>



//extern int TC_Timer2;       // —четчик прерываний Timer2
extern int M128Mark;

void Timer2Start();


 typedef enum{
  EPLM_SWITCH_OFF = 0,
  EPLM_WIRE_INTEGRITY_CHECK = 1,
  EPLM_NORMAL_OPERATION = 2
} E_PWM_LOAD_MODE;


#endif // End of __TIMER_DRIVER_H_INCLUDED__

