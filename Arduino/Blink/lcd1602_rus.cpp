
//================================================================================================================
// модуль логики библиотеки дисплея 16x2 <= технически, можно адаптировать и на большие по размеру экранчики
//================================================================================================================

#include "lcd1602_rus.h"

//================================================================================================================
// служебные функции
//================================================================================================================


// TODO:::: function template???
// TODO:::: заменить на библиотечную (!) а то ппц, нельзя такое в эфир пускать
// Определяем длину строки (количество символов) 
inline void str_length(const wchar_t* _str, int& str_size_){
  str_size_ = 0;
  while(_str[str_size_] != 0)
  {
    str_size_++;
  }
}
inline void str_length(const char* _str, int& str_size_){
  str_size_ = 0;
  while(_str[str_size_] != 0)
  {
    str_size_++;
  }
}

//================================================================================================================
// конструкторы
//================================================================================================================

lcd1602_rus :: lcd1602_rus(uint8_t rs, uint8_t wr, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) : LiquidCrystal (rs, wr, enable, d0, d1, d2, d3)
{
}

lcd1602_rus :: lcd1602_rus(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) : LiquidCrystal (rs, enable, d0, d1, d2, d3)
{
}

//================================================================================================================
// очистка экрана, сброс индекса, сброс дублирующих переменных
//================================================================================================================

void lcd1602_rus::clear()
{
    LiquidCrystal::clear();
    resetIndex();
    RESET_VIRTUAL_CURSOR;
}




//================================================================================================================
// на данный момент :: :: грубо переписываем инициализацию на 16 : 2 )) 
// Только 1602 дисплейки .. почему? потому что нам доступно лишь 8 символов :3 обычно ..
//================================================================================================================

void lcd1602_rus::begin(uint8_t cols, uint8_t rows, uint8_t charsize){
  LiquidCrystal::begin(16,2,charsize);
  RESET_VIRTUAL_CURSOR;
}


//================================================================================================================
// основной диспетчер, определяющий способ отображения символа
//================================================================================================================

void lcd1602_rus::letter_dispatcher( int unicode, int capital, int character_code ){
  def_letter letter_copy;

  int engflag = 0;

  memcpy_P(&letter_copy, &rus_alphabet[character_code], sizeof(def_letter));

  uint8_t rus[8];
  //memcpy_P(rus, letter_copy.capital, 8);

  //this->setCursor(0, 0); // resets memory mode of smthng
  //this->createChar(0, rus);
  //this->setCursor(2, 0);
  //this->write(byte(0));

  //
  // копируем спецсимвол, если это возможно .. если невозможно, выводим английскую букву ()
  // TODO::: сделать автозамену русской буквы более адекватным образом
  //
  switch ( capital ){
    case 0: // нет
      if ( letter_copy.small != 0 ){
        memcpy_P(rus, letter_copy.small, 8);
        
      } else {
        LiquidCrystal::setCursor(0, 0);
        LiquidCrystal::setCursor(column,row_);
        LiquidCrystal::write(letter_copy.eng_code_ascii_small);
        COLUMN_INCREMENT(1);
        
        engflag = 1;
      }
    break;
    case 1: // да
      if ( letter_copy.capital != 0 ){
        memcpy_P(rus, letter_copy.capital, 8);
      }
      else{
        LiquidCrystal::setCursor(0, 0);
        LiquidCrystal::setCursor(column,row_);
        LiquidCrystal::write(letter_copy.eng_code_ascii_capital);
        COLUMN_INCREMENT(1);
        
        engflag = 1;
      }
    break;
  };

//
// индексация букв, уже записанных в память дисплея (всего 8)
// если спецбукв будет больше, то поведение будет не вполне адекватным (возможна доработка)
  if (!engflag){
    
    int sIndex = searchIndex(output_index);
    if ( sIndex == 10000){
      
      LiquidCrystal::setCursor(0, 0);
      LiquidCrystal::createChar(index_ptr, rus);
      index_array[index_ptr] = output_index;
      
      LiquidCrystal::setCursor(column,row_);
      LiquidCrystal::write(byte(index_ptr));
      COLUMN_INCREMENT(1);
      index_ptr++;
      
      if ( index_ptr == MAX_SYMBOL_COUNT ){ // Error state
        //LiquidCrystal::clear();
        //LiquidCrystal::setCursor(0, 0);
        //LiquidCrystal::print("error state!");
        index_ptr = 0;
      }
    }else{
      //LiquidCrystal::setCursor(0, 0);
      //LiquidCrystal::setCursor(column,row_);
      LiquidCrystal::write(byte(sIndex));
      COLUMN_INCREMENT(1);
    }
  }
}

//
// печать wchar_t строки (печать по умолчанию - определение сдвига русской буквы по коду)
// с последующим вызовом диспетчера букв
size_t lcd1602_rus::print (const wchar_t *_str)
{
  int current_char = 0;
  int str_size = 0;
  int walker;

  //Определяем длину строки (количество символов)
  str_length(_str, str_size);

  while(current_char < str_size)
  {
    walker = _str[current_char];
    output_index = walker;

//    Serial.println(walker);
    
    // main shift selector
    if ((CAPITAL_A_ASCII <= walker) && (walker <= CAPITAL_YA_ASCII)){
      walker -= CAPITAL_A_ASCII;

    } else if ((SMALL_A_ASCII <= walker) && (walker <= SMALL_YA_ASCII)){
      walker -= SMALL_A_ASCII;      

    } else if ((CAPITAL_A_UNICODE <= walker) && (walker <= CAPITAL_YA_UNICODE)){
      walker -= CAPITAL_A_UNICODE;
      
      letter_dispatcher(1,1,walker);      
    } else if ((SMALL_A_UNICODE <= walker) && (walker <= SMALL_YA_UNICODE)){
      walker -= SMALL_A_UNICODE;
      letter_dispatcher(1,0,walker);                 
    } else {
      LiquidCrystal::setCursor(0, 0);
      LiquidCrystal::setCursor(column,row_);
      LiquidCrystal::print((char)walker);
      COLUMN_INCREMENT(1);
    }
    current_char++;
  }






   return 0;
}

//
// простая печать .. char* <= уже реализована в LiquidCrystal для английского
// всё русское по умолчанию в дуине идёт в wchar_t
size_t lcd1602_rus::print (const char* _str){
  LiquidCrystal::print(_str);
  return 0;
}

// аналогично, но для экономии места строки можно печатать прямо из PROGMEM
size_t lcd1602_rus::print_progmem (wchar_t* progmemstr){
  wchar_t buf__[16];
  memcpy_P(progmemstr, buf__, 16);
  return print(buf__);
}

