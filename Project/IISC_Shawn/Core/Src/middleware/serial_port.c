#include "serial_port.h"

//Declare UART buffer
uint8_t receive_buffer[UART_BUFFER_SIZE] = {0};

//Declare serial port ring buffer struct pointer
RING_BUFFER* p_serial_buffer;

//Declare dma handle pointer
DMA_HandleTypeDef* p_dma_handle;

//Declare uart handle pointer
UART_HandleTypeDef* p_uart_handle;

void serial_port_init(RING_BUFFER* _serial_buffer, UART_HandleTypeDef* _uart_handle,
		DMA_HandleTypeDef* _dma_handle){

	//Assign pointer to DMA handle to global pointer
	p_dma_handle = _dma_handle;

	//Assign pointer to DMA handle to global pointer
	p_uart_handle = _uart_handle;

	//Set pointer to serial buffer
	p_serial_buffer = _serial_buffer;

	//Configure DMA callback functions
	dma_register_callbacks(_dma_handle, dma_transfer_complete_cb,
			dma_transfer_failure_cb);

	//Enable UART receive interrupts
	if(HAL_UART_Receive_IT(_uart_handle, receive_buffer, UART_BUFFER_SIZE) != HAL_OK){
		//set error code
	}

	return;
}

void serial_transmit_msg(char* msg, uint8_t num_bytes){

	//encode crc

	//append to data

	//Transmit message
	if(HAL_UART_Transmit_IT(p_uart_handle, (uint8_t*)msg, num_bytes) != HAL_OK){

	}

	return;
}

void encode_crc(void){


	return;
}

bool check_crc(void){

	//Performs crc checks

	//returns success / failure
	return SUCCESS;
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef* _uart_handle){

	//check which uart handle triggered callback
	if(_uart_handle == &huart1){

		//If crc failed, transmit NACK else, transmit ACK & Trigger DMA transfer
		if(check_crc() == FAILURE){

			//Transmit Not-Acknowledged
			uint8_t send_nack = NACK;
			if(HAL_UART_Transmit_IT(_uart_handle, &send_nack, 1) != HAL_OK){

			}


		}else{

		//Trigger DMA transfer. To be replaced once crc implemented

		//HAL_DMA_Start_IT(p_dma_handle, (uint32_t)CRC RESULT DATA,
		//	(uint32_t)p_serial_buffer, 1);
		HAL_DMA_Start_IT(p_dma_handle, (uint32_t)receive_buffer,
				(uint32_t)(p_serial_buffer->buffer + p_serial_buffer->write_index), 1);

		}


		return;
	}

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* _uart_handle){

	//Enable UART receive interrupts
	if(HAL_UART_Receive_IT(_uart_handle, receive_buffer, UART_BUFFER_SIZE) != HAL_OK){

	}

}

void HAL_UART_ErrorCallback(UART_HandleTypeDef* _uart_handle){

}
