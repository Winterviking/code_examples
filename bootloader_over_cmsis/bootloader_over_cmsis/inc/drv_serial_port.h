//==============================================================
//==============================================================
//==============================================================
//
// ��������� ������������� ���������� �������������� ��������
// ��� ������ ���� ����������
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
// ������ ������������ ������
//==============================================================
typedef enum {
    ECSTF_SLIP      = 1,
    ECSTF_TEXT      = 2,
    ECSTF_NOFORMAT  = 0
} E_COM_SERIAL_TX_FORMAT; //

//==============================================================
// ����� ������ �������� �����
//==============================================================
typedef enum {
    ECSTM_RUN       = 1,
    ECSTM_STOP      = 0
} E_COM_SERIAL_TX_MODE;

//==============================================================
// ������ ������������ ������
//==============================================================
typedef enum {
    ECSRF_SLIP      = 1,
    ECSRF_TEXT      = 2,
    ECSRF_NOFORMAT  = 0,
    ECSRF_SIM300    = 3 // ����������
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

// ����������� ��������-������
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
    volatile TSerialTxFormat SerialTx_Format; // ������ ������������ ������
    volatile TSerialTxMode SerialTx_Mode;   // ����� ������ ����� - ��������/��������
    volatile WORD SerialTx_Length; // ������ ������ � ������
    volatile BYTE	SerialTx_Data[SERIAL_TX_BUFFER_SIZE+6]; // ����� �����������
    //===========================================================
    // ��������
    //===========================================================
    volatile TSerialRxFormat SerialRx_Format;
    volatile bool SerialRx_DataReady;
    volatile WORD SerialRx_Length;
    volatile BYTE SerialRx_Data[SERIAL_RX_BUFFER_SIZE+6];
    //===========================================================
    volatile BYTE TxSlip_00;
    volatile WORD TxOutPointer; // ��������� ���������� ������ �� ������
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
// ������
//==============================================================


void init_com_serial_port_driver();                                                                 // �������� ������� �������������
void com_serial_port_struct_clear   (volatile com_serial_port_def* port);                           // ������� �������� ��������� ����� � ������� memset
void com_serial_tx_stop             (volatile com_serial_port_def* port);                           // ������� �����������
bool is_com_serial_tx_ready         (volatile com_serial_port_def* port);                           // �������� ���������� ����� �������� ������
bool com_serial_tx_start            (volatile com_serial_port_def* port);                           // ������ ��������
bool com_serial_tx_clear            (volatile com_serial_port_def *port );                          // ������� ������ �����������
bool com_serial_tx_add_byte         (volatile com_serial_port_def* port, BYTE x);                   // ���������� ����� � �����
bool com_serial_tx_add_array        (volatile com_serial_port_def* port, BYTE* arr, WORD size);     // ���������� ������� � �����
bool com_serial_tx_add_string       (volatile com_serial_port_def* port, char* str);                // ���������� ������ � ����� (��� ���� �����������)
bool com_serial_tx_send_string      (volatile com_serial_port_def* port, char* str);                // �������������� �������� ������ *str �� ���������� ��������� ����������
bool com_serial_tx_send_slip_packet (volatile com_serial_port_def* port, BYTE* packet, WORD size);  // �������������� �������� SLIP ������

void com_serial_rx_read_data(volatile com_serial_port_def* port);
void com_serial_clear(volatile com_serial_port_def* port);

void sim_buffer_clear();
bool get_sim_data(BYTE* data);

// ������� ��������� � ����������
// ���������� true ���� ����� ���������� ������
// ������� ������ ������ �� ������ data
//==============================================================
// ����������
//==============================================================
bool com_serial_tx_irq_SIM800(volatile com_serial_port_def* port, BYTE* data);
bool com_serial_tx_irq_USB(volatile com_serial_port_def* port, BYTE* data);
//==============================================================
// ��������
//==============================================================
void com_serial_rx_irq_SIM800(volatile com_serial_port_def* port, BYTE x);
void com_serial_rx_irq_USB(volatile com_serial_port_def* port, BYTE x);






#endif // End of __DRV_SERIAL_PORT_H_INCLUDED__
