
#include "eeprom_driver.h"


//
page_container page_container_buffer;
uint8_t page_container_pointer;

int8_t pointer;
int8_t pointer_pre;

int address_walker;
int address_walker_pre;

void seek_page_container();

void init_eeprom_driver() {
  pointer = -1;
  pointer_pre = -1;
}

void writePage() {
  seek_page_container();
  
  uint8_t add_buff = 0;
  uint8_t flag_success = 0;
  int address_walker_buf = 0;
  int address_walker_pre_buf = 0;
  for ( int i = 0; i < PAGE_CONTAINER_NUMBER; i++ ){
    address_walker_buf = address_walker + i*PAGE_CONTAINER_SIZE;
    address_walker_pre_buf = address_walker_pre + i*PAGE_CONTAINER_SIZE;
    if ( i == page_container_pointer ){
     
      for ( int j = 0; j < PAGE_CONTAINER_SIZE; j++ ){
        EEPROM.update( address_walker_buf + j, page_container_buffer.data_byte_array[j] );
      }      
      flag_success = 1;
    }else{
      for ( int j = 0; j < PAGE_CONTAINER_SIZE; j++ ){
        add_buff = EEPROM.read(address_walker_pre_buf + j);
        EEPROM.update( address_walker_buf + j, add_buff );
      }
    }
  }


  if ( flag_success == 1 ){
    if ( pointer != pointer_pre ){
      if ( pointer == (PAGE_NUMBER - 1) ){
        for ( int k = 0; k < PAGE_NUMBER; k++ ){
          EEPROM.update( k,0xFF );// "erase"
        }
      }else{
        EEPROM.update( pointer, 0 );
      }
    }
  }
  

  //  uint8_t ams = EEPROM.read(0);
  //  Serial.print(0);
  //  Serial.print("\t");
  //  Serial.print(ams, DEC);
  //  Serial.println();
}

void seek_page_container (){
  address_walker = 0;
  address_walker_pre = 0;
  // scan header

  uint8_t data;
  for ( pointer = 0; pointer < PAGE_NUMBER; pointer++ ) {
    data = EEPROM.read(address_walker);
    if (data == 0xFF) {
      break;
    }
    address_walker++;
  }

  if ( pointer == 0 ) pointer_pre = PAGE_NUMBER - 1;

  /*  if((pointer+1) == PAGE_NUMBER){
      for (int i = 0; i < PAGE_NUMBER; i++){
        EEPROM.update(i,0xFF);
      }
    }*/

  address_walker = EEPROM_HEADER_SIZE + TOTAL_EEPROM_SIZE_AVAILABLE * pointer; // to
  address_walker_pre = EEPROM_HEADER_SIZE + TOTAL_EEPROM_SIZE_AVAILABLE * pointer_pre; // from
  //found write-enabled page    
}

void read_page_container ( uint8_t index ){
  seek_page_container();

  int address_walker_pre_buf = address_walker_pre + index*PAGE_CONTAINER_SIZE;

  for ( int i = 0; i < PAGE_CONTAINER_SIZE; i++ ){
    page_container_buffer.data_byte_array[i] = EEPROM.read( address_walker_pre_buf + i );
  }
}

void clear_page_container_buffer(){
    for ( int i = 0; i < PAGE_CONTAINER_SIZE; i++ ){
    page_container_buffer.data_byte_array[i] = 0;
  }
}

void copy_wchar_string_to_buffer( wchar_t* str_to_copy ){
  int i = 0;
  do{
    page_container_buffer.data.text.text16[i++] = *str_to_copy++;
  }while(*str_to_copy != 0);
  page_container_buffer.data.text.text16[i] = 0;
}

void debug_output_english_string( wchar_t* str_to_output ){
  char serialsend[20];
  char* yeah = serialsend;
  int i = 0;
  do{
    *yeah++ = (char)((wchar_t)(*str_to_output++)-L'A') + 'A';
    i++;
  }while(*str_to_output != 0);
  *yeah = 0;


  Serial.println(serialsend);
}










