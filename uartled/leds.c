

#include <leds.h>
#include <MDR1986VE1T.h>

// Маска включенных светодиодов
u32 CurrentLights;

// Сервисные утилиты

void InitPortLED(void) {
    MDR_PORTD->FUNC &= ~((0x3FF << (LED0_OFS << 1)));   // port
    MDR_PORTD->ANALOG |= LEDS_MASK;                     // digital
    MDR_PORTD->PWR |= (0x155 << (LED0_OFS << 1));       // slow
    MDR_PORTD->RXTX &= ~LEDS_MASK;
    MDR_PORTD->OE |= LEDS_MASK;
}

void ShiftLights(void) {
    u32 ovf;
    MDR_PORTD->RXTX = (MDR_PORTD->RXTX & ~LEDS_MASK) | (CurrentLights & LEDS_MASK);
    ovf = (CurrentLights & (1UL << 31)) != 0;
    CurrentLights <<= 1;
    CurrentLights |= ovf;
}


void Lights(u32 mask) {
    MDR_PORTD->RXTX = (MDR_PORTD->RXTX & ~LEDS_MASK) | (mask & LEDS_MASK);
}




