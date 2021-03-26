#ifndef TIMER_H
#define TIMER_H

#include "definitions.h"

/**
 * Description: This driver implements timer functions used for the PWM, Led Blinking
 * and time keeping
 *
 * Feature List:
 * 1, Enabled/Disabled Timer
 * 2, Enabled/Disabled PWM
 * 3, Adjusts PWM duty cycle
 *
*/

/**
 * @brief Description: Enables timer module.
 *
 * @par Parameters:
 * - TIM_HandleTypeDef *htm: Timer module handle
 *
 * @return void
 */
void enable_timer(TIM_HandleTypeDef*);

/**
 * @brief Description: Disables timer module.
 *
 * @par Parameters:
 * - TIM_HandleTypeDef *htm: Timer module handle
 *
 * @return void
 */
void disable_timer(TIM_HandleTypeDef*);

/**
 * @brief Description: Enables timer module to be used for PWM.
 *
 * @par Parameters:
 * - TIM_HandleTypeDef *htm: Timer module handle
 * - uint32_t channel: Channel from timer to pwm peripheral
 *
 * @return void
 */
void enable_pwm(TIM_HandleTypeDef*, uint32_t);

/**
 * @brief Description: Disables pwm signal from time.
 *
 * @par Parameters:
 * - TIM_HandleTypeDef *htm: Timer module handle
 * - uint32_t channel: Channel from timer to pwm peripheral
 *
 * @return void
 */
void disable_pwm(TIM_HandleTypeDef*, uint32_t);

/**
 * @brief Description: sets pwm duty cycle
 *
 * @par Parameters:
 * - TIM_HandleTypeDef *htm: Timer module handle
 * - uint8_t duty_cycle: Duty cycle to set
 *
 * @return void
 */
void set_pwm_duty_cycle(TIM_HandleTypeDef*, uint8_t);

#endif
