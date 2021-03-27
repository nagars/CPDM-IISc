#ifndef BLINK_H
#define BLINK_H

#include "serial_port.h"
#include "timer.h"
#include "multiples.h"

/*Transmit msg buffer size*/
#define MSG_SIZE	10

void enable_timers(void);
void disable_timers(void);

void begin_new_operation(void);
void conclude_current_operation(void);


#endif
