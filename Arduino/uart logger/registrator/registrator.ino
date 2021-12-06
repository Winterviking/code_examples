
#include <SD.h>


File dataFile;

// set up variables using the SD utility library functions:
Sd2Card card;
//SdVolume volume;
//SdFile root;

const int chipSelect = 10;


//  uint8_t data_cache[451]; // 50 3byte samples
//uint8_t data_cache[145];

uint8_t data_cache[260];


typedef enum {
  EMAS_INIT,
  EMAS_IDLE,
  EMAS_REGISTER,
  EMAS_RECOVER
} E_MAIN_APP_STATE;

typedef enum {
  EPM_DETECT,
  EPM_DUMP
} E_PROGRAM_MODE;

E_MAIN_APP_STATE state = EMAS_INIT;


char file_name[13] = {'l','o','g','z','a','a','a','.','t','x','t', 0};
char one = 'a';
char two = 'a';
char three = 'a';

void dropship(){
    if (one != 'z') one++;
    else if ( two != 'z' ) {two++; one = 'a';}
    else if ( three != 'z' ){three++; two = 'a';}
    else{ //  drop
      one = 'a';
      two = 'a';
      three = 'a';
    }
    file_name[4] = one;
    file_name[5] = two;
    file_name[6] = three;

 //   Serial.println(file_name);
}



//
//
// basic
//
//
void setup_sensor (){
  dropship();
  file_name[3] = 'a';



}

//
//
// button pin setup >> >> >> >> >>(  )<< << << << << 
//
//
//

#define BUTTON_PORT PIND
#define BUTTON1_MASK 0b00000001
#define BUTTON2_MASK 0b00000001

#define BUTTON_DEBOUNCE_FACTOR_MS 500

uint8_t buttons;

enum E_BUTTON_MASK{
  EBM_START = 0b00000001,
  EBM_SETUP = 0b00000010,  
};

enum E_BUTTON{
  EB_START = 0,
  EB_SETUP = 1,
  EB_MAX = 2
};

typedef enum {
  EBS_PRESSED = 0,
  EBS_RELEASED = 1,
  EBS_READY = 2  
} E_BUTTON_STATE;

typedef struct{
  uint32_t debounce;
  E_BUTTON_STATE state;
  uint8_t mask;
} S_BUTTON;

S_BUTTON button_array[EB_MAX];



void InitButtons(){
  DDRD &= 0b00111111;
  DDRD |= 0b00000000;
  PORTD |= 0b11000000; // pullup

  buttons = 0;

  for (int i = 0; i < EB_MAX; i++){
    button_array[i].state = EBS_READY;
    button_array[i].debounce = 0;
    button_array[i].mask = 0;
  }

  button_array[EB_START].mask = EBM_START;
  button_array[EB_SETUP].mask = EBM_SETUP;
}



uint8_t zzz = 1;
// user code
void event_receiver(uint8_t button){
  switch ( button ){
    case EB_START:
          if (zzz)
            state = EMAS_REGISTER;
          else 
            state = EMAS_IDLE;

          zzz = 1 - zzz;
          
          ApplyLEDWord(0b11110000);
          delay(1000);
          ApplyLEDWord(0b00000000);
          delay(1000);


    break;
    case EB_SETUP:

    break;  
  };
}


//button module

void ButtonProcLight(){
  uint8_t buttons = PIND;
  if ((buttons & 0b11000000)>0){
    ButtonProc();
  }
}

int ButtonProc(){
  uint8_t buttons = PIND;
  buttons &= 0b11000000;
  buttons = buttons >> 6;
  buttons = (~buttons)&0b00000011;// negate, so pressed button will look like 1
  
  for (int i = 0; i < EB_MAX; i++){
    if ( button_array[i].state == EBS_READY ){
      if ((button_array[i].mask & buttons) > 0)
      {
        button_array[i].state = EBS_PRESSED;
        button_array[i].debounce = millis()+BUTTON_DEBOUNCE_FACTOR_MS;
//        Serial.println(button_array[i].debounce);
      }
    }else if (button_array[i].state == EBS_PRESSED){
     // Serial.println(button_array[i].state);
      if (button_array[i].debounce < millis()){
        if ((button_array[i].mask & buttons) == 0){
          button_array[i].state = EBS_RELEASED;
          button_array[i].debounce =  millis()+BUTTON_DEBOUNCE_FACTOR_MS;
          event_receiver(i);
        }
      }
    }else if (button_array[i].state == EBS_RELEASED){
       if (button_array[i].debounce < millis()){
         button_array[i].state = EBS_READY;
         button_array[i].debounce = 0;
       }
    }
  }

  
}














uint8_t ledword = 1;


void ApplyLEDWord(uint8_t leds){
  PORTC &= 0b11110000;
  PORTC |= ((leds)&(0b1111));//&0b1111;
  PORTD &= 0b11000011;
  PORTD |= (((leds >> 4)&(0b1111))<<2)&0b00111100;
}

void initLEDs(){
  DDRC &= 0b11110000;
  DDRC |= 0b00001111;
  DDRD &= 0b11000011;
  DDRD |= 0b00111100;

uint8_t zz = 0;
  for (int i = 0; i < 64; i++){
    ApplyLEDWord(zz);
    zz++;
    delay(20);
  }
  delay(1000);
  ApplyLEDWord(0b00000000);


}





void setup() {
  // put your setup code here, to run once:

  //
  // Base periphetal
  //

  
  Serial.begin(115200);

  InitButtons();
  initLEDs();  

  while (!SD.begin(chipSelect)){
    ApplyLEDWord(0b10000000);
    delay(500);
    ApplyLEDWord(0b00000000);
    delay(5000);   
  }


  delay(1000);



  uint8_t sample_number = 0;
  uint32_t total = 0;

  uint32_t tim = millis();
//  uint16_t loopcntr = 0;
  


  state = EMAS_IDLE;
   
   while (1){
    switch (state){
      case EMAS_IDLE:
        // button detection (!)
        ButtonProc();
      break;
      case EMAS_REGISTER:{

        char bufff[40];

        for (int i = 0; i < 40; i++) bufff[i] = 0;
        uint16_t ptrr = 0;

        dataFile = SD.open(&file_name[0], FILE_WRITE);    

        uint32_t timeouts = millis();
        
        if (dataFile) {
          
          // command up          
          Serial.print("mac tx uncnf 1 22");
          //Serial.print(0x0D);
          //Serial.print(0x0A);

          do{
            if (Serial.available() > 0){
              bufff[ptrr++] = Serial.read(); // read the incoming byte:
            }
          }while ((timeouts+3000) < millis());
          
          dataFile.println(bufff);
          //char code = 'a';
          //dataFile.write(code);
          ApplyLEDWord(17);
          delay(2000);
          ApplyLEDWord(0);

        }else{
          state = EMAS_RECOVER;
          break;
        }
        
        dataFile.close();
        
    
        if (total > 10000){ 
          Serial.println( millis() - tim);
    
          dropship();
          
          total = 0;
        }

        ApplyLEDWord(ledword*4);
        ledword = 1 - ledword;
    


        ButtonProcLight();
      }
      break;

      case EMAS_RECOVER:
        while (!SD.begin(chipSelect)){
          ApplyLEDWord(0b10000000);
          delay(500);
          ApplyLEDWord(0b00000000);
          delay(5000);    
        }

        state = EMAS_REGISTER;
      break; 
    }
   }
}

void loop() {



}


