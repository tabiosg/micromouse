#ifndef INC_ULTRASONIC_H_
#define INC_ULTRASONIC_H_

#include "main.h"

extern int risingEdgeInterrupt;
extern int counter;
extern float centimeters;

int16_t distance_of_object_in_cm();

#endif /* INC_ULTRASONIC_H_ */
