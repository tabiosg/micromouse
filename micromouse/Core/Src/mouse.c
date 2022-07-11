#include "mouse.h"

void recalibrate_by_turning()
{
	set_servo_angle(Front);
	int total_change = 0;
	direction recalibrate_dir[6] = { Left, Right, Left, Right, Left, Right };
	float min_cm_front = distance_of_object_in_cm();
	for (int i = 0; i < 4; ++i)
	{
		direction readjust_dir = recalibrate_dir[i];
		for (int j = 0; j < 6; ++j)
		{
			total_change += readjust_dir - 1;
			if (total_change >= 10 || total_change <= -10)
			{
				return;
			}
			if (requested_manual_command != AUTON_CHAR)
			{
				return 0;
			}  // if (requested_manual_command != AUTON_CHAR)
			rotate_direction(readjust_dir, 0.5);
			HAL_Delay(30);
			stop_all_motors();
			HAL_Delay(100);
			float current_cm_front = distance_of_object_in_cm();
			if (current_cm_front < min_cm_front - 1)
			{
				break;  // if it jumped too much, then you probably looked at a different wall, so break.
			}
			else if (current_cm_front < min_cm_front)
			{
				min_cm_front = current_cm_front;
			}  // if (current_cm_front > max_cm_front)
			else if (current_cm_front > min_cm_front * 1.000005)
			{
				break;  // if getting larger, then break
			}  // else
		}  // while (1)
	}
	rotate_direction(Left, 0.5);
	HAL_Delay(30);
	stop_all_motors();
	HAL_Delay(400);

}  // void recalibrate_by_turning()

void calibrate_at_walls()
{
	set_servo_angle(Left);
	motors_backward(0.75);
	HAL_Delay(150);
	stop_all_motors();
	HAL_Delay(500);
	float distance_left_cm = distance_of_object_in_cm();
	set_servo_angle(Right);
	HAL_Delay(1000);
	float distance_right_cm = distance_of_object_in_cm();
	set_servo_angle(Front);

	if (distance_left_cm < 16 && distance_right_cm < 16)
	{
		float distance_difference_right_left_cm = distance_right_cm - distance_left_cm;
		int proposed_left_motor_mult = LEFT_MOTOR_MULT - distance_difference_right_left_cm * 10;
		// Subtract for the left motor multiplier because the left motor is actually the right one
		LEFT_MOTOR_MULT = proposed_left_motor_mult < LEFT_MOTOR_MULT_DEFAULT - MAX_MULT_CHANGE_RANGE ? LEFT_MOTOR_MULT : proposed_left_motor_mult;
		LEFT_MOTOR_MULT = proposed_left_motor_mult > LEFT_MOTOR_MULT_DEFAULT + MAX_MULT_CHANGE_RANGE ? LEFT_MOTOR_MULT : proposed_left_motor_mult;
	}
	motors_forward(0.75);
	HAL_Delay(150);
	stop_all_motors();
	HAL_Delay(400);

}

void rotate_direction_90(direction d)
{
	recalibrate_by_turning();
	set_servo_angle(Front);
	// TODO - make sure numbers are precise enough. need to tune
	switch(d)
	{
	case Left:
		rotate_direction(Left, 1);
		HAL_Delay(390);
		stop_all_motors();
		return;
	case Front:
		return;
	case Right:
		rotate_direction(Right, 1);
		HAL_Delay(400);
		stop_all_motors();
		return;
	}  // switch(d)

	// Done to try to adjust the robot.
	recalibrate_by_turning();
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
	HAL_Delay(640);
	stop_all_motors();
	HAL_Delay(200);
	calibrate_at_walls();
	recalibrate_by_turning();
}  // go_forward_one_unit()
