#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include <definitions.h>
#include "dma.h"

/**
 * Description: This driver acts as the serial port library for communication with
 * another system via uart
 *
 * Feature List:
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

void serial_port_init(uint8_t*, UART_HandleTypeDef*, DMA_HandleTypeDef*);

bool check_crc(void);

#endif
