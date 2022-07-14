#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "direction.h"
#include "main.h"

#define SERVO_ANGLE_LEFT 180
#define SERVO_ANGLE_FRONT 100
#define SERVO_ANGLE_RIGHT 20

void set_servo_angle(direction d);

#endif /* INC_SERVO_H_ */
