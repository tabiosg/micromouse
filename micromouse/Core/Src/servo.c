#include "servo.h"

void set_servo_angle(direction d)
{
	// TODO - confirm that these angles are what we want
	switch(d)
	{
	case Left:
		TIM2->CCR1 = SERVO_ANGLE_LEFT;
		return;
	case Front:
		TIM2->CCR1 = SERVO_ANGLE_FRONT;
		return;
	case Right:
		TIM2->CCR1 = SERVO_ANGLE_RIGHT;
		return;
	}  // switch(d)
}  // set_servo_angle(direction d)
