
#ifndef __MENU_LIBRARY_H_INCLUDED__
#define __MENU_LIBRARY_H_INCLUDED__

#include <stdint.h>
#include <avr/pgmspace.h>
#include "lcd1602_rus.h"
#include "buttons.h"
#include "timers.h"



#define MENU_ITEM_COUNT 20

// full menus graph

typedef struct {
  wchar_t name[16];
  int id;
  int add;
  int parent_id;
  int (*action)(E_BUTTONS_AVAILABLE, void*);
  void* action_argument;
  int (*loop_action)(void*);
  wchar_t* output_message;
} menu_item;


typedef enum {
  EMS_BROWSING,
  EMS_SELECTED,
  EMS_OUTPUT
} E_MENU_STATUS;


//fetch_children

void init_menu_library(lcd1602_rus* lib_ptr);
void render_menu();
int up_keypressed(void* data);
int down_keypressed(void* data);
int ok_keypressed(void* data);
int cancel_keypressed(void* data);

extern int error_flag;
extern int menu_changed;

#endif // End of __MENU_LIBRARY_H_INCLUDED__

