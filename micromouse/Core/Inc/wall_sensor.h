#ifndef INC_WALL_SENSOR_H_
#define INC_WALL_SENSOR_H_

#include "stdint.h"
#include "direction.h"
#include "servo.h"
#include "ultrasonic.h"

uint8_t is_there_wall_on_direction(direction d);

#endif /* INC_WALL_SENSOR_H_ */
