#include "servo.h"

void set_servo_angle(direction d)
{
	// TODO - confirm that these angles are what we want
	switch(d)
	{
	case Left:
		TIM2->CCR1 = 50;
		return;
	case Front:
		TIM2->CCR1 = 150;
		return;
	case Right:
		TIM2->CCR1 = 250;
		return;
	}  // switch(d)
}  // set_servo_angle(direction d)
