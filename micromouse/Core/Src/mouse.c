#include "mouse.h"

void rotate_direction_90(direction d)
{


	// TODO - make sure numbers are precise enough. need to tune
	switch(d)
	{
	case Left:
		rotate_direction(Left, 1);
		HAL_Delay(333);
		stop_all_motors();
		return;
	case Front:
		return;
	case Right:
		rotate_direction(Right, 1);
		HAL_Delay(342);
		stop_all_motors();
		return;
	}  // switch(d)
}  // rotate_direction_90(direction d)

void rotate_180_degrees()
{
	rotate_direction_90(Left);
	HAL_Delay(200);
	rotate_direction_90(Left);

}  // rotate_180_degrees()

void rotate_360_degrees(direction d)
{
	// This function is mainly used for testing and tuning
	switch(d)
	{
	case Left:
		rotate_direction(Left, 1);
		HAL_Delay(1475);
		stop_all_motors();
		return;
	case Front:
		return;
	case Right:
		rotate_direction(Right, 1);
		HAL_Delay(1700);
		stop_all_motors();
		return;
	}  // switch(d)

}  // rotate_360_degrees(direction d)

void go_forward_one_unit()
{
	motors_forward(1);
	HAL_Delay(629);
	stop_all_motors();
}  // go_forward()
