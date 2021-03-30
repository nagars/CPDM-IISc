#include "timer.h"

//Stores timer elapsed callback function pointer assigned by user
void (*timer_complete_cb)(TIM_HandleTypeDef *_htm);

void enable_timer(TIM_HandleTypeDef *_htm){

	//Clear Capture occurred bit. Issue with HAL? Seems to be set upon init of timer,
	//causing interrupt trigger upon first enable of Timer.
	//Clearing this bit prevents that.
	 __HAL_TIM_CLEAR_FLAG(_htm,TIM_FLAG_CC1 );

	//HAL Macro to enable peripheral
	HAL_TIM_Base_Start_IT(_htm);

	return;
}

void disable_timer(TIM_HandleTypeDef *_htm){

	//HAL Macro to disable peripheral
	HAL_TIM_Base_Stop_IT(_htm);

	return;
}

void enable_pwm(TIM_HandleTypeDef *_htm, uint32_t channel){

	//HAL Macro to enable peripheral
	HAL_TIM_PWM_Start(_htm, channel);

	return;
}

void disable_pwm(TIM_HandleTypeDef *_htm, uint32_t channel){

	//HAL Macro to disable peripheral
	HAL_TIM_PWM_Stop(_htm, channel);

	return;
}

void set_pwm_duty_cycle(TIM_HandleTypeDef *_htm, uint8_t duty_cycle){

	//Ensure duty cycle cuts off at 100
	if(duty_cycle > 100){
		duty_cycle = 100;
	}

	//Current period of timer
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

	return;
}

//Triggered when timer capture compare occurs
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htm){

	//Calls user assigned function
	timer_complete_cb(htm);

	return;
}
