#ifndef INC_MANUAL_CONTROL_H_
#define INC_MANUAL_CONTROL_H_

#include "motors.h"
#include "direction.h"

void execute_manual_command(char message[30]);

void manual_turn(direction d);

void manual_forward();

void manual_backward();

void manual_stop();

#endif /* INC_MANUAL_CONTROL_H_ */
