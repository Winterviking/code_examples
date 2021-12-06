//==============================================================
//==============================================================
//
// 1) �������� ����������� � ���������
// 2) ��������������� volatile
// 3) ��������� ���������������� ����, ����� �������������� ����
// 4) ���������� ��������������� ������� ������ �� �������
//
//==============================================================
//==============================================================
#include "drv_serial_port.h"
#include "drv_clock.h"
#include "usb_cdc.h"
#include "usb_utilities.h"
#include "drv_usb_main.h"
#include "drv_uart.h"
#include <string.h>

//==============================================================
//==============================================================
//==============================================================

#define TX_newline_first  ((BYTE)'\n')
#define TX_newline_second ((BYTE)'\r')

//==============================================================
//==============================================================
//==============================================================

volatile com_serial_port_def COM0;
volatile com_serial_port_def COM1;



//
// LORA specific buffer
//

volatile WORD rx_circle_point   = 0;
volatile WORD rx_circle_count   = 0;
volatile WORD sim_read_point    = 0;
volatile bool sim_sending       = false;
volatile bool sim_needsend      = false;

volatile bool txlock;
volatile bool rxlock;



//==============================================================
//==============================================================
//==============================================================

void com_serial_port_struct_clear(volatile com_serial_port_def* port){
    memset((void*)port,0,sizeof(com_serial_port_def));
}


// �������� ������� �������������
void init_com_serial_port_driver()
{
    com_serial_port_struct_clear(&COM0);
    COM0.tx.format = ECSTF_NOFORMAT;
    COM0.rx.format = ECSRF_SIM300;
    COM0.PortNum = 0;

    com_serial_port_struct_clear(&COM1);
    COM1.tx.format = ECSTF_SLIP;
    COM1.rx.format = ECSRF_SLIP;
    COM1.PortNum = 1;
}


// ������� �����������
void com_serial_tx_stop(volatile com_serial_port_def* port){
    port->tx.mode = ECSTM_STOP;
    port->tx.buf.occupied = 0;
    port->tx.out_ptr = 0;
}


// �������� ���������� ����� �������� ������
bool is_com_serial_tx_ready (volatile com_serial_port_def* port){
    if (port->PortNum == 1) { // TODO:::: ���������
        while(EP1_busy){
            if(TIMER(ep1_busy_timer) > 1000){
                EP1_busy = false;
                com_serial_tx_stop(port);
                usb_send = false;
                drv_usb_disconnect();
            }
        }
    }

    return (port->tx.mode == ECSTM_STOP);
}



// ������ ��������
bool com_serial_tx_start(volatile com_serial_port_def* port) {

    if(port->tx.mode != ECSTM_STOP)
        return false;
    if(port->tx.buf.occupied == 0)
        return true;

    if(port->PortNum == 1){ // �����������
        while(EP1_busy){
            if(TIMER(ep1_busy_timer) > 1000){
                EP1_busy = false;
                com_serial_tx_stop(&COM1);
                usb_send = false;
                drv_usb_disconnect();
            }
        }
    }

    port->tx.out_ptr    = 0;
    port->tx.state      = 0;
    port->tx.mode        = ECSTM_STOP;

    if(port->PortNum == 1) EP1_IN();
    if(port->PortNum == 0) com_serial_generate_tx(port);

    return true;
}

//==============================================================
//==============================================================
//==============================================================

// ������� ������ �����������
bool com_serial_tx_clear(volatile com_serial_port_def *port ) {
    if (port->tx.mode != ECSTM_STOP)
        return false;
    port->tx.buf.occupied = 0;

    return true;
}

// ���������� ����� � �����
bool com_serial_tx_add_byte(volatile com_serial_port_def* port, BYTE x) {
    if(port->tx.mode != ECSTM_STOP)
        return false;
    if(port->tx.buf.occupied >= COM_SERIAL_TX_BUFFER_LENGTH)
        return false;

    port->tx.buf.data[port->tx.buf.occupied++] = x;
    return true;
}

// ���������� ������� � �����
bool com_serial_tx_add_array(volatile com_serial_port_def* port, BYTE* arr, WORD size)
{
    WORD i;

    if(port->tx.mode != ECSTM_STOP)
        return false; // ���������� �����
    if((port->tx.buf.occupied + size - 1) >= COM_SERIAL_TX_BUFFER_LENGTH)
        return false; // ����� �����

    for (i=0; i<size; i++)
        port->tx.buf.data[port->tx.buf.occupied++] = arr[i];

    return true;
}

// ���������� ������ � ����� (��� ���� �����������)
bool com_serial_tx_add_string(volatile com_serial_port_def* port, char* str){
    BYTE x;

    if(port->tx.mode != ECSTM_STOP)
        return false;

    x = *str++;
    while(x != '\n') {
        if(port->tx.buf.occupied >= COM_SERIAL_TX_BUFFER_LENGTH)
            break;
        port->tx.buf.data[port->tx.buf.occupied++] = x;
        x=*str++;
    }
    return true;
}


//================================================================
//================================================================
//================================================================
// �������������� �������� ������ *� �� ���������� ��������� ����������
bool com_serial_tx_send_string(volatile com_serial_port_def* port, char* str) {
    WORD n = 0;

    while(!is_com_serial_tx_ready(port)) {
        if(n++ > 50000)
            return false;
    }

    com_serial_tx_add_string(port, str);
    port->tx.format = ECSTF_TEXT;
    com_serial_tx_start(port);

    return true;
}

// �������������� �������� SLIP ������

bool com_serial_tx_send_slip_packet(volatile com_serial_port_def* port, BYTE* packet, WORD size){
    WORD n = 0;

    while(!is_com_serial_tx_ready(port)){
        if(n++>50000)
            return false;
    }

    com_serial_tx_add_array(port, packet, size);
    port->tx.format = ECSTF_SLIP;
    com_serial_tx_start(port);
    return true;
}

//================================================================
//================================================================
//================================================================
//
//==============================================================
// 0 - �������� C0
// 1 - �������� ������� ����� = 1
// 2 - �������� ������
// 3 - �������� 2�� �����
//==============================================================
void com_serial_rx_read_data(volatile com_serial_port_def* port) {
    if(port->rx.dataready){
            port->rx.dataready = false;
            port->rx.state = 0;
            port->rx.count = 0;
            port->rx.buf.occupied = 0;
    }
}


//
// � �������, ��� ��� �������� ������� ... ���� ������ .. �� 2 .. ������ � �������� ������..
void com_serial_clear(volatile com_serial_port_def* port)
{
    port->tx.buf.occupied    = 0;
    port->tx.out_ptr         = 0;
    port->tx.state           = 0;
    port->tx.crc             = 0;

    port->rx.dataready       = 0;
    port->rx.buf.occupied    = 0;
    port->rx.state           = 0;
    port->rx.count           = 0;

    // �������������� ������� LORA ������� :: ��� �� USB �������� .. � ������� ����� ������-�� .. >>
    rx_circle_count   = 0;
    sim_read_point    = 0;
    rx_circle_point   = 0;
//    simbuflen=0;
}

//==============================================================
// ��� COM0 RX - ��������� �����
//==============================================================

void sim_buffer_clear(){
    while (rx_circle_count){
        if(++sim_read_point >= COM_SERIAL_RX_BUFFER_LENGTH)
            sim_read_point = 0;
        if(rx_circle_count)
            rx_circle_count--;
    }

    sim_read_point  = 0;
    rx_circle_count = 0;
    rx_circle_point = 0;
}

bool get_sim_data(BYTE* data){
    if(!rx_circle_count)
        return false;

    *data = COM0.rx.buf.data[sim_read_point];

    if(++sim_read_point >= COM_SERIAL_RX_BUFFER_LENGTH)
        sim_read_point = 0;
    rx_circle_count--;

    return true;
}


//================================================================
//================================================================
//================================================================
// ������� ��������� � ����������
// ���������� true ���� ����� ���������� ������
// ������� ������ ������ �� ������ data
//================================================================
// ����������
//================================================================
bool com_serial_tx_irq_SIM800(volatile com_serial_port_def* port, BYTE* data){
    if(port->tx.mode == ECSTM_STOP)
        return false;
    BYTE cond = port->tx.format;
    switch(cond) {
    case ECSTF_NOFORMAT:
        if(port->tx.buf.occupied >= COM_SERIAL_TX_BUFFER_LENGTH){
            com_serial_tx_stop(port);
            return false;
        }
        if(port->tx.out_ptr >= port->tx.buf.occupied){
            com_serial_tx_stop(port);
            return false;
        }
        *data = port->tx.buf.data[port->tx.out_ptr++];
        return true;
    default:
        com_serial_tx_stop(port);
    };

    com_serial_tx_stop(port);
    return false;
}

bool com_serial_tx_irq_USB(volatile com_serial_port_def* port, BYTE* data) {
    BYTE m;

    if (port->tx.mode == ECSTM_STOP)
        return false;
    BYTE cond = ECSTF_SLIP;

    switch (cond)
    {
    case ECSTF_SLIP: //WARNING check buffer lenght
        if (port->tx.buf.occupied >= (COM_SERIAL_TX_BUFFER_LENGTH + 6)) {
            com_serial_tx_stop(port);
            return false;
        }

        switch (port->tx.state) {
        case 0:// �������� ������� ������ ������
            *data = 0xC0; // ������ ������
            port->tx.state = 1;
            return true;

        case 1:// �������� �������������� ���������
            *data = 0x01; // ������������� ���������
            port->tx.state = 2;
            port->tx.crc = 0x5555;
            port->tx.crc++;
            return true;

        case 2: // �������� ������
            if (port->tx.out_ptr >= port->tx.buf.occupied) {
                switch (LOBYTE(port->tx.crc)) {
                case 0xC0:
                    port->tx.buf.data[port->tx.buf.occupied++] = 0xDB;
                    port->tx.buf.data[port->tx.buf.occupied++] = 0xDC;
                    break;
                case 0xDB:
                    port->tx.buf.data[port->tx.buf.occupied++] = 0xDB;
                    port->tx.buf.data[port->tx.buf.occupied++] = 0xDD;
                    break;
                default:
                    port->tx.buf.data[port->tx.buf.occupied++] = LOBYTE(port->tx.crc);
                }

                switch (HIBYTE(port->tx.crc)) {
                case 0xC0:
                    port->tx.buf.data[port->tx.buf.occupied++] = 0xDB;
                    port->tx.buf.data[port->tx.buf.occupied++] = 0xDC;
                    break;
                case 0xDB:
                    port->tx.buf.data[port->tx.buf.occupied++] = 0xDB;
                    port->tx.buf.data[port->tx.buf.occupied++] = 0xDD;
                    break;
                default:
                    port->tx.buf.data[port->tx.buf.occupied++] = HIBYTE(port->tx.crc);
                }
                *data = port->tx.buf.data[port->tx.out_ptr++];
                port->tx.state = 10;

                return true;
            }

            m = port->tx.buf.data[port->tx.out_ptr++];

            if (m == 0xC0) {
                port->tx.Slip_00 = 0xDC;
                port->tx.state = 3;
                *data = 0xDB;
                port->tx.crc += m;
                return true;
            }

            if (m == 0xDB){
                port->tx.Slip_00 = 0xDD;
                port->tx.state = 3;
                *data = 0xDB;
                port->tx.crc += m;
                return true;
            }

            port->tx.crc += m;
            *data = m;
            return true;
        case 3: // �������� ������� ����� ������ ��� �������������
            *data = port->tx.Slip_00;
            port->tx.state = 2;

            return true;
        case 10: // �������� ����������� �����
            if (port->tx.out_ptr >= port->tx.buf.occupied) {// �������� ������� ����� ������
                *data = 0xC0;
                port->tx.state = 12;

                return true;
            }

            *data = port->tx.buf.data[port->tx.out_ptr++];
            return true;
        case 12: // ���������� ��������
        default:
            com_serial_tx_stop(port);
            return false;
        }
    }
    com_serial_tx_stop(port);
    return false;
}

//================================================================
//================================================================


//================================================================
// ��Ȩ����
//================================================================
void com_serial_rx_irq_SIM800(volatile com_serial_port_def* port, BYTE x) {
    if (port->rx.dataready)
        return; // ���������� ������ ��� �� ���������
    switch(port->rx.format){
    case ECSRF_SIM300:
        if(rx_circle_count >= COM_SERIAL_RX_BUFFER_LENGTH)
            return;
        if(!sim_sending){
            port->rx.buf.data[rx_circle_point] = x;
            if (++rx_circle_point >= COM_SERIAL_RX_BUFFER_LENGTH)
                rx_circle_point = 0;
            rx_circle_count++;
        }
        return;
    default:
        port->rx.format = ECSRF_SLIP;
    };
}


void com_serial_rx_irq_USB(volatile com_serial_port_def* port, BYTE x) {
    if (port->rx.dataready) // ���������� ������ ��� �� ���������
        return;

    switch(port->rx.format){
    case ECSRF_SLIP:
        switch(port->rx.state){
        case 0:// �������� 0xC0
            if (x != 0xC0)
                return;
            port->rx.state = 1;
            return;
        case 1:
            if(x == 0xC0)
                return;
            if(x != 0x01){
                port->rx.state = 0;
                return;
            }

            port->rx.count = 0;
            port->rx.crc = 0x5555;
            port->rx.crc += x;
            port->rx.state = 2;
            return;
        case 2: // ����� ������ � �������� ������� �����
            switch(x){
            case 0xC0:// ������ ����� ������
                if (port->rx.count < 2) {
                    port->rx.state = 1;
                    return;
                }
                if ((port->rx.buf.data[port->rx.count - 2] != LOBYTE(port->rx.crc)) ||
                        (port->rx.buf.data[port->rx.count - 1] != HIBYTE(port->rx.crc))) {
                    port->rx.state = 1;
                    return;
                }
                port->rx.dataready = true;
                port->rx.buf.occupied = port->rx.count - 2;
                port->rx.state = 0xFF;
                return;
            case 0xDB:
                port->rx.state = 3;
                return;
            default:
MM02:
                if(port->rx.count >= (COM_SERIAL_RX_BUFFER_LENGTH + 2)){
                    port->rx.state = 0;
                    port->rx.count = 0;
                    return;
                }

                port->rx.buf.data[port->rx.count++] = x;

                if (port->rx.count > 2)
                    port->rx.crc += port->rx.buf.data[port->rx.count - 3];
                return;
            };

        case 3:
            switch(x){
            case 0xDC:
                x = 0xC0;
                port->rx.state = 2;
                goto MM02;
            case 0xDD:
                x = 0xD8;
                port->rx.state = 2;
                goto MM02;
            case 0xC0:
                port->rx.state = 1;
                return;
            };
            port->rx.state = 0;
            return;
        default:
            port->rx.state = 0;
        };
    default:
        port->rx.format = ECSRF_SLIP;
    }
}










