#ifndef UART_SIM_H
#define UART_SIM_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "esp_log.h"

#define UART_SIM_NUM UART_NUM_2
#define TX_SIM_PIN (GPIO_NUM_10)
#define RX_SIM_PIN (GPIO_NUM_9)
#define BAUD_RATE_SIM 9600
#define BUF_SIZE_SIM 1024

#define TAG_UART_SIM "UART_SIM"

void uart_sim_init();

#endif
