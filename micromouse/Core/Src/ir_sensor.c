#include "ir_sensor.h"

uint8_t is_there_wall_on_direction(direction d)
{
	// TODO - see how to find out
	switch (d)
	{
	case LEFT:
		return 1;
	case FRONT:
		return 1;
	case RIGHT:
		return 1;
	}  // switch()

	return -1;
}
