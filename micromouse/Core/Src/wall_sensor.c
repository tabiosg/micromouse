#include <wall_sensor.h>

uint8_t is_there_wall_on_direction(direction d)
{
	set_servo_angle(d);
	HAL_Delay(100);
	return distance_of_object_in_cm() < 18;
}  // is_there_wall_on_direction(direction d)
