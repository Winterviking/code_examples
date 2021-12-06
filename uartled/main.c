
#include <init.h>
#include <evalboard.h>
#include <driver.h>

void main ()
{
        int i;
        PC = 0;



        initEvalboard();


#ifdef EVALBOARD
#ifdef INTRO
        // INTRO
        // :D :D :D
        // :D :D :D
        SWITCH_LED__ON(LED1_pin|LED2_pin);
        DELAY_MS(400);
        SWITCH_LED_OFF(LED1_pin|LED2_pin);
        DELAY_MS(400);
        SWITCH_LED__ON(LED7_pin|LED8_pin);
        DELAY_MS(400);
        SWITCH_LED_OFF(LED7_pin|LED8_pin);
        DELAY_MS(400);


        for ( i = 3; i > 0; i-- )
        {
                SWITCH_LED__ON(LED1_pin);DELAY_MS(30);
                SWITCH_LED__ON(LED2_pin);DELAY_MS(30);
                SWITCH_LED__ON(LED3_pin);DELAY_MS(30);
                SWITCH_LED_OFF(LED1_pin);DELAY_MS(30);
                SWITCH_LED__ON(LED4_pin);DELAY_MS(30);
                SWITCH_LED_OFF(LED2_pin);DELAY_MS(30);
                SWITCH_LED__ON(LED5_pin);DELAY_MS(30);
                SWITCH_LED_OFF(LED3_pin);DELAY_MS(30);
                SWITCH_LED__ON(LED6_pin);DELAY_MS(30);
                SWITCH_LED_OFF(LED4_pin);DELAY_MS(30);
                SWITCH_LED__ON(LED7_pin);DELAY_MS(30);
                SWITCH_LED_OFF(LED5_pin);DELAY_MS(30);
                SWITCH_LED__ON(LED8_pin);DELAY_MS(30);
                SWITCH_LED_OFF(LED6_pin);DELAY_MS(30);
                SWITCH_LED_OFF(LED7_pin);DELAY_MS(30);
                SWITCH_LED_OFF(LED8_pin);DELAY_MS(30);

                SWITCH_LED__ON(LED8_pin);DELAY_MS(30);
                SWITCH_LED__ON(LED7_pin);DELAY_MS(30);
                SWITCH_LED__ON(LED6_pin);DELAY_MS(30);
                SWITCH_LED_OFF(LED8_pin);DELAY_MS(30);
                SWITCH_LED__ON(LED5_pin);DELAY_MS(30);
                SWITCH_LED_OFF(LED7_pin);DELAY_MS(30);
                SWITCH_LED__ON(LED4_pin);DELAY_MS(30);
                SWITCH_LED_OFF(LED6_pin);DELAY_MS(30);
                SWITCH_LED__ON(LED3_pin);DELAY_MS(30);
                SWITCH_LED_OFF(LED5_pin);DELAY_MS(30);
                SWITCH_LED__ON(LED2_pin);DELAY_MS(30);
                SWITCH_LED_OFF(LED4_pin);DELAY_MS(30);
                SWITCH_LED__ON(LED1_pin);DELAY_MS(30);
                SWITCH_LED_OFF(LED3_pin);DELAY_MS(30);
                SWITCH_LED_OFF(LED2_pin);DELAY_MS(30);
                SWITCH_LED_OFF(LED1_pin);DELAY_MS(30);
        }

        SWITCH_LED__ON(LED1_pin|LED2_pin|LED3_pin|LED4_pin|LED5_pin|LED6_pin|LED7_pin|LED8_pin);
        DELAY_MS(300);
        SWITCH_LED_OFF(LED1_pin|LED2_pin|LED3_pin|LED4_pin|LED5_pin|LED6_pin|LED7_pin|LED8_pin);

        printf("Project \"%s\" %s %s\n",PROJECT_NAME,VERSION,YEAR );
#endif
#endif

        while(1){
        // system
                PC++;
                DELAY_MS(250);
        // user



                // check button states
                readButtonStates(); // driver

                // Read and reset system timer CCR register to measure time ( dt ) /* future */

               buttonLedsDemo();

                // Check user timer)))))))
               MarkM4Routine();

        }
}










