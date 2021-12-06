
//
// Проверочный интегральный модуль для отображения меню на 1602 экране
// позволяет вводить и выводить данные
// в дальнейшем был добавлен слой абстракции 
// нну а тут "помойка функциональности")


#include "menu_library.h"
#include "eeprom_driver.h"
#include "user_timers.h"


//menu_list_item menu_items[MENU_ITEM_COUNT];

lcd1602_rus* lcd_lib;
menu_item curr_item;

int time_transition_status;

int error_flag;


E_MENU_STATUS menu_status;
int menu_position;
int menu_changed;

void render_menu();







void proc_int_display(void* data) {

}






void (*proc_int)(void*);
void (*proc_int_loop)(void*);

//int menu_int_input;
const int menu_int_input_min = 0;
const int menu_int_input_default = 20;
const int menu_int_input_max = 50;

int menu_int_input_buffer;

typedef enum {
  EMIIS_INTRO,
  EMIIS_INPUT,
  //  EMIIS_PROC,
  EMIIS_OUTRO_GOOD,
  EMIIS_OUTRO_BAD,
  EMIIS_DROP
} E_MENU_INT_INPUT_STATUS;

E_MENU_INT_INPUT_STATUS menu_int_input_status;


int lib_int_input(E_BUTTONS_AVAILABLE btn, void* data) {

  switch (menu_int_input_status) {
    //    case EMIIS_INTRO:
    case EMIIS_INPUT:
      switch (btn) {
        case EBA_UP:
          if ( menu_int_input_buffer < menu_int_input_max ) {
            menu_int_input_buffer++;
            menu_changed = 1;
          }
          break;
        case EBA_DOWN:
          if ( menu_int_input_min < menu_int_input_buffer ) {
            menu_int_input_buffer--;
            menu_changed = 1;
          }
          break;
        case EBA_OK:

          if (proc_int != 0) {
            proc_int(0);
          } else {
            menu_int_input_status = EMIIS_OUTRO_GOOD;
            menu_changed = 1;
          }

          break;
        case EBA_CANCEL:

          if (proc_int != 0) {
            proc_int(0);
          } else {
            menu_int_input_status = EMIIS_OUTRO_BAD;
            menu_changed = 1;
          }
          break;
      }
      break;
    //    case EMIIS_PROC:
    //    break;
    case EMIIS_OUTRO_BAD:
    case EMIIS_OUTRO_GOOD:
      menu_int_input_status = EMIIS_DROP;
      break;
    default:
      break;
  };

  return 1;
}

int lib_int_input_loop(void* data) {
  switch (menu_int_input_status) {
    case EMIIS_INTRO:
      menu_int_input_buffer = menu_int_input_default;
      menu_int_input_status = EMIIS_INPUT;
      menu_changed = 1;
      break;
    case EMIIS_INPUT:
      if ( menu_changed ) {
        // clear row ... macros??
        lcd_lib->setCursor(0, 0);
        lcd_lib->print("                ");

        // calculate current digit number
        int zappart = 0;
        int menu_int_buf_copy = menu_int_input_buffer;
        do {
          //if ( ((menu_int_buf_copy/10) != 0) && (menu_int_buf_copy%10) == 0 ) zappart++;
          menu_int_buf_copy /= 10;

          zappart++;
        } while (menu_int_buf_copy != 0);

        //        Serial.println(zappart);

        // put it out
        lcd_lib->setCursor(16 - zappart, 0);

        //!!!! macro ???
        char cstr[16];
        itoa(menu_int_input_buffer, cstr, 10);
        lcd_lib->print(cstr);

        menu_changed = 0;
      }
      break;
    case EMIIS_OUTRO_GOOD:
      if ( proc_int_loop != 0 ) {
        proc_int_loop(0);
      } else {
        if ( menu_changed ) {
          lcd_lib->setCursor(0, 0);
          lcd_lib->print("^_^ anykey..");

          menu_changed = 0;
        }
      }
      break;
    case EMIIS_OUTRO_BAD:

      if ( proc_int_loop != 0 ) {
        proc_int_loop(0);
      } else {
        if ( menu_changed ) {
          lcd_lib->setCursor(0, 0);
          //lcd_lib->print("                ");

          lcd_lib->print("(X) anykey.. (X)");
          menu_changed = 0;
        }
      }

      break;
    case EMIIS_DROP:
      menu_status = EMS_BROWSING;
      menu_changed = 1;
      menu_int_input_status = EMIIS_INTRO;
      break;
  };

  return 1;
}





//#define __PURE_STRING_INPUT__

#ifdef __PURE_STRING_INPUT__


typedef enum {
  EMLIS_INTRO,
  EMLIS_INPUT,
  //  EMIIS_PROC,
  EMLIS_STRING_APPEND,
  EMLIS_STRING_ENDING,
  EMLIS_POPUP_QUESTION,
  EMLIS_OUTRO_GOOD,
  EMLIS_OUTRO_BAD,
  EMLIS_DROP
} E_MENU_LETTER_INPUT_STATUS;

const int menu_letter_input_min = 0;
const int menu_letter_input_default = 0;
const int menu_letter_input_max = 31;
int menu_letter_input_buffer;

wchar_t string_buffer[16];
int string_buffer_ptr;

E_MENU_LETTER_INPUT_STATUS menu_letter_input_status;

int lib_letter_input(E_BUTTONS_AVAILABLE btn, void* data) {

  switch (menu_letter_input_status) {
    //    case EMIIS_INTRO:
    case EMLIS_INPUT:
      switch (btn) {
        case EBA_UP:
          if ( menu_letter_input_buffer < menu_letter_input_max ) {
            menu_letter_input_buffer++;
            menu_changed = 1;
          }
          break;
        case EBA_DOWN:
          if ( menu_letter_input_min < menu_letter_input_buffer ) {
            menu_letter_input_buffer--;
            menu_changed = 1;
          }
          break;
        case EBA_OK:

          if (proc_int != 0) {
            proc_int(0);
          } else {
            menu_letter_input_status = EMLIS_STRING_APPEND;
            menu_changed = 1;
          }

          break;
        case EBA_CANCEL:

          if (proc_int != 0) {
            proc_int(0);
          } else {
            menu_letter_input_status = EMLIS_STRING_ENDING;
            menu_changed = 1;
          }
          break;
      }
      break;
    //    case EMIIS_PROC:
    //    break;
    case EMLIS_STRING_APPEND:
    case EMLIS_STRING_ENDING:
    break;
    case EMLIS_POPUP_QUESTION:
      switch (btn) {
        case EBA_OK:

          menu_letter_input_status = EMLIS_OUTRO_GOOD;
          menu_changed = 1;

          break;
        case EBA_CANCEL:
          
          menu_letter_input_status = EMLIS_OUTRO_BAD;
          menu_changed = 1;

          break;
      }      
    break;
    case EMLIS_OUTRO_BAD:
    case EMLIS_OUTRO_GOOD:
      menu_letter_input_status = EMLIS_DROP;
      break;
    default:
      break;
  };

  return 1;
}

int lib_letter_input_loop(void* data) {
  switch (menu_letter_input_status) {
    case EMLIS_INTRO:
      menu_letter_input_buffer = menu_letter_input_default;
      menu_letter_input_status = EMLIS_INPUT;
      string_buffer_ptr = 0;
      menu_changed = 1;
      break;
    case EMLIS_INPUT:
      if ( menu_changed ) {
        // clear row ... macros??
        lcd_lib->setCursor(0, 0);
        lcd_lib->print("                ");

        // calculate current digit number
        int zappart = 0;
        int menu_letter_buf_copy = menu_letter_input_buffer;
        do {
          //if ( ((menu_int_buf_copy/10) != 0) && (menu_int_buf_copy%10) == 0 ) zappart++;
          menu_letter_buf_copy /= 10;

          zappart++;
        } while (menu_letter_buf_copy != 0);

        //        Serial.println(zappart);

        // put it out
        //lcd_lib->setCursor(16 - zappart, 0);
        lcd_lib->setCursor(15, 0);
        //!!!! macro ???
        //char cstr[16];
        //itoa(menu_letter_input_buffer, cstr, 10);
        //lcd_lib->print(cstr);

        wchar_t ssstr[2];
        ssstr[0] = menu_letter_input_buffer+L'А';
        ssstr[1] = 0;
        lcd_lib->print(ssstr);

        menu_changed = 0;
      }
      break;
    case EMLIS_STRING_APPEND:
      if (menu_changed){
        lcd_lib->setCursor(0, 1);
        string_buffer[string_buffer_ptr++] = menu_letter_input_buffer+L'А';
        string_buffer[string_buffer_ptr] = 0;
        wchar_t* loccptr = string_buffer;
        

        int shiftttt = string_buffer_ptr - 15;
        if ( shiftttt > 0 ){
          loccptr += shiftttt;
        }
        
        lcd_lib->print(loccptr);

        menu_letter_input_buffer = menu_letter_input_default;
        menu_letter_input_status = EMLIS_INPUT;
        menu_changed = 1; // !!!!
      }    
      break;
    case EMLIS_STRING_ENDING:
      if (menu_changed){
        menu_letter_input_status = EMLIS_POPUP_QUESTION;
      }
      break;
    case EMLIS_POPUP_QUESTION:
      if (menu_changed){
        lcd_lib->setCursor(0, 0);
        lcd_lib->print(L"str is ready");
        menu_changed = 0;    
      }
      break;
    case EMLIS_OUTRO_GOOD:
      if ( proc_int_loop != 0 ) {
        proc_int_loop(0);
      } else {
        if ( menu_changed ) {
          lcd_lib->setCursor(0, 0);
          lcd_lib->print("^_^ anykey..");

          menu_changed = 0;
        }
      }
      break;
    case EMLIS_OUTRO_BAD:

      if ( proc_int_loop != 0 ) {
        proc_int_loop(0);
      } else {
        if ( menu_changed ) {
          lcd_lib->setCursor(0, 0);
          //lcd_lib->print("                ");

          lcd_lib->print("(X) anykey.. (X)");
          menu_changed = 0;
        }
      }

      break;
    case EMLIS_DROP:
      menu_status = EMS_BROWSING;
      menu_changed = 1;
      menu_letter_input_status = EMLIS_INTRO;
      break;
  };

  return 1;
}

#endif


typedef enum {
  EMEFIS_INTRO,
  EMEFIS_BUTTON_NUMBER_INPUT,
  EMEFIS_STRING_STEP_DESCRIPTION,
  EMEFIS_LETTER_INPUT,
  EMEFIS_STRING_APPEND,
  EMEFIS_STRING_ENDING,
  EMEFIS_INTEGER_STEP_DESCRIPTION,
  EMEFIS_INTEGER_INPUT,
  EMEFIS_POPUP_QUESTION,
  EMEFIS_OUTRO_GOOD,
  EMEFIS_OUTRO_BAD,
  EMEFIS_DROP
} E_MENU_EEPROM_FULL_INPUT_STATUS;

const int menu_emefis_button_number_min = 0;
const int menu_emefis_button_number_default = 0;
const int menu_emefis_button_number_max = 11;
int menu_button_input_buffer;

const int menu_emefis_letter_input_min = 0;
const int menu_emefis_letter_input_default = 0;
//const int menu_emefis_letter_input_max = 31;
const int menu_emefis_letter_input_max = 27;
int menu_emefis_letter_buffer;

const int menu_emefis_int_input_min = 0;
const int menu_emefis_int_input_default = 0;
const int menu_emefis_int_input_max = 99;
int menu_emefis_int_buffer;

wchar_t eeprom_string_buffer[19];
int eeprom_string_buffer_ptr;

E_MENU_EEPROM_FULL_INPUT_STATUS menu_eeprom_input_status;

int lib_eeprom_input(E_BUTTONS_AVAILABLE btn, void* data) {

  switch (menu_eeprom_input_status) {
    //    case EMIIS_INTRO:
    case EMEFIS_BUTTON_NUMBER_INPUT:
      switch (btn) {
        case EBA_UP:
          if ( menu_button_input_buffer < menu_emefis_button_number_max ) {
            menu_button_input_buffer++;
            menu_changed = 1;
          }
          break;
        case EBA_DOWN:
          if ( menu_emefis_button_number_min < menu_button_input_buffer ) {
            menu_button_input_buffer--;
            menu_changed = 1;
          }
          break;
        case EBA_OK:
          menu_eeprom_input_status = EMEFIS_STRING_STEP_DESCRIPTION;
          menu_changed = 1;
        break;
        case EBA_CANCEL:
          menu_eeprom_input_status = EMEFIS_OUTRO_BAD;
          menu_changed = 1;
        break;
      };
      break;
    case EMEFIS_STRING_STEP_DESCRIPTION:
      switch (btn) {
        case EBA_OK:

          menu_eeprom_input_status = EMEFIS_LETTER_INPUT;
          menu_changed = 1;

          break;
        case EBA_CANCEL:
          
          menu_eeprom_input_status = EMEFIS_OUTRO_BAD;
          menu_changed = 1;

          break;
      }      
      break;
    case EMEFIS_LETTER_INPUT:
      switch (btn) {
        case EBA_UP:
          if ( menu_emefis_letter_buffer < menu_emefis_letter_input_max ) {
            menu_emefis_letter_buffer++;
            menu_changed = 1;
          }
          break;
        case EBA_DOWN:
          if ( menu_emefis_letter_input_min < menu_emefis_letter_buffer ) {
            menu_emefis_letter_buffer--;
            menu_changed = 1;
          }
          break;
        case EBA_OK:        
            menu_eeprom_input_status = EMEFIS_STRING_APPEND;
            menu_changed = 1;
          break;
        case EBA_CANCEL:
            menu_eeprom_input_status = EMEFIS_STRING_ENDING;
            menu_changed = 1;
          break;
      }
      break;
    case EMEFIS_STRING_APPEND:
    case EMEFIS_STRING_ENDING:
    break;
    case EMEFIS_INTEGER_STEP_DESCRIPTION:
      switch (btn) {
        case EBA_OK:

          menu_eeprom_input_status = EMEFIS_INTEGER_INPUT;
          menu_changed = 1;

          break;
        case EBA_CANCEL:
          
          menu_eeprom_input_status = EMEFIS_OUTRO_BAD;
          menu_changed = 1;

          break;
      }      
      break;
    case EMEFIS_INTEGER_INPUT:
      switch (btn) {
        case EBA_UP:
          if ( menu_emefis_int_buffer < menu_emefis_int_input_max ) {
            menu_emefis_int_buffer++;
            menu_changed = 1;
          }
          break;
        case EBA_DOWN:
          if ( menu_emefis_int_input_min < menu_emefis_int_buffer ) {
            menu_emefis_int_buffer--;
            menu_changed = 1;
          }
          break;
        case EBA_OK:
            menu_eeprom_input_status = EMEFIS_POPUP_QUESTION;
            menu_changed = 1;
          break;
        case EBA_CANCEL:
            menu_eeprom_input_status = EMEFIS_OUTRO_BAD;
            menu_changed = 1;
          break;
      }      
      break;
    case EMEFIS_POPUP_QUESTION:
      switch (btn) {
        case EBA_OK:

          menu_eeprom_input_status = EMEFIS_OUTRO_GOOD;
          menu_changed = 1;

          break;
        case EBA_CANCEL:
          
          menu_eeprom_input_status = EMEFIS_OUTRO_BAD;
          menu_changed = 1;

          break;
      }      
    break;
    case EMEFIS_OUTRO_BAD:
    case EMEFIS_OUTRO_GOOD:
      menu_eeprom_input_status = EMEFIS_DROP;
      break;
    default:
      break;
  };

  return 1;
}

int lib_eeprom_input_loop(void* data) {
  switch (menu_eeprom_input_status) {
    case EMEFIS_INTRO:
      // drop variables
      menu_button_input_buffer = menu_emefis_button_number_default;
      menu_emefis_letter_buffer = menu_emefis_letter_input_default;
      menu_emefis_int_buffer = menu_emefis_int_input_default;

      menu_eeprom_input_status = EMEFIS_BUTTON_NUMBER_INPUT;
//      menu_letter_input_status = EMLIS_INPUT;
      eeprom_string_buffer_ptr = 0;
      menu_changed = 1;
      break;
    case EMEFIS_BUTTON_NUMBER_INPUT:
      if ( menu_changed ) {
        // clear row ... macros??
        lcd_lib->setCursor(0, 0);
        lcd_lib->print("                ");

        // calculate current digit number
        int zappart_button_int = 0;
        int menu_button_input_buf_copy = menu_button_input_buffer;
        do {
          //if ( ((menu_int_buf_copy/10) != 0) && (menu_int_buf_copy%10) == 0 ) zappart++;
          menu_button_input_buf_copy /= 10;

          zappart_button_int++;
        } while (menu_button_input_buf_copy != 0);



        // put it out
        lcd_lib->setCursor(16 - zappart_button_int, 0);

        //!!!! macro ???
        char menu_button_input_cstr[16];
        itoa(menu_button_input_buffer, menu_button_input_cstr, 10);
        lcd_lib->print(menu_button_input_cstr);

        menu_changed = 0;
      }
    break;
    case EMEFIS_STRING_STEP_DESCRIPTION:
      if ( menu_changed ){
        lcd_lib->setCursor(0, 0);
        lcd_lib->print("                ");
        lcd_lib->setCursor(0, 0);
        lcd_lib->print(L"дальше?");

        
        lcd_lib->setCursor(0, 1);
        lcd_lib->print("                ");
        lcd_lib->setCursor(0, 1);
        lcd_lib->print(L"ВВОД ИМЕНИ");
        
        
        menu_changed = 0;  
      }
    
    break;
    case EMEFIS_LETTER_INPUT:    
      if ( menu_changed ) {
        // clear row ... macros??
        lcd_lib->setCursor(0, 0);
        lcd_lib->print("                ");


        // calculate current digit number
        //int zappart = 0;
        //int menu_letter_buf_copy = menu_emefis_letter_buffer;
        //do {
          //if ( ((menu_int_buf_copy/10) != 0) && (menu_int_buf_copy%10) == 0 ) zappart++;
        //  menu_letter_buf_copy /= 10;

        //  zappart++;
        //} while (menu_letter_buf_copy != 0);

        // put it out
        //lcd_lib->setCursor(16 - zappart, 0);
        lcd_lib->setCursor(15, 0);
        //!!!! macro ???
        //char cstr[16];
        //itoa(menu_letter_input_buffer, cstr, 10);
        //lcd_lib->print(cstr);

        wchar_t ssstr[2];
        ssstr[0] = menu_emefis_letter_buffer+L'A';
        ssstr[1] = 0;
        lcd_lib->print(ssstr);

        menu_changed = 0;
      }
      break;
    case EMEFIS_STRING_APPEND:
      if (menu_changed){
        lcd_lib->setCursor(0, 1);
        eeprom_string_buffer[eeprom_string_buffer_ptr++] = menu_emefis_letter_buffer+L'A';
        eeprom_string_buffer[eeprom_string_buffer_ptr] = 0;
        wchar_t* loccptr = eeprom_string_buffer;
        

        int shiftttt = eeprom_string_buffer_ptr - 15;
        if ( shiftttt > 0 ){
          loccptr += shiftttt;
        }
        lcd_lib->setCursor(0, 1);
        lcd_lib->print("                ");
        lcd_lib->setCursor(0, 1);
        lcd_lib->print(loccptr);

        menu_emefis_letter_buffer = menu_emefis_letter_input_default;
        menu_eeprom_input_status = EMEFIS_LETTER_INPUT;
        menu_changed = 1; // !!!!
      }    
      break;
    case EMEFIS_STRING_ENDING:
      if (menu_changed){
        menu_eeprom_input_status = EMEFIS_INTEGER_STEP_DESCRIPTION;
      }
      break;
    case EMEFIS_INTEGER_STEP_DESCRIPTION:
      if (menu_changed){
        lcd_lib->setCursor(0, 0);
        lcd_lib->print("                ");
        lcd_lib->setCursor(0, 0);
        lcd_lib->print(L"ДАЛЬШЕ?");

        lcd_lib->setCursor(0, 1);
        lcd_lib->print("                ");
        lcd_lib->setCursor(0, 1);
        lcd_lib->print(L"ВВОД ЦЕНЫ");
        
        
        menu_changed = 0;   
      }
      break;
    case EMEFIS_INTEGER_INPUT:
      if ( menu_changed ) {
        // clear row ... macros??
        lcd_lib->setCursor(0, 0);
        lcd_lib->print("                ");

        // calculate current digit number
        int zappart = 0;
        int menu_int_buf_copy = menu_emefis_int_buffer;
        do {
          //if ( ((menu_int_buf_copy/10) != 0) && (menu_int_buf_copy%10) == 0 ) zappart++;
          menu_int_buf_copy /= 10;

          zappart++;
        } while (menu_int_buf_copy != 0);

        //        Serial.println(zappart);

        // put it out
        lcd_lib->setCursor(16 - zappart, 0);

        //!!!! macro ???
        char cstr[16];
        itoa(menu_emefis_int_buffer, cstr, 10);
        lcd_lib->print(cstr);

        menu_changed = 0;
      }
      break;
    case EMEFIS_POPUP_QUESTION:
      if (menu_changed){
        lcd_lib->setCursor(0, 0);
        lcd_lib->print("                ");
        lcd_lib->setCursor(0, 0);
        lcd_lib->print(L"ДАЛЬШЕ?");

        lcd_lib->setCursor(0, 1);
        lcd_lib->print("                ");
        lcd_lib->setCursor(0, 1);
        lcd_lib->print(L"ЗАПИСЬ");
        
        
        menu_changed = 0;   
      }      
      break;
      
    case EMEFIS_OUTRO_GOOD:
      if ( menu_changed ) {
        // write to eeprom
        

  
        page_container_pointer = menu_button_input_buffer;
        copy_wchar_string_to_buffer(eeprom_string_buffer);
        page_container_buffer.data.number.number32 = menu_emefis_int_buffer;

        writePage();

        clear_page_container_buffer();
        read_page_container(menu_button_input_buffer);

        //Serial.println(page_container_buffer.data.number.number32);
        //debug_output_english_string(page_container_buffer.data.text.text16);       

        
        lcd_lib->setCursor(0, 0);
        lcd_lib->print("^_^ anykey..");

        menu_changed = 0;
      }
      break;
    case EMEFIS_OUTRO_BAD:
      if ( menu_changed ) {
        lcd_lib->setCursor(0, 0);
        //lcd_lib->print("                ");
        
        lcd_lib->print("(X) anykey.. (X)");
        menu_changed = 0;
      }

      break;
    case EMEFIS_DROP:
      menu_status = EMS_BROWSING;
      menu_changed = 1;
      menu_eeprom_input_status = EMEFIS_INTRO;
      break;
  };

  return 1;
}




























int libtest_int_(E_BUTTONS_AVAILABLE btn, void* data) {
  
  return 1;
}





//
// Demo function
//
int  libtest(E_BUTTONS_AVAILABLE btn, void* data) {
  if ( time_transition_status == 0 )
    menu_changed = 1;


  //lcd_lib->print(L"bash::");
  //lcd_lib->print((wchar_t*)data);
  return 1;
}


uint16_t libtest_multiplier;
int  libtest_loop(void* data) {

  if (time_transition_status == 0) {
    time_transition_status++;
    //  menu_changed = 1;
    // libtest_multiplier  = 0;
  } else if (time_transition_status == 1) {
    //   if (menu_changed == 1){
    lcd_lib->setCursor(0, 0);
    lcd_lib->print("                ");
    lcd_lib->setCursor(0, 0);
    lcd_lib->print(L"bash::");
    if (data == 0) {
      lcd_lib->print(L"sup");
      char cstr[16];
      itoa(curr_item.id, cstr, 10);
      lcd_lib->print(cstr);
    } else {
      lcd_lib->print((wchar_t*)data);
    }
    //     menu_changed = 0;
    //    }
    time_transition_status++;
    reset_gen_loop_counter;
    libtest_multiplier = 0;
  } else {

    if ( gen_loop_counter > 4096 ) {
      reset_gen_loop_counter();
      libtest_multiplier++;
    }

    if ( libtest_multiplier > 2 )
    {
      libtest_multiplier = 0;
      time_transition_status = 0;
      menu_status = EMS_OUTPUT;
      menu_changed = 1;
    }
  }



  return 1;
}






//wchar_t* anykey_ = L"anykey...";
const wchar_t anykey_[] = { L"нажми кнопку!!..." };

#define MENU_ARRAY_SIZE 5

// RULES
// name         -- any wchar_t string ( for easy russian language support ) shouled be less than display width (16 in our case) (!)
//                  -- we won't implement any automation (!) here
// id           --  0 : is ignored ( 0 is an id of virtual root menu ) program scans raw array .. that means, it will care about ids only to know parential relations
//                  -- ( if an item has a brother with id shared, cancel button will return up to the first occurence of such an id ) )just in case of simpler logics
// add          --  sense
// parent_id    --  0 : root menu otherwise is placed in tree if exists or ignored otherwise
// action       --  function pointer to action bound to button ( might be some standart function or something more scepife3 )
//|   name              |  id  |  add  |  parent_id  |       action       |            action_argument   |       loop_action       |    output_message    |
const menu_item testvak[MENU_ARRAY_SIZE] PROGMEM = {
//L"тест",                  1,      0,            0,       lib_int_input,                             0,       lib_int_input_loop,    (wchar_t*)&anykey_,
  L"тест",                  1,      0,            0,             libtest,                             0,             libtest_loop,    (wchar_t*)&anykey_,
  L"изменить",              2,      0,            0,    lib_eeprom_input,                             0,    lib_eeprom_input_loop,    (wchar_t*)&anykey_,
//L"смена имени",           3,      0,            0,    lib_letter_input,                             0,    lib_letter_input_loop,    (wchar_t*)&anykey_,
  L"смена имени",           3,      0,            0,             libtest,                             0,             libtest_loop,    (wchar_t*)&anykey_,
  L"смена цены",            4,      0,            0,             libtest,                             0,             libtest_loop,    (wchar_t*)&anykey_,
  L"статус",                5,      0,            0,             libtest,                             0,             libtest_loop,    (wchar_t*)&anykey_
};

const wchar_t menu_text[MENU_ARRAY_SIZE][16] PROGMEM = {
  {L"тест"},
  {L"изменить"},
  {L"смена имени"},
  {L"смена цены"},
  {L"статус"}
};



void render_menu() {
  //menu_item item;
  wchar_t render_textbuf[16];

  if ( error_flag ) {
    lcd_lib->setCursor(0, 0);
    lcd_lib->print(L"firmware error");
  } else {
    switch ( menu_status ) {
      case EMS_BROWSING:
        if ( menu_changed )
        {
          // clear
          lcd_lib->setCursor(0, 0);
          lcd_lib->print("                ");

          // print actual information btw
          lcd_lib->setCursor(0, 0);

          //            memcpy_P(&item, &testvak[menu_position], sizeof(menu_item));
          //            lcd_lib->print(item.name);
          //memcpy_P((void*)render_textbuf, (void*)curr_item.name, 32);

          lcd_lib->print(curr_item.name);
          menu_changed = 0;
        }
        break;
      case EMS_SELECTED:
        curr_item.loop_action(0);
        break;
      case EMS_OUTPUT:
        if ( menu_changed ) {
          lcd_lib->setCursor(0, 0);
          lcd_lib->print("                ");
          lcd_lib->setCursor(0, 0);
          lcd_lib->print(curr_item.output_message);
          menu_changed = 0;
        }
        break;
    };
  }
}



int search_menu_by_id ( int id ) {
  menu_item walk_item;
  int i = 0;
  do {
    memcpy_P(&curr_item, &testvak[i], sizeof(menu_item));
    if ( curr_item.id == id ) return i;
    i++;
  } while ( i < MENU_ARRAY_SIZE );
  return -1;
}




// redo for antifool protection
int reset_menu(int parent_id) {
  menu_item walk_item;
  int result = 1;
  // lets search first element with parent == 0
  menu_position = 0;

  int i = menu_position;

  if (menu_position < MENU_ARRAY_SIZE)
  {
    do {
      memcpy_P(&walk_item, &testvak[menu_position], sizeof(menu_item));
      if (walk_item.parent_id == parent_id) { // main menu level
        break;
      }
      i++;
    } while (i < MENU_ARRAY_SIZE);

    if (i == MENU_ARRAY_SIZE) {
      //error_flag = 1;
      result = 0;
    } else {
      menu_position = i;
      curr_item = walk_item;
    }

    menu_changed = 1;
  }

  return result;
}




void init_menu_library(lcd1602_rus* lib_ptr) {
  lcd_lib = lib_ptr;
  menu_changed = 0;
  menu_status = EMS_BROWSING;
  time_transition_status = 0;

  proc_int = 0;
  proc_int_loop = 0;

  error_flag = 0;
  if (!reset_menu(0)) error_flag = 1;
}

void drop_output_message() {
  menu_status = EMS_BROWSING;
  //      lcd_lib->setCursor(0,0);
  //      lcd_lib->print(L"                ");
  //      lcd_lib->setCursor(0,0);
  time_transition_status = 0;
  menu_changed = 1;
}

int up_keypressed(void* data) {
  menu_item walk_item;
  int i = menu_position;

  reset_independent_counter_multiplier;

  switch ( menu_status ) {
    case EMS_BROWSING:
      if (menu_position > 0)
      {
        do {-
          i--;
          memcpy_P(&walk_item, &testvak[i], sizeof(menu_item));
          if ((walk_item.parent_id == curr_item.parent_id) && (walk_item.id != 0)) {
            menu_position = i;
            memcpy_P(&curr_item, &testvak[menu_position], sizeof(menu_item));

            menu_changed = 1;
            break;
          }
        } while ( (i != 0) );

      }
      break;
    case EMS_SELECTED:
      curr_item.action(EBA_UP, curr_item.action_argument);
      break;
    case EMS_OUTPUT:
      drop_output_message();
      break;
  };


  return 1;
}

int down_keypressed(void* data) {
  menu_item walk_item;
  int i = menu_position;

  reset_independent_counter_multiplier;

  switch ( menu_status ) {
    case EMS_BROWSING:
      if (menu_position < (MENU_ARRAY_SIZE - 1))
      {
        do {
          i++;
          memcpy_P(&walk_item, &testvak[i], sizeof(menu_item));
          if ((walk_item.parent_id == curr_item.parent_id) && (walk_item.id != 0)) {
            menu_position = i;
            memcpy_P(&curr_item, &testvak[menu_position], sizeof(menu_item));

            menu_changed = 1;
            break;
          }
        } while ( (i != (MENU_ARRAY_SIZE - 1)) );

      }
      break;
    case EMS_SELECTED:
      curr_item.action(EBA_DOWN, curr_item.action_argument);
      break;
    case EMS_OUTPUT:
      drop_output_message();
      break;
  };

  return 1;
}

int ok_keypressed(void* data) {

  // menu position (!)
  //  memcpy_P(&curr_item, &testvak[menu_position], sizeof(menu_item));

  reset_independent_counter_multiplier;


  switch ( menu_status ) {
    case EMS_BROWSING:


      if (reset_menu(curr_item.id)) {

      } else {
        if ( curr_item.action != 0 ) {
          curr_item.action(EBA_OK, curr_item.action_argument); // !!!! fix :) we count this action as
        }

        menu_status = EMS_SELECTED;
      }

      break;
    case EMS_SELECTED:
      curr_item.action(EBA_OK, curr_item.action_argument);
      break;
    case EMS_OUTPUT:
      drop_output_message();
      break;
  };

  return 1;
}



int cancel_keypressed(void* data) {
  menu_item test_item;
  int pos;

  reset_independent_counter_multiplier;

  switch ( menu_status ) {
    case EMS_BROWSING:
      if ( curr_item.parent_id != 0 ) {
        pos = search_menu_by_id (curr_item.parent_id);

        if ( pos != -1 ) { // useless i guess, but still
          memcpy_P(&test_item, &testvak[menu_position], sizeof(menu_item));

          if (!reset_menu (test_item.parent_id)) error_flag = 1;
        }
        else error_flag = 1;

      }
      break;
    case EMS_SELECTED:
      curr_item.action(EBA_CANCEL, curr_item.action_argument);
      break;
    case EMS_OUTPUT:
      drop_output_message();
      break;
  };

  return 1;
}
