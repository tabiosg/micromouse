#include "ultrasonic.h"

int risingEdgeInterrupt = 1;
int counter;
float centimeters = 18;

float distance_of_object_in_cm()
{
	printf("Distance is %f cm\r\n", centimeters);
	return centimeters;
}  // float distance_of_object_in_cm()
