#ifndef INC_MOTORS_H_
#define INC_MOTORS_H_

#include "stdint.h"
#include "main.h"
#include "string.h"
#include "direction.h"

#define MAX_MULT_CHANGE_RANGE 15
#define MOTOR_MULT_CHANGE_MULTIPLIER 5

#define LEFT_MOTOR_MULT_DEFAULT 172
#define RIGHT_MOTOR_MULT_DEFAULT 210

int LEFT_MOTOR_MULT = LEFT_MOTOR_MULT_DEFAULT;
int RIGHT_MOTOR_MULT = RIGHT_MOTOR_MULT_DEFAULT;

typedef enum
{
	Left_Motor, Right_Motor
} motor_side;

void set_motor_speed(motor_side side, int16_t speed400);

void stop_motor(motor_side side);

void stop_all_motors();

void rotate_direction(direction d, float speed_1);

void calibrate_at_walls();

void motors_forward(float speed_1);

void motors_backward(float speed_1);

#endif /* INC_MOUSE_H_ */
