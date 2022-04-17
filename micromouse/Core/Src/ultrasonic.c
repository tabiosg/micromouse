#include "ultrasonic.h"

int risingEdgeInterrupt = 1;
int counter;
float centimeters;

int16_t distance_of_object_in_cm()
{
	printf("Distance is %f cm\r\n", centimeters);
	return centimeters;
}  // int16_t distance_of_object_in_cm()
