#include "motors.h"

void set_motor_speed(motor_side side, int16_t speed400)
{
	// speed400 is a number in [-400, 400]
	switch(side)
	{
	case Left_Motor:
		// Low is forward
		HAL_GPIO_WritePin(LEFT_DIR_GPIO_Port, LEFT_DIR_Pin, speed400 > 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
		TIM4->CCR1 = speed400 > 0 ? speed400 : -speed400;
		return;
	case Right_Motor:
		HAL_GPIO_WritePin(RIGHT_DIR_GPIO_Port, RIGHT_DIR_Pin, speed400 > 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
		TIM3->CCR2 = speed400 > 0 ? speed400 : -speed400;
		return;
	}  // switch(side)
}  // set_motor_speed(motor_side side, int16_t speed400)

void stop_motors(motor_side side)
{
	set_motor_speed(side, 0);
}  // stop_motors(motor_side side)

void stop_all_motors()
{
	set_motor_speed(Left_Motor, 0);
	set_motor_speed(Right_Motor, 0);
}  // stop_all_motors()

void rotate_direction(direction d)
{
	// TODO - make sure numbers are precise enough. need to tune
	switch(d)
	{
	case Left:
		set_motor_speed(Left_Motor, -200);
		set_motor_speed(Right_Motor, 200);
		return;
	case Front:
		return;
	case Right:
		set_motor_speed(Left_Motor, 200);
		set_motor_speed(Right_Motor, -200);
		return;
	}  // switch(d)
}  // rotate_direction(direction d)

void motors_forward()
{
	set_motor_speed(Left_Motor, 200);
	set_motor_speed(Right_Motor, 200);
}  // void motors_forward()

void motors_backward()
{
	set_motor_speed(Left_Motor, -200);
	set_motor_speed(Right_Motor, -200);
}  // void motors_forward()

