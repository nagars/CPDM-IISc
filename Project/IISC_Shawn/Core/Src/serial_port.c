#include "serial_port.h"

//Declare UART buffer
uint8_t receive_buffer[UART_BUFFER_SIZE] = {0};

//Declare serial port ring buffer pointer
uint8_t* p_serial_buffer;

void serial_port_init(uint8_t* _serial_buffer, UART_HandleTypeDef* _uart_handle){

	//Enable UART receive interrupts
	if(HAL_UART_Receive_IT(_uart_handle, receive_buffer, UART_BUFFER_SIZE) != HAL_OK){

	}

	//Set pointer to serial buffer
	p_serial_buffer = _serial_buffer;

	return;
}

void check_crc(){

	//Performs crc checks

	//returns success / failure
	return;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* _uart_handle){

	//check which uart handle triggered callback
	if(_uart_handle == &huart1){
		check_crc();

		//If crc failed, transmit NACK else, transmit ACK & Trigger DMA transfer

		/**FOR TESTING ONLY**/
		if(HAL_UART_Transmit_IT(_uart_handle, receive_buffer, 5) != HAL_OK){

		}
		/***/
	}

}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef* _uart_handle){

	//Enable UART receive interrupts
	if(HAL_UART_Receive_IT(_uart_handle, receive_buffer, UART_BUFFER_SIZE) != HAL_OK){

	}

}

void HAL_USART_ErrorCallback(UART_HandleTypeDef* _uart_handle){


}
