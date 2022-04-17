#ifndef INC_MOTORS_H_
#define INC_MOTORS_H_

#include "stdint.h"
#include "main.h"
#include "string.h"
#include "direction.h"

#define LEFT_MOTOR_MULT 172
#define RIGHT_MOTOR_MULT 200

typedef enum
{
	Left_Motor, Right_Motor
} motor_side;

void set_motor_speed(motor_side side, int16_t speed400);

void stop_motor(motor_side side);

void stop_all_motors();

void rotate_direction(direction d, float speed_1);

void motors_forward(float speed_1);

void motors_backward(float speed_1);

#endif /* INC_MOUSE_H_ */
