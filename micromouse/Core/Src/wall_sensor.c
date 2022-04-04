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
		sprintf((char *)buf, "\%LEFT,%u", wall_detected);
		break;
	case Front:
		sprintf((char *)buf, "\%FRONT,%u", wall_detected);
		break;
	case Right:
		sprintf((char *)buf, "\%RIGHT,%u", wall_detected);
		break;
	}  // switch(d)
	HAL_UART_Transmit(&huart6, buf, sizeof(buf), 1000);
	return wall_detected;
}  // is_there_wall_on_direction(direction d)
