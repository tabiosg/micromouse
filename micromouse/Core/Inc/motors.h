#ifndef INC_MOTORS_H_
#define INC_MOTORS_H_

typedef enum
{
	Left, Right
} motor_side;

void move_motors(motor_side side, float arbitrary_unit);


#endif /* INC_MOUSE_H_ */
