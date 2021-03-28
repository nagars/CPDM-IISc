#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include "dma.h"
#include "crc.h"

/**
 * @file serial_port.h
 * @brief This driver acts as the serial port library for communication with
 * another system via uart
 *
 * @par Feature List:
 * 1, Can receive data from uart bus in interrupt mode
 * 2, Can transmit data to uart bus
 * 3, Can specify uart port based on keyhandler
 * 4, Performs CRC check
 * 5, Returns Acknowledge / Not Acknowledge Code
 * 6, Fills ring buffer and updates indexes
 * 7, Serial port can only initialise 1 uart port as the uart buffer is a global buffer
 * 8, Allows for user to assign serial port buffer
 * 9, Baud rate cannot be changed on the fly
 */

/*Serial Port Buffer*/
#ifndef SERIAL_BUFFER_SIZE
	#define SERIAL_BUFFER_SIZE 8
#endif

/*UART Buffer*/
#ifndef UART_BUFFER_SIZE
	#define UART_BUFFER_SIZE 10
#endif

/**
 * @brief Description: Initialisation routine for serial port driver
 *
 * @param RING_BUFFER* : pointer to serial port buffer struct
 * @param UART_HandleTypeDef* : UART peripheral handle
 * @param DMA_HandleTypeDef* : DMA peripheral handle
 *
 * @return void
 */
void serial_port_init(RING_BUFFER*, UART_HandleTypeDef*, DMA_HandleTypeDef*);

/**
 * @brief Description: transmits message via initialised uart with crc
 *
 * @param const uint8_t* : data array to transmit
 * @param uint8_t : Number of bytes to transmit
 * @return void
 */
void serial_transmit(const uint8_t*, uint8_t);


#endif
