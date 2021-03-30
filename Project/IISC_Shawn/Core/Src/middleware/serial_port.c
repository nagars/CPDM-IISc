#include "serial_port.h"
#include <string.h>

//Declare UART receive buffer
uint8_t receive_buffer[UART_BUFFER_SIZE] = {0};

//Declare UART transmit buffer
uint8_t transmit_buffer[UART_BUFFER_SIZE] = {0};

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

	//Assign pointer to UART handle to global pointer
	p_uart_handle = _uart_handle;

	//Set global pointer to serial buffer
	p_serial_buffer = _serial_buffer;

	//Configure DMA callback functions
	dma_register_callbacks(_dma_handle, dma_transfer_complete_cb,
			dma_transfer_failure_cb);

	//Enable UART receive interrupts
	if(HAL_UART_Receive_IT(_uart_handle, receive_buffer, UART_BUFFER_SIZE) != HAL_OK){

		//Reset UART RX error state and re-attempt
		//_uart_handle->RxState = HAL_UART_STATE_READY;
		//HAL_UART_Receive_IT(_uart_handle, receive_buffer, UART_BUFFER_SIZE);
	}

	return;
}

void serial_transmit(const uint8_t* msg, uint8_t msg_size){

	//clear buffer
	//Ensures last 2 bytes reserved for crc are 0 as required for crc16.
	//Rest of the transmit buffer is reserved for the msg
	for(uint8_t n = 0; n < UART_BUFFER_SIZE; n++){
		transmit_buffer[n] = 0;
	}

	//Ensures msg size fits within uart buffer after appending of crc
	if(msg_size > UART_BUFFER_SIZE - 2){
		//Copy enough of msg to fit in buffer and leave last 2 bytes. Ignore the rest
		memcpy(transmit_buffer, msg, UART_BUFFER_SIZE - 2);
	}else{
		//Copy entire msg
		memcpy(transmit_buffer, msg, msg_size);
	}



	//Generate crc16 encoded transmit message.
	generate_crc16_msg(crc16_ccitt_table, transmit_buffer, UART_BUFFER_SIZE);

	//Transmit message
	if(HAL_UART_Transmit_IT(p_uart_handle, transmit_buffer, UART_BUFFER_SIZE) != HAL_OK){

		//If failed, Reset uart error state and re-attempt
		//p_uart_handle->gState = HAL_UART_STATE_READY;
		//HAL_UART_Transmit_IT(p_uart_handle, transmit_buffer, UART_BUFFER_SIZE);

	}

	return;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* _uart_handle){

	//check which uart handle triggered callback
	if(_uart_handle == p_uart_handle){

		//If crc failed, transmit NACK else, transmit ACK & Trigger DMA transfer
		bool data_valid = check_crc16(crc16_ccitt_table, receive_buffer,
							UART_BUFFER_SIZE);
		if(data_valid == FAILURE){

			//Transmit Not-Acknowledged
			uint8_t send_nack = NACK;
			serial_transmit(&send_nack, 1);

		}else{

			//Trigger DMA transfer of valid data to serial buffer.
			//Instruction from pc is only 1 bytes, hence 1 byte transferred
			//Return not acknowledge if DMA fails
			if(HAL_DMA_Start_IT(p_dma_handle, (uint32_t)receive_buffer,
				(uint32_t)(p_serial_buffer->buffer + p_serial_buffer->write_index), 1) != HAL_OK){

				//Transmit Not-Acknowledged
				uint8_t send_nack = NACK;
				serial_transmit(&send_nack, 1);
			}

		}

		return;
	}

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* _uart_handle){

	//check which uart handle triggered callback
	if(_uart_handle == p_uart_handle){
		//Enable UART receive interrupts
		if(HAL_UART_Receive_IT(p_uart_handle, receive_buffer, UART_BUFFER_SIZE) != HAL_OK){

			//If failed, reset UART RX error state and re-attempt
			//_uart_handle->RxState = HAL_UART_STATE_READY;
			//HAL_UART_Receive_IT(p_uart_handle, receive_buffer, UART_BUFFER_SIZE);
		}
	}

}

void HAL_UART_ErrorCallback(UART_HandleTypeDef* _uart_handle){

	//check which uart handle triggered callback
	if(_uart_handle == p_uart_handle){
		//If UART receive/transmit error occurs, reset state
		_uart_handle->RxState = HAL_UART_STATE_READY;
		_uart_handle->gState = HAL_UART_STATE_READY;

		//Transmit Not-Acknowledged
		uint8_t send_nack = NACK;
		serial_transmit(&send_nack, 1);
	}

}
