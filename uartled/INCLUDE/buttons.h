
#ifndef __BUTTONS_H_INCLUDED__
#define __BUTTONS_H_INCLUDED__

#include <config.h>
#include <includer.h>
#include <printf.h>
#include <leds.h>



void readButtonStates();

void mapFileProc();

void buttonLedsDemo();

void init_joystick_hw();

void prepareMapFile();








// GENERIC PART         printf("%d\n",(int)MDR_PORTE->RXTX);
#define GET_PIN_STATE(port,pin) ((port->RXTX & pin) != 0)
#define SWITCH_PIN__ON(port,pin) port->SETTX = pin
#define SWITCH_PIN_OFF(port,pin) port->CLRTX = pin






// BUTTON PART

// button registers
extern u8 BUTTON_STATE_REGISTER;

enum E_BUTTON_PINS {
 RIGHT__BUTTON        = (1 << PORT_PIN_NUMBER_05),
 TOP____BUTTON        = (1 << PORT_PIN_NUMBER_08),
 SELECT_BUTTON        = (1 << PORT_PIN_NUMBER_09),
 LEFT___BUTTON        = (1 << PORT_PIN_NUMBER_10),
 BACK___BUTTON        = (1 << PORT_PIN_NUMBER_11),
 BOTTOM_BUTTON        = (1 << PORT_PIN_NUMBER_15),
 };

#define RIGHT__BUTTON_Pos       0x0
#define TOP____BUTTON_Pos       0x1
#define SELECT_BUTTON_Pos       0x2
#define LEFT___BUTTON_Pos       0x3
#define BACK___BUTTON_Pos       0x4
#define BOTTOM_BUTTON_Pos       0x5

#define RIGHT__BUTTON_Msk       0x01
#define TOP____BUTTON_Msk       0x02
#define SELECT_BUTTON_Msk       0x04
#define LEFT___BUTTON_Msk       0x08
#define BACK___BUTTON_Msk       0x10
#define BOTTOM_BUTTON_Msk       0x20

enum E_BUTTON_STATUS{
EBS_RELEASED    = 0,
EBS_PRESSED     = 1
};

#define GET_BUTTON_STATE(button) (!GET_PIN_STATE(MDR_PORTE,button))
#define WRITE_BUTTON_STATE(button,msk) BUTTON_STATE_REGISTER = GET_BUTTON_STATE(button) ? (BUTTON_STATE_REGISTER | msk) : (BUTTON_STATE_REGISTER & ~msk)
#define READ_BUTTON_STATE(msk) (((BUTTON_STATE_REGISTER & msk) != EBS_RELEASED) ? (EBS_PRESSED) : (EBS_RELEASED))
















#endif // End of __BUTTONS_H_INCLUDED__

