#include "mouse.h"

void rotate_direction_90(direction d)
{


	// TODO - make sure numbers are precise enough. need to tune
	switch(d)
	{
	case Left:
		printf("Rotating left. \r\n");
		rotate_direction(Left);
		HAL_Delay(445);
		stop_all_motors();
		return;
	case Front:
		return;
	case Right:
		printf("Rotating right. \r\n");
		rotate_direction(Right);
		HAL_Delay(445);
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
		rotate_direction(Left);
		HAL_Delay(1475);
		stop_all_motors();
		return;
	case Front:
		return;
	case Right:
		rotate_direction(Right);
		HAL_Delay(1700);
		stop_all_motors();
		return;
	}  // switch(d)

}  // rotate_360_degrees(direction d)

void go_forward_one_unit()
{
	// TODO - make sure numbers are precise enough. need to tune
	printf("Heading forward. \r\n");
	motors_forward();
	HAL_Delay(1000);
	stop_all_motors();
}  // go_forward()
