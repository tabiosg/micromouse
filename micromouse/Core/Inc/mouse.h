#ifndef INC_MOUSE_H_
#define INC_MOUSE_H_

#include "direction.h"
#include "motors.h"
#include "main.h"

void rotate_direction(direction d);

void rotate_180_degrees();

void rotate_360_degrees(direction d);

void go_forward_one_unit();

#endif /* INC_MOUSE_H_ */
