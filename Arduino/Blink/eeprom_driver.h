#ifndef __EEPROM_DRIVER_H_INCLUDED__
#define __EEPROM_DRIVER_H_INCLUDED__


#include <Arduino.h>
#include <EEPROM.h>
//
// Pre calculate all numbers before using the module (!)
// простейший драйвер EEPROM с абстракцией на страницы 
// необходимо было кешировать транзакции при отсутствии интернетов

#define TOTAL_EEPROM_SIZE_IN_BYTES 512
#define TOTAL_EEPROM_SIZE_AVAILABLE 504
#define EEPROM_HEADER_SIZE 8

#define PAGE_CONTAINER_NUMBER 12
#define PAGE_NUMBER 1
#define PAGE_CONTAINER_SIZE 42
#define PAGE_CONTAINER_TEXT 38
#define PAGE_CONTAINER_TEXT_WCHAR 19
#define PAGE_CONTAINTER_NUMBER 4

typedef union {
  struct {
    union {
      uint8_t text_byte_array[PAGE_CONTAINER_TEXT];
      wchar_t text16[PAGE_CONTAINER_TEXT_WCHAR];
    } text;
    union{
      uint32_t number32;
      uint8_t number_byte_array[PAGE_CONTAINTER_NUMBER];
    } number;
  } data;
  uint8_t data_byte_array[PAGE_CONTAINER_SIZE];
} page_container;





void writePage();
void read_page_container ( uint8_t index );
void clear_page_container_buffer();
void copy_wchar_string_to_buffer( wchar_t* str_to_copy );
void debug_output_english_string( wchar_t* str_to_output );


//
// External parameters to write page container
//
extern page_container page_container_buffer;
extern uint8_t page_container_pointer;


#endif // End of __EEPROM_DRIVER_H_INCLUDED__




