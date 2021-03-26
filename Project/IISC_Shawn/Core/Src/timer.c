#include "timer.h"

uint8_t duty = 0;

void enable_timer(TIM_HandleTypeDef *_htm){

	/*HAL Macro to initialize timer and enable module*/
	if(HAL_TIM_Base_Start_IT(_htm) != HAL_OK){

	}

	return;
}

void disable_timer(TIM_HandleTypeDef *_htm){

	/*HAL Macro to disable module*/
	__HAL_TIM_DISABLE(_htm);

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

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htm){

	if(htm == &htim14){

		/**For testing only**/
		set_pwm_duty_cycle(&htim16, duty + 10);
		duty+=10;
		/***/

		//Check if another data instruction is waiting in qeue

		//If not, disable both timer and pwm

	}

}

