#include <wall_sensor.h>

uint8_t is_there_wall_on_direction(direction d)
{
	set_servo_angle(d);
	HAL_Delay(1000);
	uint8_t wall_detected = distance_of_object_in_cm() < 18;
	char buf[20];
	switch(d)
	{
	case Left:
		memcpy(buf, wall_detected ? "\%LEFT,0,,,,,,,,,,,," : "\%LEFT,0,,,,,,,,,,,,", 20);
		break;
	case Front:
		memcpy(buf, wall_detected ? "%FRONT,1,,,,,,,,,,," : "%FRONT,0,,,,,,,,,,,", 20);
		break;
	case Right:
		memcpy(buf, wall_detected ? "%RIGHT,1,,,,,,,,,,," : "%RIGHT,0,,,,,,,,,,,", 20);
		break;
	}  // switch(d)
	HAL_UART_Transmit(&huart6, buf, sizeof(buf), 1000);
	return wall_detected;
}  // is_there_wall_on_direction(direction d)
