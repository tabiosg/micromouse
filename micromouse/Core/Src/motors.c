#include "motors.h"

int LEFT_MOTOR_MULT = LEFT_MOTOR_MULT_DEFAULT;
int RIGHT_MOTOR_MULT = RIGHT_MOTOR_MULT_DEFAULT;

void set_motor_speed(motor_side side, int16_t speed400)
{
	// speed400 is a number in [-400, 400]
	switch(side)
	{
	case Left_Motor:
		// Low is forward
		HAL_GPIO_WritePin(LEFT_DIR_GPIO_Port, LEFT_DIR_Pin, speed400 > 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
		TIM4->CCR1 = speed400 > 0 ? speed400 : -speed400;
		return;
	case Right_Motor:
		HAL_GPIO_WritePin(RIGHT_DIR_GPIO_Port, RIGHT_DIR_Pin, speed400 > 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
		TIM3->CCR2 = speed400 > 0 ? speed400 : -speed400;
		return;
	}  // switch(side)
}  // set_motor_speed(motor_side side, int16_t speed400)

void stop_motor(motor_side side)
{
	set_motor_speed(side, 0);
}  // stop_motor(motor_side side)

void stop_all_motors()
{
	printf("Currently stopping the motors.\r\n");
	char buf[20];
	memcpy(buf, "$STOP,,,,,,,,,,,,,,", 20);
	HAL_UART_Transmit(&huart6, buf, sizeof(buf), 1000);
	stop_motor(Left_Motor);
	stop_motor(Right_Motor);
}  // stop_all_motors()

void rotate_direction(direction d, float speed_1)
{
	// TODO - make sure numbers are precise enough. need to tune
	char buf[20];
	switch(d)
	{
	case Left:
		printf("Currently rotating left.\r\n");
		memcpy(buf, "$LEFT,,,,,,,,,,,,,,", 20);
		HAL_UART_Transmit(&huart6, buf, sizeof(buf), 1000);
		set_motor_speed(Left_Motor, -LEFT_MOTOR_MULT * speed_1);
		set_motor_speed(Right_Motor, RIGHT_MOTOR_MULT * speed_1);
		return;
	case Front:
		return;
	case Right:
		printf("Currently rotating right.\r\n");
		memcpy(buf, "$RIGHT,,,,,,,,,,,,,", 20);
		HAL_UART_Transmit(&huart6, buf, sizeof(buf), 1000);
		set_motor_speed(Left_Motor, LEFT_MOTOR_MULT * speed_1);
		set_motor_speed(Right_Motor, -RIGHT_MOTOR_MULT * speed_1);
		return;
	}  // switch(d)
}  // rotate_direction(direction d, float speed_1)

void motors_forward(float speed_1)
{
	printf("Moving the motors forward.\r\n");
	char buf[20];
	memcpy(buf, "$FORWARD,,,,,,,,,,,", 20);
	HAL_UART_Transmit(&huart6, buf, sizeof(buf), 1000);
	set_motor_speed(Left_Motor, -LEFT_MOTOR_MULT * speed_1);
	set_motor_speed(Right_Motor, -RIGHT_MOTOR_MULT * speed_1);
}  // void motors_forward(float speed_1)

void motors_backward(float speed_1)
{
	printf("Moving the motors backward.\r\n");
	char buf[20];
	memcpy(buf, "$BACKWARD,,,,,,,,,,", 20);
	HAL_UART_Transmit(&huart6, buf, sizeof(buf), 1000);
	set_motor_speed(Left_Motor, LEFT_MOTOR_MULT * speed_1);
	set_motor_speed(Right_Motor, RIGHT_MOTOR_MULT * speed_1);
}  // void motors_backward(float speed_1)

