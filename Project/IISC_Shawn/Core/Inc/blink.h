#ifndef BLINK_H
#define BLINK_H

#include "serial_port.h"
#include "timer.h"
#include "multiples.h"

/**
 * @file blink.h
 * @brief This driver implements functions for the blinking and response msg operations
 *
 * @par Feature List:
 * 1, Enables/Disables Timers
 * 2, For each instruction, sets new pwm duty cycle, calculates if data is a multiple
 * of 4 and/or 7, generates response and transmits on serial
 * 3, Upon instruction completion, updates ring buffer indexes.
 * 4, Ensures indexes do not overun
 *
*/

/*Transmit msg buffer size*/
#ifndef MSG_SIZE
	#define MSG_SIZE	10
#endif

/**
 * @brief Description: Enables timers.
 *
 * @parm void
 *
 * @return void
 */
void enable_timers(void);

/**
 * @brief Description: Disables timers
 *
 * @parm void
 *
 * @return void
 */
void disable_timers(void);

/**
 * @brief Description: reads buffer slot, sets new pwm duty cycle,
 * checks if data is multiple of 4 and/or 7, generates response message and transmits
 *
 * @parm void
 *
 * @return void
 */
void begin_new_operation(void);

/**
 * @brief Description: Adjusts ring buffer indexes to reflect a completed operation
 * on a buffer slot
 *
 * @parm void
 *
 * @return void
 */
void conclude_current_operation(void);

/**
 * @brief Description: called upon timer elapse. Checks which timer triggered it.
 * tim14 -> set operation_complete flag
 *
 * @parm TIM_HandleTypeDef*: Handle of timer that triggered callback
 *
 * @return void
 */
void timer_elapsed_cb(TIM_HandleTypeDef*);

#endif
