

#ifndef __LEDS_H_INCLUDED__
#define __LEDS_H_INCLUDED__

#include <types.h>
#include <config.h>
#include <includer.h>
#include <printf.h>


// LED PART

enum E_LED_PINS {
 LED1_pin            = (1 << PORT_PIN_NUMBER_07),
 LED2_pin            = (1 << PORT_PIN_NUMBER_08),
 LED3_pin            = (1 << PORT_PIN_NUMBER_09),
 LED4_pin            = (1 << PORT_PIN_NUMBER_10),
 LED5_pin            = (1 << PORT_PIN_NUMBER_11),
 LED6_pin            = (1 << PORT_PIN_NUMBER_12),
 LED7_pin            = (1 << PORT_PIN_NUMBER_13),
 LED8_pin            = (1 << PORT_PIN_NUMBER_14)
 };

#define SWITCH_LED__ON(led) SWITCH_PIN__ON(MDR_PORTD,led)
#define SWITCH_LED_OFF(led) SWITCH_PIN_OFF(MDR_PORTD,led)
#define GET_LED_STATE(led) GET_PIN_STATE(MDR_PORTD,led)

#define UART1_ACTIVITY__ON      MDR_PORTD->SETTX = LED1_pin|LED2_pin;
#define UART1_ACTIVITY_OFF      MDR_PORTD->CLRTX = LED1_pin|LED2_pin;






// ??????




/* Смещения в регистре и маски для конкретных светодиодов */
typedef enum {
    LED0_OFS    = 7,
    LED1_OFS    = 8,
    LED2_OFS    = 9,
    LED3_OFS    = 10,
    LED4_OFS    = 11,
    LED0_MASK   = (1 << LED0_OFS),
    LED1_MASK   = (1 << LED1_OFS),
    LED2_MASK   = (1 << LED2_OFS),
    LED3_MASK   = (1 << LED3_OFS),
    LED4_MASK   = (1 << LED4_OFS),
    LEDS_MASK   = (LED0_MASK | LED1_MASK | LED2_MASK | LED3_MASK | LED4_MASK)
} LEDS_Masks;

/* ROL */
#define __SHLC(val, cnt) ((val << (cnt & 31)) | (val >> ((32 - cnt) & 31)))

/* Маска включенных светодиодов */
extern u32 CurrentLights;

/* Сервисные утилиты */
void InitPortLED(void);
void ShiftLights(void);
void Lights(u32 mask);

#endif // End of __LEDS_H_INCLUDED__


