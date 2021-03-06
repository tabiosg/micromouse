#include "test.h"

void test_turn_left()
{
	rotate_direction_90(Right);
	HAL_Delay(1000);
}  // void test_turn_left()

void test_alternate_left_right()
{
	rotate_direction_90(Left);
	HAL_Delay(1000);
	rotate_direction_90(Right);
	HAL_Delay(1000);
}  // void test_alternate_left_right()

void test_zig_zag()
{
	go_forward_one_unit();
	HAL_Delay(1000);
	rotate_direction_90(Right);
	HAL_Delay(1000);
	go_forward_one_unit();
	HAL_Delay(1000);
	rotate_direction_90(Left);
	HAL_Delay(1000);
	go_forward_one_unit();
	HAL_Delay(1000);
	rotate_direction_90(Right);
	HAL_Delay(1000);
	go_forward_one_unit();
	HAL_Delay(1000);
	rotate_180_degrees();
	HAL_Delay(1000);

	go_forward_one_unit();
	HAL_Delay(1000);
	rotate_direction_90(Left);
	HAL_Delay(1000);
	go_forward_one_unit();
	HAL_Delay(1000);
	rotate_direction_90(Right);
	HAL_Delay(1000);
	go_forward_one_unit();
	HAL_Delay(1000);
	rotate_direction_90(Left);
	HAL_Delay(1000);
	go_forward_one_unit();
	HAL_Delay(1000);
	rotate_180_degrees();

}  // void test_zig_zag()

void test_alternate_360()
{
	rotate_360_degrees(Left);
	HAL_Delay(1000);
	rotate_360_degrees(Right);
	HAL_Delay(1000);
}  // void test_alternate_360()

void test_wall_sensor()
{
	uint8_t left_wall = is_there_wall_on_direction(Left);
	HAL_Delay(1000);
	uint8_t right_wall = is_there_wall_on_direction(Right);
	HAL_Delay(1000);
	uint8_t front_wall = is_there_wall_on_direction(Front);
	HAL_Delay(1000);
}

void test_servo_angles()
{
	TIM2->CCR1 = 75; // right
	TIM2->CCR1 = 100;
	TIM2->CCR1 = 125;
	TIM2->CCR1 = 150;
	TIM2->CCR1 = 175;
	TIM2->CCR1 = 200;
	TIM2->CCR1 = 225;// left
}

void do_test_algorithm()
{
	if (requested_manual_command != AUTON_CHAR)
	{
		return;
	}


//	test_alternate_left_right();
//	test_zig_zag();
	test_turn_left();
//	test_wall_sensor();
//	test_servo_angles();

//	go_forward_one_unit();
//	HAL_Delay(2000);

//	distance_of_object_in_cm();

	return do_test_algorithm();
}  // do_test_algorithm()
