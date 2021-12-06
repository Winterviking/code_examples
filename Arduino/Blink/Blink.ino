//
// тесты :: точка входа с кучей мусора
// в устройстве использовалась Atmega128 <= где памяти было гораздо больше, чем в скромной Atmega162

#include <Arduino.h>
#include "atmega162.h"
//#include <LiquidCrystal.h>
//#include <avr/pgmspace.h>
#include "lcd1602_rus.h"
#include "buttons.h"
#include "user_timers.h"
#include "menu_library.h"

#include "kkm_library.h"


#include "eeprom_driver.h"

#include <avr/io.h>

#define SHOW_MANIPULATION_STATUSES
//#define KKM_LIB_CONNECTED
//#define __ONE_TIME_INPUT_DUMP__
#define __ACTUAL_CHECK_PRINTING__

 
//const int lcd_rs = 10, lcd_rw = 11, lcd_en = 12, lcd_d4 = 1, lcd_d5 = 2, lcd_d6 = 3, lcd_d7 = 4;
const int lcd_rs = 32, lcd_rw = 33, lcd_en = 34, lcd_d4 = 10, lcd_d5 = 11, lcd_d6 = 12, lcd_d7 = 13;
//const int lcd_rs = 32, lcd_rw = 33, lcd_en = 34, lcd_d4 = 1, lcd_d5 = 2, lcd_d6 = 3, lcd_d7 = 4;
//LiquidCrystal lcd(lcd_rs, lcd_rw, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7);
lcd1602_rus lcd(lcd_rs, lcd_rw, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7);
//LiquidCrystal_1602_RUS lcd(lcd_rs, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7);

//
// Fonts :) 
// 
const byte smiley[8] PROGMEM = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};


//
//
// add types
//
//

typedef enum{
  ESS_TEST,
  ESS_MENU,
  ESS_BLOCK_INPUT_MENU,
  ESS_SCAN,
  ESS_WORKOUT,
  ESS_PRINT
} E_SYSTEM_STATE;

E_SYSTEM_STATE ess_state;



//
//
// TIMER
//
//

uint8_t pina;
uint8_t pinc;
uint8_t flipper;
uint16_t btn_delayer;



SIGNAL(TIMER0_COMP_vect) {
  TCNT0 = 0;
//  digitalWrite(0, HIGH);
  inc_gen_loop_counter();
  inc_independent_counter();

  if ( independent_counter > 8191 ){
      inc_independent_counter_multiplier();
      reset_independent_counter();
  }

  inc_independent_counter2();

  if ( independent_counter2 > 8191 ){
      inc_independent_counter_multiplier2();
      reset_independent_counter2();
  }


  if ( ess_state == ESS_MENU ){
    btn_delayer++;
    if (btn_delayer > 4){
      buttons_read(); 
  
      btn_delayer = 0;
    }
  } else if ( ess_state == ESS_SCAN ){
    if (buttons_wakeup()){
      ess_state = ESS_BLOCK_INPUT_MENU;
      reset_gen_loop_counter();
      menu_changed = 1;
    }
  } else if (ess_state == ESS_WORKOUT){
 //   Serial.print(independent_counter_multiplier2);
    if (independent_counter_multiplier2 > 2){
      ess_state = ESS_PRINT;
      reset_independent_counter_multiplier2();
      reset_independent_counter2();
    }
  }
  
//  if ( ess_state == ESS_SCAN){
//    pina = PINA;
//    pinc = PINC;
//  }
/*  
    if (flipper){
    Serial.write(pina);
  } else {
    Serial.write(pinc);
    Serial.write(0b10011001);
  }
  
  flipper = !flipper;
*/

//  digitalWrite(0, LOW);
}


void show_manipulation_button_statuses(){
  if (button_up_status == HIGH){
    lcd.setCursor(12,1);
    lcd.print("1");
  }else{
    lcd.setCursor(12,1);
    lcd.print("0");
  }
  if (button_down_status == HIGH){
    lcd.setCursor(13,1);
    lcd.print("1");
  }else{
    lcd.setCursor(13,1);
    lcd.print("0");
  }
  if (button_ok_status == HIGH){
    lcd.setCursor(14,1);
    lcd.print("1");
  }else{
    lcd.setCursor(14,1);
    lcd.print("0");
  }
  if (button_cancel_status == HIGH){
    lcd.setCursor(15,1);
    lcd.print("1");
  }else{
    lcd.setCursor(15,1);
    lcd.print("0");
  }  
}



//
//
// WORKFLOW
//
//






int startflag;



//
//
// DEBUG MARSHALLING
//
//
int STOP_FLAG;





// the setup function runs once when you press reset or power the board
void setup() {

  byte arr[8];
  byte* arr_ptr; 


  cli();

  // initialize digital pin 13 as an output.
  pinMode(0, OUTPUT);
  Serial.begin(115200);
//  Serial.println("start");

  //
  // !!! PERIPHETAL !!!
  //



  const int a[EBA_MAX_NUMBER] = {1,2,3,4};
  init_buttons(a); // up down ok cancel
  //init_timer0();
  init_usertimer_system();

  init_menu_library(&lcd);

  add_event_receiver(EBA_UP, &up_keypressed);
  add_event_receiver(EBA_DOWN, &down_keypressed);
  add_event_receiver(EBA_OK, &ok_keypressed);
  add_event_receiver(EBA_CANCEL, &cancel_keypressed);

//  buttons[EBA_UP]._event_receivers_keypressed[0] = up_keypressed;
//  buttons[EBA_DOWN]._event_receivers_keypressed[0] = down_keypressed;


  pina = 0;
  pinc = 0;
  flipper = 0;
  btn_delayer = 0;

  //
  // !!! LCD !!!
  //

  arr_ptr = &arr[0];

  memcpy_P( arr_ptr, smiley, 8 );
  lcd.createChar(0, arr_ptr);
  lcd.createChar(1, arr_ptr);
  lcd.createChar(2, arr_ptr);
  lcd.createChar(3, arr_ptr);
  lcd.createChar(4, arr_ptr);
  lcd.createChar(5, arr_ptr);
  lcd.createChar(6, arr_ptr);
  lcd.createChar(7, arr_ptr);

  lcd.begin();
  lcd.clear();

//  lcd.print(L"воруй, убивай,");
//  lcd.NextLine();
//  lcd.print(L"еби гусей!");

  lcd.print(L"строка а");
  lcd.NextLine();
  lcd.print(L"строка б");

  DDRA = 0b00000000;// input
  DDRC = 0b00000000;// input

  PORTA = 0b11111111;// pullup 
  PORTC = 0b11111111;// pullup


  sei();

  // DEBUG_MARSHALLING
  //writePage();
  STOP_FLAG = 0;
  startflag = 0;

  ess_state = ESS_MENU;
}

//#undef main




//!!!!
const wchar_t blank_line[17] PROGMEM = L"                ";


//int menu_transition_timeout;
int flukstart = 0;
byte buff[10]; 

int button_num = 0;

int main(){
  setup();

//  menu_transition_timeout = 0;
  uint8_t jjjp;
  while (1){
//    uint8_t porta = PINA;
    switch ( ess_state ){
      case ESS_TEST:
      break;
      case ESS_MENU:
            digitalWrite(0, HIGH);
            render_menu();
            digitalWrite(0, LOW);
            
            jjjp = ~PINA;
            if ((jjjp&0b00000001) > 0){
              lcd.setCursor(10,1);
              lcd.print("0");
              if (!startflag){
                cli();
                
                print_progmem_string (0);
                //print_progmem_string (1);
                //print_progmem_string_with_int (2,1);
                //print_progmem_string (3);
                //print_progmem_string_with_int(4,button_num);
                //print_progmem_string (5);
                //print_progmem_string_with_string(6,L"OK");
                //print_progmem_string (7);
                //print_progmem_string (8);
                //print_progmem_string_with_int(9,pina);
                //print_progmem_string_with_int(10,pinc);
                //print_progmem_string (11);
        
                //send_cmd(cutoff,7);  
                sei();
                startflag = 1;
              }
            }
            else{
              lcd.setCursor(10,1);
              lcd.print("1");  
            }
          
#ifdef SHOW_MANIPULATION_STATUSES
            show_manipulation_button_statuses();
#endif  

            if ( independent_counter_multiplier > 10 ){
              ess_state = ESS_SCAN;
            }
      break;
      case ESS_BLOCK_INPUT_MENU:
        if(buttons_not_pressed()){ 
          ess_state = ESS_MENU;
          reset_independent_counter_multiplier;
        }
      break;
      case ESS_SCAN:

        
      break;
      case ESS_WORKOUT:
      break;   
      case ESS_PRINT:
        digitalWrite(0, LOW);

#ifdef __ACTUAL_CHECK_PRINTING__
        print_progmem_string (0);
        print_progmem_string (1);
        print_progmem_string_with_int (2,1);
        print_progmem_string (3);
        print_progmem_string_with_int(4,button_num);
        print_progmem_string (5);
        print_progmem_string_with_string(6,L"OK");
        print_progmem_string (7);
        print_progmem_string (8);
        print_progmem_string_with_int(9,pina);
        print_progmem_string_with_int(10,pinc);
        print_progmem_string (11);

        send_cmd(cutoff,7);
#endif


        //Serial.println("print state");
        //Serial.println(button_num);
        delay(10);
        ess_state = ESS_SCAN;
      break;   
    };
    
    if(ess_state == ESS_SCAN){
      lcd.setCursor(0,0);
      lcd.print_progmem((wchar_t*)blank_line);
      lcd.NextLine();
      lcd.print_progmem((wchar_t*)blank_line);

//
// EEPROM STOPFLAG TEST MARSHALLING DEBUG
//
      /*if (!STOP_FLAG){
        wchar_t* localstring = L"you noob";
        int ls_length = 9;
        uint32_t localnum = 1010101;
        for (int m = 0; m < ls_length; m++){
          page_container_buffer.data.text.text16[m] = localstring[m];
        }
        page_container_buffer.data.number.number32 = localnum;

        page_container_pointer = 11;

        writePage();
        clear_page_container_buffer();

        read_page_container(page_container_pointer);

        Serial.println(page_container_buffer.data.number.number32);
        debug_output_english_string(page_container_buffer.data.text.text16);
        debug_output_english_string(L"you noobyie");
        
        STOP_FLAG = 1;  
      }*/


      

      



#ifdef __ONE_TIME_INPUT_DUMP__
      int flipparrr = 0;

      for(;;){
        pina = ~(PINA);
        pinc = ~(PINC);
        if(flipparrr)
          {Serial.write(pina);}
        else {
          Serial.write(pinc);
          Serial.write(0b10011001);
        }
        flipparrr = 1 - flipparrr;
      }
#endif
      
      for(;;){
        pina = ~(PINA);
        pinc = ~(PINC);
        //Serial.print("+");

        button_num = 0;
        if ( pinc & 0b00000100 ){
          if ( pina & 0b00000001 ) {
            button_num = 1;
          } 
          if ( pina & 0b00000010 ) {
            button_num = 2;
          } 
          if ( pina & 0b00000100 ) {
            button_num = 3;
          } 
          if ( pina & 0b00001000 ) {
            button_num = 4;
          } 
          if ( pina & 0b00010000 ) {
            button_num = 5;
          } 
          if ( pina & 0b00100000 ) {
            button_num = 6;
          } 
          if ( pina & 0b01000000 ) {
            button_num = 7;
          } 
          if ( pina & 0b10000000 ) {
            button_num = 8;
          } 
        }

        
        if ( pinc & 0b00001000 ){
          if ( pina & 0b00000001 ) button_num = 9;
          if ( pina & 0b00000010 ) button_num = 10;
          if ( pina & 0b00000100 ) button_num = 11; 
        }

        if ( button_num > 0 ){
          digitalWrite(0, HIGH);
          ess_state = ESS_WORKOUT;
          reset_independent_counter2;
          reset_independent_counter_multiplier2;
          //digitalWrite(0, LOW);
        }
        
        if(ess_state != ESS_SCAN)break;
      }


        
      
      if (ess_state == ESS_BLOCK_INPUT_MENU ){
        lcd.setCursor(0,0);
        lcd.print(L"отпусти кнопку");
  
        lcd.setCursor(0,1);      
      }else{
//        lcd.setCursor(0,0);
//        lcd.print("printed");  
      }
    }
  
  }

  return 1;
}
