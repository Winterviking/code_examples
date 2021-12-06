#ifndef __CONFIG_H_INCLUDED__
#define __CONFIG_H_INCLUDED__




//=============================================================================
//
//
// Внимание :
// загрузчик нужно положить в начало флеш-памяти (0x08000000)
// --------------------------сгодится и для иных камней, но нужно уточнять..
// ОЗУ :: ОЗУ сдвинуть на 0x100, чтобы вместилась таблица векторов прерываний .. (0x20000100) таблица векторов прерываний будет браться оттуда..
// соответственно, нужно настраивать линковщик и для загрузчика.. и для проекта вообще.. (подробнее в скелетном проекте по мере отладки)
// память можно резать, пока всё работает. 16К ROM из 64К и 0x1F00 байт RAM из 8К доступных..
// ещё не предел (на проект хватило с головой оставшегося)
// всё драйверное выносится таблицей функций в основную программу (нужно обязательно положить таблицу в определённый адрес (совсем другая история))
// вырезана инициализация периферии (беспроводные модули все убраны) <-
// есть и C++ наработки, но в продакшн не пойдут ... пока
//
//
//=============================================================================

#define MAX_BOOTLOADER_API_FUNCTION_NUMBER 1



// вот эту вот величину отправляем в linker файл как сдвиг начального адреса ОЗУ
#define vectorTableSize 0x100



//
// conversion

#define MAX_CONVERT_STRING_SIZE             12

//
// flash page sizes

#define page_size_module 256
#define page_size_flash 128

//
// flash addr
#define FLASH_EEPROM_START_ADDR   0x08080000
#define FLASH_BASEPROG_START_ADDR 0x08004000


//
// serial port pipes
//

#define COM_SERIAL_TX_BUFFER_LENGTH         256+16
#define COM_SERIAL_RX_BUFFER_LENGTH         256+16
#define COM_SERIAL_RX_TIMEOUT               700


//
// HW BEAUTIFY
//

//LEDS
#define LED_RED_PORT GPIOA
#define LED_RED_PIN GPIO_PIN_4

#define LED_GREEN_PORT GPIOA
#define LED_GREEN_PIN GPIO_PIN_5

//USB
#define USB_START_PORT GPIOB
#define USB_START_PIN GPIO_PIN_10

#define USB_DM_PORT GPIOA
#define USB_DM_PIN GPIO_PIN_11

#define USB_DP_PORT GPIOA
#define USB_DP_PIN GPIO_PIN_12

#define USB_DETECT_PORT GPIOC
#define USB_DETECT_PIN GPIO_PIN_13

//RN
#define RADIO_RESET_PORT GPIOA
#define RADIO_RESET_PIN GPIO_PIN_7
#define RADIO_BOOT_PORT GPIOB
#define RADIO_BOOT_PIN GPIO_PIN_7

//BUTTONS
#define BUTTON1_PORT GPIOB
#define BUTTON1_PIN GPIO_PIN_4
#define BUTTON2_PORT GPIOB
#define BUTTON2_PIN GPIO_PIN_5
#define BUTTON3_PORT GPIOB
#define BUTTON3_PIN GPIO_PIN_6
#define SECURITY_PORT GPIOB
#define SECURITY_PIN GPIO_PIN_5

//I2C
#define SDA_PORT GPIOB
#define SDA_PIN GPIO_PIN_14
#define SCL_PORT GPIOB
#define SCL_PIN GPIO_PIN_13





#endif /* __CONFIG_H_INCLUDED__ */
