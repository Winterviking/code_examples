
#include "drv_uart.h"
#include "drv_serial_port.h"

// HAL uart
UART_HandleTypeDef uart_handle;

void drv_uart_init(bool parity)
{
    __USART1_CLK_ENABLE();  // USARTx_CLK_ENABLE();

    uart_handle.Instance            = USART1;  //USARTx;
    uart_handle.Init.BaudRate       = 115200;
    uart_handle.Init.StopBits       = UART_STOPBITS_1;
    uart_handle.Init.Parity         = UART_PARITY_EVEN;
    uart_handle.Init.WordLength     = UART_WORDLENGTH_9B;
    uart_handle.Init.HwFlowCtl      = UART_HWCONTROL_NONE;
    uart_handle.Init.Mode           = UART_MODE_TX_RX;

    HAL_UART_Init(&uart_handle);

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.Pin          = GPIO_PIN_9;
    GPIO_InitStructure.Mode         = GPIO_MODE_AF_PP;
    GPIO_InitStructure.Pull         = GPIO_NOPULL;
    GPIO_InitStructure.Speed        = GPIO_SPEED_FAST;
    GPIO_InitStructure.Alternate    = GPIO_AF4_USART1;

    HAL_GPIO_Init(GPIOA,&GPIO_InitStructure);

    GPIO_InitStructure.Pin          = GPIO_PIN_10;
    GPIO_InitStructure.Alternate    = GPIO_AF4_USART1;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);


    //if (HAL_UART_Init(&UartHandle) != HAL_OK)fault_Error_Handler();
    __HAL_UART_ENABLE_IT(&uart_handle, UART_IT_RXNE);
    __HAL_UART_ENABLE_IT(&uart_handle, UART_IT_TC);

    HAL_NVIC_SetPriority((IRQn_Type) USART1_IRQn, 0, 0);
    //HAL_NVIC_SetPriority((IRQn_Type) USART1_IRQn, 2, 1);
    HAL_NVIC_EnableIRQ((IRQn_Type) USART1_IRQn);
}

void drv_uart_deinit()
{
    HAL_NVIC_DisableIRQ((IRQn_Type) USART1_IRQn);

    __HAL_UART_DISABLE_IT(&uart_handle, UART_IT_RXNE);
    __HAL_UART_DISABLE_IT(&uart_handle, UART_IT_TC);

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.Pin          = GPIO_PIN_9;
    GPIO_InitStructure.Mode         = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull         = GPIO_NOPULL;
    GPIO_InitStructure.Speed        = GPIO_SPEED_LOW;

    GPIOA->BSRR = GPIO_PIN_9;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

    __USART1_CLK_DISABLE();  ///USARTx_CLK_ENABLE();
}


BYTE x;

void USART1_IRQHandler() // def name
{
    if (uart_handle.Instance->ISR & UART_FLAG_ORE)
        __HAL_UART_CLEAR_IT(&uart_handle, UART_CLEAR_OREF);

    if(uart_handle.Instance->ISR & UART_FLAG_RXNE) // switch????
    {
        com_serial_rx_irq_SIM800(&COM0, (uint8_t)uart_handle.Instance->RDR);
        uart_handle.Instance->ISR &= ~UART_FLAG_RXNE;
    }

    if(uart_handle.Instance->ISR & UART_FLAG_TC)
    {
        uart_handle.Instance->ISR &= ~UART_FLAG_TC;
        __HAL_UART_CLEAR_IT(&uart_handle, UART_CLEAR_TCF);
        if (com_serial_tx_irq_SIM800(&COM0,&x))
        {
            uart_handle.Instance->TDR = x;
        }
    }
}

void com_serial_generate_tx(volatile com_serial_port_def* port){
    BYTE x;
    if (port->PortNum != 0)
        return;

    if (com_serial_tx_irq_SIM800( port, &x ))
        uart_handle.Instance->TDR=x;
}

void uart_send(BYTE x){
    uart_handle.Instance->TDR = x;
}








