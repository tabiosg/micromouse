#include <wall_sensor.h>

uint8_t is_there_wall_on_direction(direction d)
{
	set_servo_angle(d);
	HAL_Delay(1000);
	int16_t distance_cm = distance_of_object_in_cm();
	uint8_t wall_detected = distance_cm < 16 ;
	char buf[20];
	switch(d)
	{
	case Left:
		printf(wall_detected ? "There is a wall on the left.\r\n" : "There is no wall on the left.\r\n");
		memcpy(buf, wall_detected ? "\%LEFT,0,,,,,,,,,,,," : "\%LEFT,0,,,,,,,,,,,,", 20);
		break;
	case Front:
		printf(wall_detected ? "There is a wall in front.\r\n" : "There is no wall in front.\r\n");
		memcpy(buf, wall_detected ? "%FRONT,1,,,,,,,,,,," : "%FRONT,0,,,,,,,,,,,", 20);
		break;
	case Right:
		printf(wall_detected ? "There is a wall on the right.\r\n" : "There is no wall on the right.\r\n");
		memcpy(buf, wall_detected ? "%RIGHT,1,,,,,,,,,,," : "%RIGHT,0,,,,,,,,,,,", 20);
		break;
	}  // switch(d)
	HAL_UART_Transmit(&huart6, buf, sizeof(buf), 1000);
	return wall_detected;
}  // is_there_wall_on_direction(direction d)
