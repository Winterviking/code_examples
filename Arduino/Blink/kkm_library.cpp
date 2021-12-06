
#include "kkm_library.h"

byte cutoff[7] = { 0x06, 0x25, 0x1E, 0x00, 0x00, 0x00, 0x00}; //, 0x3D };


const wchar_t msg01[] PROGMEM = { L"Добро пожаловать:"};
const wchar_t msg02[] PROGMEM = { L"_________________________" };
const wchar_t msg03[] PROGMEM = { L"Номер теста:" };
const wchar_t msg04[] PROGMEM = { L"*************************" };
const wchar_t msg05[] PROGMEM = { L"Номер кнопки:" };
const wchar_t msg06[] PROGMEM = { L"*************************" };
const wchar_t msg07[] PROGMEM = { L"Статус устройства:" };
const wchar_t msg08[] PROGMEM = { L"=========================" };
const wchar_t msg09[] PROGMEM = { L"Отладочная информация:" };
const wchar_t msg10[] PROGMEM = { L"PINA::" };
const wchar_t msg11[] PROGMEM = { L"PINC::" };
const wchar_t msg12[] PROGMEM = { L"_________________________" };


const wchar_t* const msg_array[] PROGMEM = {
  msg01,
  msg02,
  msg03,
  msg04,
  msg05,
  msg06,
  msg07,
  msg08,
  msg09,
  msg10,
  msg11,
  msg12
};



int flagstart = 0;

uint8_t special_cmd_buffer[48];

#define bufff special_cmd_buffer
void send_cmd( uint8_t* str, int len ){
//  byte bufff[10];
/*      byte lol = word2[1];
      for ( int i = 2; i < 49; i++ ){
        lol ^= word2[i];
      }

      //cli();

  if ( !flukstart ) { 
    Serial.write(ENQ); // ENQ

    delay(10);
    //Serial.read();

    flukstart = 1;
  }
      
      for ( int i = 0; i < 49; i++ )
      {  Serial.write(word2[i]);  }
      Serial.write(lol);

      while(Serial.read() != STX);
      
      
      Serial.readBytes(buff, 5); 

      Serial.write(ACK);*/




  
    byte lol = str[0];
    for ( int i = 1; i < len; i++ ){
      lol ^= str[i];
    }

  byte check_enq;
  if ( !flagstart ) { 
    Serial.write(ENQ); // ENQ

    check_enq = Serial.read();
    if ( check_enq == ACK ){
      
    }
    else if ( check_enq == NAK ){
      
    }
//    delay(10);
    //Serial.read();

    flagstart = 1;
  }

/*  while ( Serial.available() ) {Serial.write(ENQ); delay(10);}
  byte m = Serial.read();
  if ( m == ACK ){
    if(Serial.available()){
      while(Serial.read() != STX);
      Serial.readBytes(buff, 5);

      Serial.write(ACK);
      delay(10);
    }
  } else if ( m == NAK ){

  }*/



  Serial.write(STX);
  for ( int i = 0; i < len; i++ )
    {Serial.write(str[i]);}
  Serial.write(lol);
  //delay(1);

  /*uint16_t zzz = 0;
  while (!Serial.available()){ 
    zzz++;
    if(zzz>1000) break;
  }
  if ( zzz <= 1000 ){
    while(Serial.read() != STX);
    Serial.readBytes(bufff, 5); 

    
  }*/
    while(Serial.read() != STX);
    Serial.readBytes(bufff, 5); 
  
  Serial.write(ACK);
}


char wcharToChar(wchar_t wchar);

void print_string(const wchar_t* str){
  
  // setup special buffer
  special_cmd_buffer[0] = 0x2F;
  special_cmd_buffer[1] = 0x2F;
  special_cmd_buffer[2] = 0x1E;
  special_cmd_buffer[3] = 0x00;
  special_cmd_buffer[4] = 0x00;
  special_cmd_buffer[5] = 0x00;
  special_cmd_buffer[6] = 0x07;
  special_cmd_buffer[7] = 0x01;

  int i = 8;
  uint16_t test_wch;
  while ( str[i - 8] != 0 ){
    test_wch = str[i - 8];
    
    if ( test_wch == 0x0401 ){
      special_cmd_buffer[i] = 168;
    } else if ( test_wch == 0x0451 ){
      special_cmd_buffer[i] = 184;
    } else if ((0x0410 <= test_wch) && (test_wch < 0x0450)) {
      test_wch = test_wch + 192 - 0x410;
      special_cmd_buffer[i] = test_wch & 0xFF;
    }else{
      special_cmd_buffer[i] = wcharToChar(test_wch);
    }
    
    i++;
  }
  

  for (; i < 48; i++){
    special_cmd_buffer[i] = 0;
  }
  
  
  send_cmd(special_cmd_buffer,48);
}

void print_progmem_string( int index_ ){
  wchar_t aaa[30];

  int j = 0;
  do {
    aaa[j] = pgm_read_dword((wchar_t*)pgm_read_ptr(&msg_array[index_]) + j);
    
    j++;
  } while (aaa[j-1] != 0);
  
  print_string(aaa);
}

void print_progmem_string_with_int( int index_, uint16_t param_ ){
  wchar_t aaa[30];

  int j = 0;
  do {
    aaa[j] = pgm_read_dword((wchar_t*)pgm_read_ptr(&msg_array[index_]) + j);
    
    j++;
  } while (aaa[j-1] != 0);
  j--;
  aaa[j] = L' ';
  j++;

  int buff_ = param_;
  for (int i = 0; i < 10; i++){
    buff_ /= 10;
    if (buff_ == 0) {
      buff_ = i+1;
      break;
    }
  }

  int buff__;
  for ( int i = buff_; i > 0; i--){
    buff__ = param_;
    for ( int k = 0; k < (i-1); k++ ){
      buff__ /= 10;
    }
    buff__ = buff__ % 10;
    aaa[j] = L'0' + buff__;
    j++;
  }
  aaa[j] = 0;
  
  print_string(aaa);
}

void print_progmem_string_with_string( int index_, wchar_t* param_ ){
  wchar_t aaa[30];

  int j = 0;
  do {
    aaa[j] = pgm_read_dword((wchar_t*)pgm_read_ptr(&msg_array[index_]) + j);
    
    j++;
  } while (aaa[j-1] != 0);
  j--;
  aaa[j] = L' ';
  j++;

  do {
     aaa[j] = *param_;
     j++;
     param_++;
  } while (*param_ != 0);
  
  aaa[j] = 0;
  
  print_string(aaa);
}


// TODO::: подход на константах.. нужно выкинуть свитч на помойку
//
//const wchar_t* WCHAR_ALPHABET_STRING 	= L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz 0123456789.,!?@#$%^&*()-_=+\\/|`~<>\"\';:";
//const char* CHAR_ALPHABET_STRING 		=  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz 0123456789.,!?@#$%^&*()-_=+\\/|`~<>\"\';:";

// хардкод-соответствия кодировок  .. фу
// зато не занимаем место в ОЗУ .. грязные хаки
char wcharToChar(wchar_t wchar){
  switch(wchar){
 
    case L'A':
      return 'A';
    break;
 
    case L'B':
      return 'B';
    break;
 
    case L'C':
      return 'C';
    break;
 
    case L'D':
      return 'D';
    break;
 
    case L'E':
      return 'E';
    break;
 
    case L'F':
      return 'F';
    break;
 
    case L'G':
      return 'G';
    break;
 
    case L'H':
      return 'H';
    break;
 
    case L'I':
      return 'I';
    break;
 
    case L'J':
      return 'J';
    break;
 
    case L'K':
      return 'K';
    break;
 
    case L'L':
      return 'L';
    break;
 
    case L'M':
      return 'M';
    break;
 
    case L'N':
      return 'N';
    break;
 
    case L'O':
      return 'O';
    break;
 
    case L'P':
      return 'P';
    break;
 
    case L'Q':
      return 'Q';
    break;
 
    case L'R':
      return 'R';
    break;
 
    case L'S':
      return 'S';
    break;
 
    case L'T':
      return 'T';
    break;
 
    case L'U':
      return 'U';
    break;
 
    case L'V':
      return 'V';
    break;
 
    case L'W':
      return 'W';
    break;
 
    case L'X':
      return 'X';
    break;
 
    case L'Y':
      return 'Y';
    break;
 
    case L'Z':
      return 'Z';
    break;
 
    case L'a':
      return 'a';
    break;
 
    case L'b':
      return 'b';
    break;
 
    case L'c':
      return 'c';
    break;
 
    case L'd':
      return 'd';
    break;
 
    case L'e':
      return 'e';
    break;
 
    case L'f':
      return 'f';
    break;
 
    case L'g':
      return 'g';
    break;
 
    case L'h':
      return 'h';
    break;
 
    case L'i':
      return 'i';
    break;
 
    case L'j':
      return 'j';
    break;
 
    case L'k':
      return 'k';
    break;
 
    case L'l':
      return 'l';
    break;
 
    case L'm':
      return 'm';
    break;
 
    case L'n':
      return 'n';
    break;
 
    case L'o':
      return 'o';
    break;
 
    case L'p':
      return 'p';
    break;
 
    case L'q':
      return 'q';
    break;
 
    case L'r':
      return 'r';
    break;
 
    case L's':
      return 's';
    break;
 
    case L't':
      return 't';
    break;
 
    case L'u':
      return 'u';
    break;
 
    case L'v':
      return 'v';
    break;
 
    case L'w':
      return 'w';
    break;
 
    case L'x':
      return 'x';
    break;
 
    case L'y':
      return 'y';
    break;
 
    case L'z':
      return 'z';
    break;
 
    case L' ':
      return ' ';
    break;
 
    case L'0':
      return '0';
    break;
 
    case L'1':
      return '1';
    break;
 
    case L'2':
      return '2';
    break;
 
    case L'3':
      return '3';
    break;
 
    case L'4':
      return '4';
    break;
 
    case L'5':
      return '5';
    break;
 
    case L'6':
      return '6';
    break;
 
    case L'7':
      return '7';
    break;
 
    case L'8':
      return '8';
    break;
 
    case L'9':
      return '9';
    break;
 
    case L'.':
      return '.';
    break;
 
    case L',':
      return ',';
    break;
 
    case L'!':
      return '!';
    break;
 
    case L'?':
      return '?';
    break;

    case L'@':
      return '@';
    break;
 
    case L'#':
      return '#';
    break;
 
    case L'$':
      return '$';
    break;
 
    case L'%':
      return '%';
    break;
 
    case L'^':
      return '^';
    break;
 
    case L'&':
      return '&';
    break;
 
    case L'*':
      return '*';
    break;
 
    case L'(':
      return '(';
    break;
 
    case L')':
      return ')';
    break;
 
    case L'-':
      return '-';
    break;
 
    case L'_':
      return '_';
    break;
 
    case L'=':
      return '=';
    break;
 
    case L'+':
      return '+';
    break;
 
    case L'\\':
      return '\\';
    break;
 
    case L'/':
      return '/';
    break;
 
    case L'|':
      return '|';
    break;
 
    case L'`':
      return '`';
    break;
 
    case L'~':
      return '-';
    break;
 
    case L'<':
      return '<';
    break;
 
    case L'>':
      return '>';
    break;
 
    case L'\"':
      return '\"';
    break;
 
    case L'\'':
      return '\'';
    break;
 
    case L';':
      return ';';
    break;
 
    case L':':
      return ':';
    break;
  }
}



