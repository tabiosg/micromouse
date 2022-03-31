#include "ultrasonic.h"

int risingEdgeInterrupt = 1;
int counter;
float centimeters;

int16_t distance_of_object_in_cm()
{
	char string[40];
	sprintf((char *)string, "%f", centimeters * 1000);
//	HAL_UART_Transmit(&huart6, (uint8_t *)string, sizeof(string), 1000);
	printf("%f\r\n", centimeters);
	return centimeters;
}  // int16_t distance_of_object_in_cm()
