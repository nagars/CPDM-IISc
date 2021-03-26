#ifndef DMA_H
#define DMA_H

#include "definitions.h"

/**
 * @file dma.h
 * @brief This driver implements DMA functions to be used by the serial port
 * library
 *
 * @par Feature List:
 * 1, Can register callbacks for complete transfer through DMA or failed transfer.
 * 2, Implements callback functions for serial port driver
 * 3, DMA channel and callbacks can be assigned by user
 * 4, Current success callback sends an ack on uart line
 * 5, Current failure callback sends a nack on uart line
*/

/**
 * @brief Description: registers callbacks for dma operations.
 *
 * @param DMA_HandleTypeDef* : DMA peripheral handle
 * @param void (*)(DMA_HandleTypeDef*) : Callback for a successful transfer
 * @param void (*)(DMA_HandleTypeDef*) : Callback for failed transfer
 *
 * @return void
 */
void dma_register_callbacks(DMA_HandleTypeDef * _hdma,
		void(*transfer_complete_cb)(DMA_HandleTypeDef * _hdma),
		void(*transfer_failure_cb)(DMA_HandleTypeDef * _hdma));

/**
 * @brief Description: callback for successful dma transfer
 *
 * @param DMA_HandleTypeDef* : DMA peripheral handle
 *
 * @return void
 */
void dma_transfer_complete_cb(DMA_HandleTypeDef * _hdma);

/**
 * @brief Description: callback for failed dma transfer
 *
 * @param DMA_HandleTypeDef* : DMA peripheral handle
 *
 * @return void
 */
void dma_transfer_failure_cb(DMA_HandleTypeDef * _hdma);

#endif
