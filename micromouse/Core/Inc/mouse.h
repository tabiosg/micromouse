#ifndef INC_MOUSE_H_
#define INC_MOUSE_H_

#include "direction.h"
#include "stdio.h"
#include "motors.h"
#include "servo.h"
#include "ultrasonic.h"
#include "main.h"
#include "manual_control.h"

void recalibrate_by_turning();

void calibrate_at_walls_move_back();

void rotate_direction_90(direction d);

void rotate_180_degrees();

void rotate_360_degrees(direction d);

void go_forward_one_unit();

#endif /* INC_MOUSE_H_ */
