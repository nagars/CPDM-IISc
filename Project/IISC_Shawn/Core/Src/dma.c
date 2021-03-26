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
