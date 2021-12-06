
//================================================================================================================
// модуль логики библиотеки дисплея 16x2 <= технически, можно адаптировать и на большие по размеру экранчики
//================================================================================================================

#ifndef __LCD1602_RUS_H_INCLUDED__
#define __LCD1602_RUS_H_INCLUDED__

//================================================================================================================
// includes 
//================================================================================================================

#include <LiquidCrystal.h>// стандартная библиотека ардуино для работы с экранами
#include "display_array_rus.h" // шрифт и таблица соответствия
#include <Arduino.h>


//================================================================================================================
// CONSTANTS
//================================================================================================================
#define MAX_SYMBOL_COUNT 8  //Максимальное количество переназначаемых символов от 0 до 7

//================================================================================================================
// macro (TODO::: inline functions) 
//================================================================================================================

#define RESET_VIRTUAL_CURSOR 	row_ = 0; column = 0
#define ROW_INCREMENT(a) 		row_+=a
#define COLUMN_INCREMENT(a) 	column+=a
#define RESET_ROW 				row_ = 0
#define RESET_COLUMN 			column = 0

//================================================================================================================
// Служебные функции
//================================================================================================================
//
// возможно, стоит перейти на стандартную библиотеку
// функции позволяют аккуратно считать не только char строки, но и wchar_t (unicode) строки тоже
// применить новый C++ ??
//
inline void str_length(const wchar_t* _str, int& str_size_);
inline void str_length(const char* _str, int& str_size_);


//================================================================================================================
// extension of LiquidCrystal class
//================================================================================================================

class lcd1602_rus : public LiquidCrystal
{
  public:
	//RS pin, RW pin, enable, bus pins....
    lcd1602_rus(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
    lcd1602_rus(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
  public:  
	// очистка экрана
    void clear();
	
	// инициализация системы (возможно использование с большими по количеству символов экрана)
    void begin(uint8_t cols = 16, uint8_t rows = 2, uint8_t charsize = LCD_5x8DOTS);

    // хз .. я бы и ascii русское запарсил ( проблем-то )
	// возможны вопросы при пробросе с компьютера .. но тут нужно тестировать
	
	// функции печати с позиции курсора
    size_t print (const wchar_t *_str);
    size_t print (const char* _str);
    size_t print_progmem (wchar_t* progmemstr);

	// мгновенный перевод строки
    void NextLine(){
      ROW_INCREMENT(1);
      RESET_COLUMN;
    }

	// перемещение курсора Liquidcrystal библиотекой и кеширование для нашей логики (TODO:: проверить возможность извлечения x y <- из LiquidCrystal)
    void setCursor(uint8_t col, uint8_t row) {
        LiquidCrystal::setCursor(col,row);
        column = col;
        row_ = row;
    }


  private:
	// основная функция, работающая с таблицей соответствия
    void letter_dispatcher( int unicode, int capital, int character_code );
    
	//
	// index - добавляет в ближнюю кеш-очередь ссылки на уже отображённые специальные буквы
	//
    void resetIndex(){
      for(int i = 0; i < MAX_SYMBOL_COUNT; i++){
        index_array[i] = 0;
      }  
      index_ptr = 0;
    }

    int searchIndex(uint16_t test_subject){
      for(int i = 0; i < MAX_SYMBOL_COUNT; i++){
        if (index_array[i] == test_subject ){
          return i;
        }
      }
      return 10000;          
    }

    //
    // Нужны только для того, чтобы обойти тупой глюк..
    // индексация, дублирование и контроль
    uint8_t row_;
    uint8_t column;

	// индекс
    uint16_t index_array[MAX_SYMBOL_COUNT];
    uint8_t index_ptr;

    uint16_t output_index;
};






#endif // End of __LCD1602_RUS_H__



