#include "blink.h"

extern RING_BUFFER serial_buffer;		//Struct containing indexes and buffer
extern char msg[MSG_SIZE];				//Char array for message to be return to pc
extern bool operation_complete_flag;	//To track of current blink operation is done or not

void enable_timers(void){

	//Enable pwm and timers
	enable_timer(&htim14);				//triggers every 10sec (for led and msg response operation)
	enable_timer(&htim17);				//triggers every 2 sec (for blinking)
	enable_pwm(&htim16, TIM_CHANNEL_1);	//for pwm

	return;
}

void disable_timers(void){

	//disable both timers and pwm
	disable_timer(&htim14);
	disable_timer(&htim17);
	disable_pwm(&htim16, TIM_CHANNEL_1);

	return;
}

void begin_new_operation(void){

	//clear operation complete flag
	operation_complete_flag = false;

	//clear msg buffer
	for(uint8_t n = 0; n < MSG_SIZE; n++){
		msg[n] = 0;
	}

	//check for 4 and 7
	check_multiples(serial_buffer.buffer[serial_buffer.read_index], msg);

	//Transmit msg
	serial_transmit_msg(msg, MSG_SIZE);

	//Begin new 10 sec LED blink operation with updated duty cycle
	set_pwm_duty_cycle(&htim16, serial_buffer.buffer[serial_buffer.read_index]);

	return;
}

void conclude_current_operation(void){

	//Decrement number of pending buffer slots
	serial_buffer.num_pending--;

	//Increment read index on buffer
	serial_buffer.read_index++;

	//Reset read_index if it exceeds buffer size
	if(serial_buffer.read_index >= SERIAL_BUFFER_SIZE){
		serial_buffer.read_index = 0;
	}

	return;
}


void timer_elapsed_cb(TIM_HandleTypeDef *htm){

	//Checks which timer has triggered callback
	if(htm == &htim17){					//2 sec completed

		//Checks if pwm is disabled
		if((*(&htim16.Instance->CR1)&(0x01)) == false){
			//Enabled pwm
			enable_pwm(&htim16, TIM_CHANNEL_1);

		}else{
			//Disabled pwm
			disable_pwm(&htim16, TIM_CHANNEL_1);
		}

	} else if(htm == &htim14){			//10 sec completed

		//set operation_complete flag
		operation_complete_flag = true;

	}

	return;
}
