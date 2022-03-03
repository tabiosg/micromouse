#include "mouse.h"

void rotate_direction(direction d)
{
	// TODO - make sure numbers are precise enough. need to tune
	switch(d)
	{
	case Left:
		set_motor_speed(Left, 200);
		set_motor_speed(Right, -200);
		HAL_Delay(3000);
		stop_all_motors();
		return;
	case Front:
		return;
	case Right:
		set_motor_speed(Left, -200);
		set_motor_speed(Right, 200);
		HAL_Delay(3000);
		stop_all_motors();
		return;
	}  // switch(d)
}  // rotate_direction(direction d)

void rotate_180_degrees()
{
	rotate_direction(Left);
	rotate_direction(Left);
}  // rotate_180_degrees()

void go_forward_one_unit()
{
	// TODO - make sure numbers are precise enough. need to tune
	set_motor_speed(Left, 200);
	set_motor_speed(Right, 200);
	HAL_Delay(3000);
	stop_all_motors();
}  // go_forward()
