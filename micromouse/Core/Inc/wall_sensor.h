#ifndef INC_WALL_SENSOR_H_
#define INC_WALL_SENSOR_H_

#include "stdint.h"
#include "direction.h"
#include "servo.h"
#include "string.h"
#include "ultrasonic.h"

#define WALL_DISTANCE_CM 16
#define TOO_CLOSE_DISTANCE_CM 6

uint8_t is_there_wall_on_direction(direction d);

#endif /* INC_WALL_SENSOR_H_ */
