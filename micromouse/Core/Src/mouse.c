#include "mouse.h"

void rotate_direction(direction d)
{
	// TODO - see how to turn
	switch (d)
	{
	case LEFT:
		move_motors(LEFT, 10);
		move_motors(RIGHT, -10);
		return;
	case FRONT:
		return;
	case RIGHT:
		move_motors(LEFT, -10);
		move_motors(RIGHT, 10);
		return;
	}  // switch()
}

void rotate_180_degrees()
{
	// TODO - see how to rotate 180 degrees
	rotate_direction(LEFT);
	rotate_direction(LEFT);
}

void go_forward()
{
	// TODO - see how to go forward
	move_motors(LEFT, 10);
	move_motors(RIGHT, 10);
}
