#include "manual_control.h"

void execute_manual_command(char message[30])
{
	if(message[0] != '$') {
		manual_stop();
	}  // if(message[0] != '$')

	switch(message[1]) {
	case 'l':
		manual_turn(Left);
		break;
	case 'r':
		manual_turn(Left);
		break;
	case 'f':
		manual_forward();
		break;
	case 'b':
		manual_backward();
		break;
	case 's':
	default:
		manual_stop();
		break;
	}  // switch(message[1])


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
