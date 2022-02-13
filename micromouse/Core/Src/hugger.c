#include "hugger.h"

void do_hug_left_algorithm()
{
	// Keep to the left.
	if (!is_there_wall_on_direction(LEFT))
	{
		// If there is an opening on the left, then we head there.
		rotate_direction(LEFT);
		go_forward();
	}
	else if (is_there_wall_on_direction(FRONT))
	{
		// There is wall on both left and on front

		// There is also wall on right
		if (is_there_wall_on_direction(RIGHT))
		{
			rotate_180_degrees();
			go_forward();
		}
		// There is no wall on right
		rotate_direction(RIGHT);
		go_forward();
	}
	else
	{
		// Just go forward if there is no wall in front but a wall on left
		go_forward();
	}  // if()

	if (found_destination())
	{
		return;
	}

	return do_hug_left_algorithm();
}

uint8_t found_destination()
{
	return 0;
}
