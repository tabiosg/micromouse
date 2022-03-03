#include "test.h"

void do_test_algorithm()
{
	turn_LED(Yellow, On);
	for (int i = 0; i < 4; ++i)
	{
		rotate_direction(Left);
		go_forward_one_unit();
	}
	for (int i = 0; i < 4; ++i)
	{
		rotate_direction(Right);
		go_forward_one_unit();
	}
	turn_LED(Yellow, Off);
	for (int i = 0; i < 4; ++i)
	{
		rotate_180_degrees();
		go_forward_one_unit();
	}
	return do_test_algorithm();
}  // do_test_algorithm()
