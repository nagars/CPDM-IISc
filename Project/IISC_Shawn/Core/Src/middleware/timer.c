#include "timer.h"

//Stores timer elapsed callback function pointer assigned by user
void (*timer_complete_cb)(TIM_HandleTypeDef *_htm);

void enable_timer(TIM_HandleTypeDef *_htm){


	//Clear Capture occurred bit. Issue with HAL? Seems to be set upon init of timer,
	//causing interrupt trigger upon mcu bootup. Clearing this bit prevents that.
	 __HAL_TIM_CLEAR_FLAG(_htm,TIM_FLAG_CC1 );

	//HAL Macro to initialize timer and enable module
	if(HAL_TIM_Base_Start_IT(_htm) != HAL_OK){
	}


	return;
}

void disable_timer(TIM_HandleTypeDef *_htm){

	//HAL Macro to disable module*/
	if(HAL_TIM_Base_Stop_IT(_htm) != HAL_OK){
	}


	return;
}

void enable_pwm(TIM_HandleTypeDef *_htm, uint32_t channel){

	if(HAL_TIM_PWM_Start(_htm, channel) != HAL_OK){

	}

	return;
}

void disable_pwm(TIM_HandleTypeDef *_htm, uint32_t channel){

	if(HAL_TIM_PWM_Stop(_htm, channel) != HAL_OK){

	}

	return;
}

void set_pwm_duty_cycle(TIM_HandleTypeDef *_htm, uint8_t duty_cycle){

	//Ensure duty cycle cuts off at 100
	if(duty_cycle > 100){
		duty_cycle = 100;
	}

	//Current period
	uint16_t current_period_val = _htm->Init.Period;

	//Calculate new output compare value to meet new duty cycle
	uint16_t compare_val = (duty_cycle * current_period_val)/100;

	//Set new output compare value
	_htm->Instance->CCR1 = (compare_val - 1);

	return;

}

void register_timer_complete_callback(void (*_timer_complete_cb)(TIM_HandleTypeDef*)){

	//assigns user function to be called on timer elapse
	timer_complete_cb = _timer_complete_cb;

}

//Triggered when timer capture compare occurs
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htm){

	//Calls user assigned function
	timer_complete_cb(htm);

}
