#ifndef INC_MANUAL_CONTROL_H_
#define INC_MANUAL_CONTROL_H_

#include "motors.h"
#include "direction.h"

#define LEFT_CHAR '4'
#define RIGHT_CHAR '6'
#define FORWARD_CHAR '2'
#define BACKWARD_CHAR '5'
#define S_CHAR '8'
#define AUTON_CHAR 'A'

void execute_manual_command(char command);

void manual_turn(direction d);

void manual_forward();

void manual_backward();

void manual_stop();

#endif /* INC_MANUAL_CONTROL_H_ */
