




//
// CP866
//

//char* stringtest = "абвгдеёжзиклмнопрстуфхцчшщъыьэюяabcdefghijklmnopqrstuvwxyz";

//char utf8_detection_symbols[2] = {0xD0,0xD1};
#define UTF8_DETECTION_SYMBOL1 0xD0
#define UTF8_DETECTION_SYMBOL2 0xD1



uint8_t convert_symbol(uint8_t* str_ptr, uint8_t* result){
  *result = 0;
  uint8_t shift = 0;;
  switch(str_ptr[0]){
    case UTF8_DETECTION_SYMBOL1: // 0xD0
      if ((0x90 <= str_ptr[1]) && (str_ptr[1] <= 0xBF)){
        *result = str_ptr[1] - 0x10;
      } else if (str_ptr[1] == 0x81){ *result = 0xF0;}
    break;
    case UTF8_DETECTION_SYMBOL2: // 0xD1
      if ((0x80 <= str_ptr[1]) && (str_ptr[1] <= 0x8F)){
        *result = str_ptr[1] + 0x60;
      } else if (str_ptr[1] == 0x91){ *result = 0xF1;}
    break;
    default:
      *result = str_ptr[0];
      shift = 1;
      
    break;
  };
  return shift ? 1 : 2;
} 

//
// refactor yourself if you want to
void tg2460h_print ( char* arduinous_array ){
  uint8_t* ptr = (uint8_t*)arduinous_array;
  uint8_t bytee = 0;
  do{
    ptr += convert_symbol(ptr,&bytee);
    Serial.write(bytee);
  }  while(bytee != 0);

  //Serial.write('\r');
  Serial.write('\n');
}

void tg2460h_cutoff(){
  // add space
  Serial.write('\r');
  Serial.write('\n');

  // cutoff rewind
  uint8_t zz[3] = {0x1C,0xC0,0x34};
  Serial.write(zz,3);
  Serial.write('\r'); // Just in case ?
}

// printer settings format
#define TG2460H_SET_FONTA               0x00
#define TG2460H_SET_FONTB               0x01
#define TG2460H_SET_EXPANDED_ON         0x08
#define TG2460H_SET_EXPANDED_OFF        0x00
#define TG2460H_SET_DOUBLEHEIGHT_ON     0x10
#define TG2460H_SET_DOUBLEHEIGHT_OFF    0x00
#define TG2460H_SET_DOUBLEWIDTH_ON      0x20
#define TG2460H_SET_DOUBLEWIDTH_OFF     0x00
#define TG2460H_SET_ITALIC_ON           0x40
#define TG2460H_SET_ITALIC_OFF          0x00
#define TG2460H_SET_UNDERLINE_ON        0x80
#define TG2460H_SET_UNDERLINE_OFF       0x00

// easy settings
void tg2460h_changeTextProperties( uint8_t settings ){
  uint8_t zz[3] = {0x1B,0x21,0x00};
  zz[2] = settings;
  Serial.write(zz,3);
  //Serial.write('\r'); // Just in case ?
}




void tg2460h_lineSpacing (bool inchy){
  uint8_t zz[2] = {0x1B,0x00};

  if (inchy)
    zz[1] = 0x32;
  else
    zz[1] = 0x33;
  Serial.write(zz,2);
}

void tg2460h_charSpacing (uint8_t spacing){
  uint8_t zz[3] = {0x1B,0x20,0x00};
  zz[2] = spacing;
  Serial.write(zz,3);
}

#define TG2460H_EMHASIZED_ON  0x01
#define TG2460H_EMHASIZED_OFF 0x00

void tg2460h_emphasized (uint8_t emphasized){
  uint8_t zz[3] = {0x1B,0x45,0x00};
  zz[2] = emphasized;
  Serial.write(zz,3);
}

#define TG2460H_DOUBLESTRIKE_ON 0x01
#define TG2460H_DOUBLESTRIKE_OFF 0x00

void tg2460h_doublestrike (uint8_t doublestrike){
  uint8_t zz[3] = {0x1B,0x47,0x00};
  zz[2] = doublestrike;
  Serial.write(zz,3);
}

//
// ye can expand lib by using tg2460h command manual ..
// i won't






//
// guaranteed to work only with TG2460h
//

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);// default printer value

  tg2460h_print("black jesus");
  tg2460h_changeTextProperties(TG2460H_SET_DOUBLEHEIGHT_ON|TG2460H_SET_ITALIC_ON|TG2460H_SET_UNDERLINE_ON);
  tg2460h_print("black jesus");
  tg2460h_changeTextProperties(0);
  tg2460h_print("black jesus");
  tg2460h_doublestrike(TG2460H_DOUBLESTRIKE_ON);
  tg2460h_print("black jesus");
  tg2460h_doublestrike(TG2460H_DOUBLESTRIKE_OFF);
  tg2460h_print("black jesus");
  tg2460h_emphasized(TG2460H_EMHASIZED_ON);
  tg2460h_print("black jesus");
  tg2460h_emphasized(TG2460H_EMHASIZED_OFF);
  tg2460h_print("black jesus");
  tg2460h_cutoff();

  while(1);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
}




