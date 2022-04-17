#include "manual_control.h"

void execute_manual_command(char command)
{

	switch(command)
	{
	case LEFT_CHAR:
		manual_turn(Left, 0.6);
		break;
	case RIGHT_CHAR:
		manual_turn(Right, 0.6);
		break;
	case FORWARD_CHAR:
		manual_forward();
		break;
	case BACKWARD_CHAR:
		manual_backward();
		break;
	case AUTON_CHAR:
	case S_CHAR:
		manual_stop();
		break;
	default:
		break;
	}  // switch(command)
	current_manual_command = requested_manual_command;


}  // void execute_manual_command(char message[30])

void manual_turn(direction d, float speed_1)
{
	rotate_direction(d, speed_1);
}  // void manual_turn(direction d)

void manual_forward()
{
	motors_forward(0.5);
}  // void manual_forward()

void manual_backward()
{
	motors_backward(0.5);
}  // void manual_backward()

void manual_stop()
{
	stop_all_motors();
}  // void manual_stop()
