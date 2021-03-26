#include "dma.h"

void dma_register_callbacks(DMA_HandleTypeDef * _hdma,
		void (*transfer_complete_cb)(DMA_HandleTypeDef * _hdma),
		void (*transfer_failure_cb)(DMA_HandleTypeDef * _hdma)){

	//Configure DMA success callback
	HAL_DMA_RegisterCallback (_hdma,
			HAL_DMA_XFER_CPLT_CB_ID , transfer_complete_cb);

	//Configure DMA failure callback
	HAL_DMA_RegisterCallback (_hdma,
			HAL_DMA_XFER_ERROR_CB_ID , transfer_failure_cb);

	return;
}

void dma_transfer_complete_cb(DMA_HandleTypeDef * _hdma){

	if(_hdma == p_dma_handle){

		//Transmit Acknowledged
		uint8_t send_ack = ACK;
		if(HAL_UART_Transmit_IT(p_uart_handle, &send_ack, 1) != HAL_OK){

		}

		//Increment pending data counter of buffer
		p_serial_buffer->num_pending++;

		//Increment write index of serial buffer
		p_serial_buffer->write_index++;

		//Check if write_index is at end of buffer. Reset if yes.
		if(p_serial_buffer->write_index >= SERIAL_BUFFER_SIZE){
			p_serial_buffer->write_index = 0;
		}

	}

	return;
}

void dma_transfer_failure_cb(DMA_HandleTypeDef * _hdma){

	if(_hdma == p_dma_handle){

		//Transmit Not-Acknowledged
		uint8_t send_nack = NACK;
		if(HAL_UART_Transmit_IT(p_uart_handle, &send_nack, 1) != HAL_OK){

		}
	}

	return;
}
