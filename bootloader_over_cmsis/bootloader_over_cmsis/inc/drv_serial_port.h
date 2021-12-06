//==============================================================
//==============================================================
//==============================================================
//
// Переделка проприетарной реализации промежуточного драйвера
// тут должен быть дисклеймер
//
//
//==============================================================
//==============================================================
//==============================================================



#ifndef __DRV_SERIAL_PORT_H_INCLUDED__
#define __DRV_SERIAL_PORT_H_INCLUDED__

#include "includer_hw.h"


//==============================================================
//==============================================================
//==============================================================

//==============================================================
// формат передаваемых данных
//==============================================================
typedef enum {
    ECSTF_SLIP      = 1,
    ECSTF_TEXT      = 2,
    ECSTF_NOFORMAT  = 0
} E_COM_SERIAL_TX_FORMAT; //

//==============================================================
// режим работы драйвера порта
//==============================================================
typedef enum {
    ECSTM_RUN       = 1,
    ECSTM_STOP      = 0
} E_COM_SERIAL_TX_MODE;

//==============================================================
// формат передаваемых данных
//==============================================================
typedef enum {
    ECSRF_SLIP      = 1,
    ECSRF_TEXT      = 2,
    ECSRF_NOFORMAT  = 0,
    ECSRF_SIM300    = 3 // расширение
} E_COM_SERIAL_RX_FORMAT;

//==============================================================
//==============================================================
//==============================================================

typedef struct {
    volatile struct tx_ {
        E_COM_SERIAL_TX_FORMAT  format;
        E_COM_SERIAL_TX_MODE    mode;
        volatile struct tx_buf_ {
            WORD    occupied;
            BYTE    data[COM_SERIAL_TX_BUFFER_LENGTH + 6];
        } buf;

        BYTE Slip_00;
        WORD out_ptr;
        BYTE state;
        WORD crc;
    } tx;

    volatile struct rx_ {
        E_COM_SERIAL_RX_FORMAT  format;
        bool                    dataready;
        struct rx_buf_ {
            WORD    occupied;
            BYTE    data[COM_SERIAL_RX_BUFFER_LENGTH + 6];
        } buf;

        BYTE state;
        WORD crc;
        WORD count;
    } rx;

    BYTE PortNum;
} com_serial_port_def;



//==============================================================
//==============================================================
//==============================================================

// определения объектов-портов
extern volatile com_serial_port_def COM0;
extern volatile com_serial_port_def COM1;

extern volatile bool txlock;
extern volatile bool rxlock;

extern volatile WORD rx_circle_point;
extern volatile WORD rx_circle_count;
extern volatile WORD sim_read_point;

//==============================================================
//==============================================================
//==============================================================

//void SerialInit();

//==============================================================
//==============================================================
//==============================================================



/*
typedef struct _TSerialPortStr
{
    volatile TSerialTxFormat SerialTx_Format; // Формат передаваемых данных
    volatile TSerialTxMode SerialTx_Mode;   // Режим работы порта - передача/ожидание
    volatile WORD SerialTx_Length; // Размер данных в буфере
    volatile BYTE	SerialTx_Data[SERIAL_TX_BUFFER_SIZE+6]; // Буфер передатчика
    //===========================================================
    // приемник
    //===========================================================
    volatile TSerialRxFormat SerialRx_Format;
    volatile bool SerialRx_DataReady;
    volatile WORD SerialRx_Length;
    volatile BYTE SerialRx_Data[SERIAL_RX_BUFFER_SIZE+6];
    //===========================================================
    volatile BYTE TxSlip_00;
    volatile WORD TxOutPointer; // указатель считывания данных из буфера
    volatile BYTE TxState;
    volatile WORD TxCRC;
    volatile BYTE RxState;
    volatile WORD RxCRC;
    volatile WORD RxCount;
    //bool RxTimerFlag;
    //WORD RxTimer;
    volatile BYTE PortNum;
} TSerialPortStr;
*/

//==============================================================
// Методы
//==============================================================


void init_com_serial_port_driver();                                                                 // основная функция инициализации
void com_serial_port_struct_clear   (volatile com_serial_port_def* port);                           // очистка основной структуры порта с помощью memset
void com_serial_tx_stop             (volatile com_serial_port_def* port);                           // останов передатчика
bool is_com_serial_tx_ready         (volatile com_serial_port_def* port);                           // проверка готовности перед посылкой пакета
bool com_serial_tx_start            (volatile com_serial_port_def* port);                           // Запуск передачи
bool com_serial_tx_clear            (volatile com_serial_port_def *port );                          // Очистка буфера передатчика
bool com_serial_tx_add_byte         (volatile com_serial_port_def* port, BYTE x);                   // Добавление байта в буфер
bool com_serial_tx_add_array        (volatile com_serial_port_def* port, BYTE* arr, WORD size);     // Добавление массива в буфер
bool com_serial_tx_add_string       (volatile com_serial_port_def* port, char* str);                // Добавление строки в буфер (без нуль терминатора)
bool com_serial_tx_send_string      (volatile com_serial_port_def* port, char* str);                // Автоматическая отправка текста *str со встроенным ожиданием готовности
bool com_serial_tx_send_slip_packet (volatile com_serial_port_def* port, BYTE* packet, WORD size);  // Автоматическая передача SLIP пакета

void com_serial_rx_read_data(volatile com_serial_port_def* port);
void com_serial_clear(volatile com_serial_port_def* port);

void sim_buffer_clear();
bool get_sim_data(BYTE* data);

// Функция вызывемая в прерывании
// Возвращает true если нужно передавать данные
// Функция кладет данные по адресу data
//==============================================================
// ПЕРЕДАТЧИК
//==============================================================
bool com_serial_tx_irq_SIM800(volatile com_serial_port_def* port, BYTE* data);
bool com_serial_tx_irq_USB(volatile com_serial_port_def* port, BYTE* data);
//==============================================================
// ПРИЕМНИК
//==============================================================
void com_serial_rx_irq_SIM800(volatile com_serial_port_def* port, BYTE x);
void com_serial_rx_irq_USB(volatile com_serial_port_def* port, BYTE x);






#endif // End of __DRV_SERIAL_PORT_H_INCLUDED__
