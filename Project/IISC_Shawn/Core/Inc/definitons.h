#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "stm32f0xx_hal.h"

/*Serial Port Buffer*/
#define SERIAL_BUFFER_SIZE 5

/*UART Buffer*/
#define UART_BUFFER_SIZE 5

/*externs of peripherals*/
extern TIM_HandleTypeDef htim14;
extern TIM_HandleTypeDef htim16;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart1_rx;

#endif
