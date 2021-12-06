
#include "buttons.h"

//
// данные кнопок
// ВЫБРОСИТЬ ЛИШНИЕ ДАННЫЕ КНОПОК - перенести в структуру, определяющую кнопки !!
direct_connected_button buttons[EBA_MAX_NUMBER];

int button_up_status;
int button_down_status;
int button_ok_status;
int button_cancel_status;


//===================================================================================================
// старый подход

//int button_up_status_old;
//int button_down_status_old;
//int button_ok_status_old;
//int button_cancel_status_old;


//int button_up_status_internal;
//int button_down_status_internal;
//int button_ok_status_internal;
//int button_cancel_status_internal;

//int button_up_pin;
//int button_down_pin;
//int button_ok_pin;
//int button_cancel_pin;

//int button_up_counter;
//int button_down_counter;
//int button_ok_counter;
//int button_cancel_counter;

//int event_receiver_button_up;
//int event_receiver_button_down;

//int (*event_receiver_OK_keypressed)(void*) ok_event_receivers;
//int (*event_receiver_CANCEL_keypressed)(void*) cancel_event_receivers;
//int (*event_receiver_UP_keypressed)(void*) up_event_receivers;
//int (*event_receiver_DOWN_keypressed)(void*) down_event_receivers;

//===================================================================================================





// up to 4 event receivers
// инициализация данных кнопок по пинам
void init_buttons(const int button_pins[EBA_MAX_NUMBER]){

	for ( int i = 0; i < EBA_MAX_NUMBER; i++ ) {
		buttons[i]._pin = button_pins[i];
		pinMode( buttons[i]._pin, INPUT );
		buttons[i]._counter = 0;
		buttons[i]._status = LOW;
		buttons[i]._old_status = LOW;
		buttons[i].fired_keypressed = 0;

		for ( int j = 0; j < MAX_AMOUNT_OF_EVENT_RECEIVERS; j++ ){
		  buttons[i]._event_receivers_keypressed[j] = 0;
		}
	}
  
//  button_up_pin = button_up;
//  button_down_pin = button_down;
//  button_ok_pin = button_ok;
//  button_cancel_pin = button_cancel;

//  pinMode(button_up, INPUT);
//  pinMode(button_down, INPUT);
//  pinMode(button_ok, INPUT);
//  pinMode(button_cancel, INPUT);

//  button_up_counter = 0;
//  button_down_counter = 0;
//  button_ok_counter = 0;
//  button_cancel_counter = 0;

	button_up_status = LOW;
	button_down_status = LOW;
	button_ok_status = LOW;
	button_cancel_status = LOW;
}

//
// функция добавления обработчика к кнопке с контролем
void add_event_receiver( int btn, int (*func)(void*)){
  for ( int i = 0; i < MAX_AMOUNT_OF_EVENT_RECEIVERS; i++ ){
    if ( buttons[btn]._event_receivers_keypressed[i] == 0 ){
      buttons[btn]._event_receivers_keypressed[i] = func;
    }
  } 
}


//
// считывание статуса кнопки 
// если хотя бы один пин подтянут к земле - сигнализируем
int buttons_wakeup(){
  int result = 0;
  for ( int i = 0; i < EBA_MAX_NUMBER; i++ ){
    if (digitalRead(buttons[i]._pin) == LOW) result = 1;
  }
  return result;
}

// если хотя бы один пин притянут к земле - не сигнализируем
// общий сканер клавиатуры
int buttons_not_pressed(){
  int result = 1;
  for ( int i = 0; i < EBA_MAX_NUMBER; i++ ){
    if (digitalRead(buttons[i]._pin) == LOW) result = 0;
  }
  return result;
}

// additional improved debounce algorythm
void buttons_read(){
  
  int button_status_internal[EBA_MAX_NUMBER];

  for ( int i = 0; i < EBA_MAX_NUMBER; i++ ){
    button_status_internal[i] = digitalRead(buttons[i]._pin);
  }
  
  for ( int i = 0; i < EBA_MAX_NUMBER; i++ ){
    // use
    if ( button_status_internal[i] == LOW ){
      buttons[i]._counter++;
    }else{
      buttons[i]._counter = (buttons[i]._counter > 0) ? (buttons[i]._counter - 1) : 0;
    }
  
    if ( buttons[i]._counter > BUTTON_ON_STATUS_COUNT ){
      buttons[i]._status = HIGH;
      buttons[i]._counter = BUTTON_ON_STATUS_COUNT;
    }
    if ( buttons[i]._counter == 0 ){
      buttons[i]._status = LOW;
    }
  }



  if ( (buttons[EBA_UP]._status == LOW) && (button_up_status == HIGH) ){
    buttons[EBA_UP].fired_keypressed = 1;
  }
  
  if ( (buttons[EBA_DOWN]._status == LOW) && (button_down_status == HIGH) ){
    buttons[EBA_DOWN].fired_keypressed = 1;
    
  }
  if ( (buttons[EBA_OK]._status == LOW) && (button_ok_status == HIGH) ){
    buttons[EBA_OK].fired_keypressed = 1;
  }
  if ( (buttons[EBA_CANCEL]._status == LOW) && (button_cancel_status == HIGH) ){
    buttons[EBA_CANCEL].fired_keypressed = 1;
  }
  button_up_status      = buttons[EBA_UP]._status;
  button_down_status    = buttons[EBA_DOWN]._status;
  button_ok_status      = buttons[EBA_OK]._status;
  button_cancel_status  = buttons[EBA_CANCEL]._status;

  


  for ( int i = 0; i < EBA_MAX_NUMBER; i++ ){
    for ( int j = 0; j < MAX_AMOUNT_OF_EVENT_RECEIVERS; j++ ){
      if (buttons[i]._event_receivers_keypressed[j] != 0){
        if (buttons[i].fired_keypressed){
          buttons[i]._event_receivers_keypressed[j](buttons[i]._event_receiver_data);
          buttons[i].fired_keypressed = 0;
        }
      }
    }
  }

  
  
  // cut
//  int button_up_status_internal = digitalRead(button_up_pin);
//  int button_down_status_internal = digitalRead(button_down_pin);
//  int button_ok_status_internal = digitalRead(button_ok_pin);
//  int button_cancel_status_internal = digitalRead(button_cancel_pin);


/*
  // use
  if ( button_up_status_internal == LOW ){
    button_up_counter++;
  }else{
    button_up_counter = (button_up_counter > 0) ? (button_up_counter - 1) : 0;
  }

  if ( button_up_counter > BUTTON_ON_STATUS_COUNT ){
    button_up_status = HIGH;
    button_up_counter = BUTTON_ON_STATUS_COUNT;
  }
  if ( button_up_counter == 0 ){
    button_up_status = LOW;
  }



  

  if ( button_down_status_internal == LOW ){
    button_down_counter++;
  }else{
    button_down_counter = (button_down_counter > 0) ? (button_down_counter - 1) : 0;
  }

  if ( button_down_counter > BUTTON_ON_STATUS_COUNT ){
    button_down_status = HIGH;
    button_down_counter = BUTTON_ON_STATUS_COUNT;
  }
  if ( button_down_counter == 0 ){
    button_down_status = LOW;
  }





  if ( button_ok_status_internal == LOW ){
    button_ok_counter++;
  }else{
    button_ok_counter = (button_ok_counter > 0) ? (button_ok_counter - 1) : 0;
  }

  if ( button_ok_counter > BUTTON_ON_STATUS_COUNT ){
    button_ok_status = HIGH;
    button_ok_counter = BUTTON_ON_STATUS_COUNT;
  }
  if ( button_ok_counter == 0 ){
    button_ok_status = LOW;
  }





  

  if ( button_cancel_status_internal == LOW ){
    button_cancel_counter++;
  }else{
    button_cancel_counter = (button_cancel_counter > 0) ? (button_cancel_counter - 1) : 0;
  }

  if ( button_cancel_counter > BUTTON_ON_STATUS_COUNT ){
    button_cancel_status = HIGH;
    button_cancel_counter = BUTTON_ON_STATUS_COUNT;
  }
  if ( button_cancel_counter == 0 ){
    button_cancel_status = LOW;
  }
*/
  //run event receiver pool
}


//
// event
//
void event_receiver(){
  
}













