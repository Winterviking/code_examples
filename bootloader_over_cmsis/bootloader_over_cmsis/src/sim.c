
#include "sim.h"
#include "drv_serial_port.h"
#include "drv_clock.h"


//
// SIM800 модуль или любой аналогичный

void radio_reset(bool reset) {
    if(reset)
        RADIO_RESET_PORT->BRR = RADIO_RESET_PIN;
    else
        RADIO_RESET_PORT->BSRR = RADIO_RESET_PIN;
}

void radio_boot(bool boot) {
    if (boot)
        RADIO_BOOT_PORT->BSRR = RADIO_BOOT_PIN;
    else
        RADIO_BOOT_PORT->BRR = RADIO_BOOT_PIN;
}

void radio_init() {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin      = RADIO_RESET_PIN;
    GPIO_InitStructure.Mode     = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull     = GPIO_NOPULL;
    GPIO_InitStructure.Speed    = GPIO_SPEED_LOW;

    HAL_GPIO_Init(RADIO_RESET_PORT, &GPIO_InitStructure);

    RADIO_RESET_PORT->BRR = RADIO_RESET_PIN;

    GPIO_InitStructure.Pin      = RADIO_BOOT_PIN;
    GPIO_InitStructure.Mode     = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull     = GPIO_NOPULL;
    GPIO_InitStructure.Speed    = GPIO_SPEED_LOW;

    HAL_GPIO_Init(RADIO_BOOT_PORT, &GPIO_InitStructure);

    RADIO_BOOT_PORT->BRR = RADIO_BOOT_PIN;
}

void radio_deinit() {
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin      = RADIO_RESET_PIN;
    GPIO_InitStructure.Mode     = GPIO_MODE_ANALOG;
    GPIO_InitStructure.Pull     = GPIO_NOPULL;
    GPIO_InitStructure.Speed    = GPIO_SPEED_LOW;

    HAL_GPIO_Init(RADIO_RESET_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.Pin      = RADIO_BOOT_PIN;
    GPIO_InitStructure.Mode     = GPIO_MODE_ANALOG;
    GPIO_InitStructure.Pull     = GPIO_NOPULL;
    GPIO_InitStructure.Speed    = GPIO_SPEED_LOW;

    HAL_GPIO_Init(RADIO_BOOT_PORT, &GPIO_InitStructure);
}

void radio_wake() {
    WAIT(100);

    com_serial_tx_clear(&COM0);

    com_serial_tx_add_byte(&COM0,'U');
    com_serial_tx_add_byte(&COM0,'\r');
    com_serial_tx_add_byte(&COM0,'\n');

    com_serial_tx_start(&COM0);
}






