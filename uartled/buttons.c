
 #include <buttons.h>



//u8 LED_STATUS_REGISTER;         //[{00000000}]
//u8 BUTTON_STATUS_REGISTER;      //[{000000}00]
u8 BUTTON_STATE_REGISTER = 0;       //[{000000}00]


void readButtonStates()
{
        WRITE_BUTTON_STATE(RIGHT__BUTTON ,RIGHT__BUTTON_Msk );
        WRITE_BUTTON_STATE(TOP____BUTTON ,TOP____BUTTON_Msk );
        WRITE_BUTTON_STATE(SELECT_BUTTON ,SELECT_BUTTON_Msk );
        WRITE_BUTTON_STATE(LEFT___BUTTON ,LEFT___BUTTON_Msk );
        WRITE_BUTTON_STATE(BACK___BUTTON ,BACK___BUTTON_Msk );
        WRITE_BUTTON_STATE(BOTTOM_BUTTON ,BOTTOM_BUTTON_Msk );

        //printf("%d\n",(int)MDR_PORTE->RXTX);
        //printf("%d\n",(int)BUTTON_STATE_REGISTER);

}

void mapFileProc()   {

}

void buttonLedsDemo()
{
        int bstate = READ_BUTTON_STATE(TOP____BUTTON_Msk);
        //printf ("top %d\n",bstate);
        if ( bstate != GET_LED_STATE(LED3_pin) )
               if (bstate) SWITCH_LED__ON(LED3_pin); else SWITCH_LED_OFF(LED3_pin);

        bstate = READ_BUTTON_STATE(RIGHT__BUTTON_Msk);
        //printf ("right %d\n",bstate);
        if ( bstate != GET_LED_STATE(LED4_pin) )
               if (bstate) SWITCH_LED__ON(LED4_pin); else SWITCH_LED_OFF(LED4_pin);

        bstate = READ_BUTTON_STATE(BOTTOM_BUTTON_Msk);
        //printf ("bottom %d\n",bstate);
        if ( bstate != GET_LED_STATE(LED5_pin) )
               if (bstate) SWITCH_LED__ON(LED5_pin); else SWITCH_LED_OFF(LED5_pin);

        bstate = READ_BUTTON_STATE(LEFT___BUTTON_Msk);
        //printf ("left %d\n",bstate);
        if ( bstate != GET_LED_STATE(LED6_pin) )
               if (bstate) SWITCH_LED__ON(LED6_pin); else SWITCH_LED_OFF(LED6_pin);

        bstate = READ_BUTTON_STATE(SELECT_BUTTON_Msk);
        if ( bstate != GET_LED_STATE(LED1_pin) || bstate != GET_LED_STATE(LED2_pin) )
               if (bstate) SWITCH_LED__ON(LED1_pin|LED2_pin); else SWITCH_LED_OFF(LED1_pin|LED2_pin);

        bstate = READ_BUTTON_STATE(BACK___BUTTON_Msk);
        if ( bstate != GET_LED_STATE(LED7_pin) || bstate != GET_LED_STATE(LED8_pin) )
               if (bstate) SWITCH_LED__ON(LED7_pin|LED8_pin); else SWITCH_LED_OFF(LED7_pin|LED8_pin);

}

void init_joystick_hw();

void prepareMapFile()
{

}

