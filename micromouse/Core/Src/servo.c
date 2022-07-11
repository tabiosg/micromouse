#include "servo.h"

void set_servo_angle(direction d)
{
	// TODO - confirm that these angles are what we want
	switch(d)
	{
	case Left:
		TIM2->CCR1 = 180;
		return;
	case Front:
		TIM2->CCR1 = 100;
		return;
	case Right:
		TIM2->CCR1 = 20;
		return;
	}  // switch(d)
}  // set_servo_angle(direction d)
