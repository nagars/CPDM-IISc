#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "stm32f0xx_hal.h"
#include <stdbool.h>

/*Status*/
#define SUCCESS 1
#define FAILURE 0

/*Serial Port Buffer*/
#define SERIAL_BUFFER_SIZE 5

/*UART Buffer*/
#define UART_BUFFER_SIZE 5

/*externs of peripherals*/
extern TIM_HandleTypeDef htim14;
extern TIM_HandleTypeDef htim16;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_memtomem_dma1_channel1;

/*externs of variable/pointers*/

//dma handle pointer
extern DMA_HandleTypeDef* p_dma_handle;
//uart handle pointer
extern UART_HandleTypeDef* p_uart_handle;

/*Serial Acknowledge code*/
#define ACK 	0xFE
#define NACK 	0xFF

#endif
