#include "manual_control.h"

void execute_manual_command(char command)
{

	switch(command)
	{
	case 'l':
		rotate_direction(Left);
		break;
	case 'r':
		rotate_direction(Right);
		break;
	case 'f':
		motors_forward();
		break;
	case 'b':
		motors_backward();
		break;
	case 's':
		stop_all_motors();
		break;
	default:
		break;
	}  // switch(command)
	current_manual_command = requested_manual_command;


}  // void execute_manual_command(char message[30])

void manual_turn(direction d)
{
	rotate_direction(d);
}  // void manual_turn(direction d)

void manual_forward()
{
	motors_forward();
}  // void manual_forward()

void manual_backward()
{
	motors_backward();
}  // void manual_backward()

void manual_stop()
{
	stop_all_motors();
}  // void manual_stop()
