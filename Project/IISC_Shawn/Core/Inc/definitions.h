#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "stm32f0xx_hal.h"
#include <stdbool.h>

/**
 * @file definitions.h
 * @brief Holds various definitions common to entire project
 */

/*******#defines*******/
/*Status*/
#define SUCCESS 1
#define FAILURE 0

/*Serial Acknowledge code*/
#define ACK 	55
#define NACK 	56

/*Serial Port Buffer*/
#define SERIAL_BUFFER_SIZE 10

/*UART Buffer*/
#define UART_BUFFER_SIZE 12

/*CRC seed*/
#define CRC_SEED 0xffff

/*Messgae to transmit size*/
#define MSG_SIZE 9

/*********Type definitions******/
/*Buffer Struct*/
typedef struct{
	  uint8_t write_index;	//Tracks which buffer slot is available to be filled
	  	  	  	  	  	  	//with new data
	  uint8_t read_index;	//Tracks which buffer slot is still pending processing
	  uint8_t num_pending;	//Tracks how many slots of data are pending processing
	  uint8_t buffer[SERIAL_BUFFER_SIZE];	//Buffer for serial port
}RING_BUFFER;


/******externs********/
/*externs of peripherals*/
extern TIM_HandleTypeDef htim14;
extern TIM_HandleTypeDef htim16;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

extern DMA_HandleTypeDef hdma_memtomem_dma1_channel1;

/*externs of variable/pointers*/
extern RING_BUFFER* p_serial_buffer;
extern DMA_HandleTypeDef* p_dma_handle;
extern UART_HandleTypeDef* p_uart_handle;


#endif
