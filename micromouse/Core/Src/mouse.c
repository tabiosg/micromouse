#include "mouse.h"

void rotate_direction(direction d)
{
	// TODO - make sure numbers are precise enough. need to tune
	switch(d)
	{
	case Left:
		set_motor_speed(Left_Motor, -200);
		set_motor_speed(Right_Motor, 200);
		HAL_Delay(445);
		stop_all_motors();
		return;
	case Front:
		return;
	case Right:
		set_motor_speed(Left_Motor, 200);
		set_motor_speed(Right_Motor, -200);
		HAL_Delay(445);
		stop_all_motors();
		return;
	}  // switch(d)
}  // rotate_direction(direction d)

void rotate_180_degrees()
{
	rotate_direction(Left);
	HAL_Delay(200);
	rotate_direction(Left);

}  // rotate_180_degrees()

void rotate_360_degrees(direction d)
{
	// This function is mainly used for testing and tuning
	switch(d)
	{
	case Left:
		set_motor_speed(Left_Motor, -200);
		set_motor_speed(Right_Motor, 200);
		HAL_Delay(1475);
		stop_all_motors();
		return;
	case Front:
		return;
	case Right:
		set_motor_speed(Left_Motor, 200);
		set_motor_speed(Right_Motor, -200);
		HAL_Delay(1700);
		stop_all_motors();
		return;
	}  // switch(d)

}  // rotate_360_degrees(direction d)

void go_forward_one_unit()
{
	// TODO - make sure numbers are precise enough. need to tune
	set_motor_speed(Left_Motor, 200);
	set_motor_speed(Right_Motor, 200);
	HAL_Delay(1000);
	stop_all_motors();
}  // go_forward()
