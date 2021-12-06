
#include "timers.h"
#include <avr/io.h>
#include <Arduino.h>

void init_timer0() {
    TCCR0 = TCCR0_CS_TIMER_DIV_8 | 
			TCCR0_WGM0_FAST_PWM | 
			TCCR0_COM0_FAST_PWM_NORMAL_OPERATION;
    OCR0 = 255;

    TIMSK |= TIMSK_MASK_OCIE0;
    TCNT0 = 0;
}
