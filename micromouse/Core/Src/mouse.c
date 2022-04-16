#include "mouse.h"

void rotate_direction_90(direction d)
{


	// TODO - make sure numbers are precise enough. need to tune
	switch(d)
	{
	case Left:
		motors_backward(1);
		HAL_Delay(20);
		rotate_direction(Left, 1);
		HAL_Delay(345);
		motors_forward(1);
		HAL_Delay(79);
		stop_all_motors();
		return;
	case Front:
		return;
	case Right:
		motors_backward(1);
		HAL_Delay(39);
		rotate_direction(Right, 1);
		HAL_Delay(369);
		motors_forward(1);
		HAL_Delay(20);
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
	HAL_Delay(709);
	stop_all_motors();
}  // go_forward()
