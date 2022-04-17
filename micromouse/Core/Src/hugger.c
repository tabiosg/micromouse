#include "hugger.h"

void do_hug_left_algorithm()
{
	// Keep to the left.
	if(!is_there_wall_on_direction(Left))
	{
		// If there is an opening on the left, then we head there.
		rotate_direction_90(Left);
		go_forward_one_unit();
	}
	else if(is_there_wall_on_direction(Front))
	{
		// There is wall on both left and on front

		// There is also wall on right
		if(is_there_wall_on_direction(Right))
		{
			rotate_180_degrees();
			go_forward_one_unit();
		}
		else
		{
			// There is no wall on right
			rotate_direction_90(Right);
			go_forward_one_unit();
		}  // if(is_there_wall_on_direction(RIGHT))
	}
	else
	{
		// Just go forward if there is no wall in front but a wall on left
		go_forward_one_unit();
	}  // if()

	if(found_hugger_destination())
	{
		return;
	}  // if(found_hugger_destination())

	return do_hug_left_algorithm();
}  // do_hug_left_algorithm()

uint8_t found_hugger_destination()
{
	// TODO - but there might not be a real way to know if you found a destination
	return 0;
}  // found_hugger_destination()
