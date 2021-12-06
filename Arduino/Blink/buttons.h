
#ifndef __BUTTONS_H_INCLUDED__
#define __BUTTONS_H_INCLUDED__

#include <Arduino.h>

//
// keyboard driver ::
// драйвер простейшей клавиатуры 4 тактовых кнопки в 4 пина
// можно адаптировать и для других клавиатур, пополнив enum кнопок
// в дальнейшем библиотека была доработана

// можно привязать несколько обработчиков событий к одной кнопке .. сейчас 1
#define MAX_AMOUNT_OF_EVENT_RECEIVERS 1

// настройка подавления дребезга
#define BUTTON_ON_STATUS_COUNT 50

//
// индивидуальное нумерование кнопок
typedef enum {
  EBA_UP          = 0,
  EBA_DOWN        = 1,
  EBA_OK          = 2,
  EBA_CANCEL      = 3,
  EBA_MAX_NUMBER  = 4
} E_BUTTONS_AVAILABLE;

//
// структура, описывающая кнопку с подавлением дребезга
typedef struct {
  int _status;
  int _old_status;
  int _pin;
  int _counter;
  int (*_event_receivers_keypressed[MAX_AMOUNT_OF_EVENT_RECEIVERS])(void*);
  void* _event_receiver_data; // ??
  int fired_keypressed;
} direct_connected_button;







//void init_buttons(int button_up, int button_down, int button_ok, int button_cancel );
// инициализация массивомм пинов
void init_buttons( const int button_pins[EBA_MAX_NUMBER]);
// привязка обработчика к кнопке (обработчик - указатель на функцию)
void add_event_receiver( int btn, int (*func)(void*));

// служебное
int buttons_wakeup();
int buttons_not_pressed();
void buttons_read();

// данные кнопок
extern int button_up_status;
extern int button_down_status;
extern int button_ok_status;
extern int button_cancel_status;

extern direct_connected_button buttons[EBA_MAX_NUMBER];


#endif // End of __BUTTONS_H_INCLUDED__

