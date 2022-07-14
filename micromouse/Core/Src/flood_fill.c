#include "flood_fill.h"

uint8_t do_flood_fill_algorithm()
{
	// Initialize the maze
	flood_fill_maze maze;

	/*
	for (uint8_t i = 0; i < MAP_SIZE; ++i)
	{
		for (uint8_t j = 0; j < MAP_SIZE; ++j)
		{
			// Initialize distance grid
			if(i <= 7 && j <= 7) maze.distance_grid[i][j] = ((7 - i) + (7 - j));
			else if(i <= 7 && j > 7) maze.distance_grid[i][j] = ((7 - i) + (j - 8));
			else if(i > 7 && j <= 7) maze.distance_grid[i][j] = ((i - 8) + (7 - j));
			else if(i > 7 && j > 7) maze.distance_grid[i][j] = ((i - 8) + (j - 8));

			// Initialize cell grid - assume no walls unless border by default
			maze.cell_grid[i][j].walls[North] = No_Wall_Here;
			maze.cell_grid[i][j].walls[East] = No_Wall_Here;
			maze.cell_grid[i][j].walls[South] = No_Wall_Here;
			maze.cell_grid[i][j].walls[West] = No_Wall_Here;
			maze.cell_grid[i][j].visited = Is_Not_Visited;

			if(i == 0) maze.cell_grid[i][j].walls[South] = Wall_Here;
			if(j == 0) maze.cell_grid[i][j].walls[West] = Wall_Here;
			if(i == MAP_SIZE - 1) maze.cell_grid[i][j].walls[North] = Wall_Here;
			if(j == MAP_SIZE - 1) maze.cell_grid[i][j].walls[East] = Wall_Here;

		}  // for (uint8_t j = 0; j < MAP_SIZE; ++j)
	}  // for (uint8_t i = 0; i < MAP_SIZE; ++i)
	*/

	// TEMPORARY - WE'RE USING A 4 BY 4 MAZE FOR THE DEMO
	for (uint8_t i = 0; i < MAP_SIZE; ++i)
		{
			for (uint8_t j = 0; j < MAP_SIZE; ++j)
			{
				// Initialize distance grid
//				maze.distance_grid[i][j] = 255;

				// Initialize cell grid - assume no walls unless border by default
				maze.cell_grid[i][j].walls[North] = No_Wall_Here;
				maze.cell_grid[i][j].walls[East] = No_Wall_Here;
				maze.cell_grid[i][j].walls[South] = No_Wall_Here;
				maze.cell_grid[i][j].walls[West] = No_Wall_Here;
				maze.cell_grid[i][j].visited = Is_Not_Visited;

				if(i == 0) maze.cell_grid[i][j].walls[South] = Wall_Here;
				if(j == 0) maze.cell_grid[i][j].walls[West] = Wall_Here;
				if(i == MAP_SIZE - 1) maze.cell_grid[i][j].walls[North] = Wall_Here;
				if(j == MAP_SIZE - 1) maze.cell_grid[i][j].walls[East] = Wall_Here;

			}  // for (uint8_t j = 0; j < MAP_SIZE; ++j)
		}  // for (uint8_t i = 0; i < MAP_SIZE; ++i)
	maze.distance_grid[0][0] = 6;
	maze.distance_grid[0][1] = 5;
	maze.distance_grid[0][2] = 4;
	maze.distance_grid[0][3] = 3;
	maze.distance_grid[1][0] = 5;
	maze.distance_grid[1][1] = 4;
	maze.distance_grid[1][2] = 3;
	maze.distance_grid[1][3] = 2;
	maze.distance_grid[2][0] = 4;
	maze.distance_grid[2][1] = 3;
	maze.distance_grid[2][2] = 2;
	maze.distance_grid[2][3] = 1;
	maze.distance_grid[3][0] = 3;
	maze.distance_grid[3][1] = 2;
	maze.distance_grid[3][2] = 1;
	maze.distance_grid[3][3] = 0;

	// Do flood fill algorithm

	maze_direction desired_direction = North;  // the direction that we want to move in next
	maze_direction direction = desired_direction;  // the direction we're currently facing
	coordinate next_coordinate;
	init_coordinate(&next_coordinate, 0, 0);  // Always start in South, West corner facing North.

	coordinate c = next_coordinate;  // c is the coordinate that we are currently in

	stack stack;
	stack.index = 0;

	// TODO - BASICALLY COPY PASTING CODE

	printf("Currently at x=%i, y=%i facing direction=%i.\r\n", c.x, c.y, direction);
	char buf5[20];
	sprintf((char *)buf5, "@%i,%i,%i,,,,,,,,,,,,,", c.x, c.y, (uint8_t)direction);
	HAL_UART_Transmit(&huart6, buf5, sizeof(buf5), 1000);

	if (requested_manual_command != AUTON_CHAR) return 0;

	if(is_there_wall_on_direction(Front))
	{
		maze.cell_grid[c.y][c.x].walls[direction] = Wall_Here;
		if(c.y + 1 < MAP_SIZE) maze.cell_grid[c.y + 1][c.x].walls[South] = Wall_Here;

	}  // if(is_there_wall_on_direction(Front))
  
	if (requested_manual_command != AUTON_CHAR) return 0;

	if(is_there_wall_on_direction(Right))
	{
		maze.cell_grid[c.y][c.x].walls[(direction + 1) % 4] = Wall_Here;
		if(c.x - 1 > -1) maze.cell_grid[c.y][c.x - 1].walls[East] = Wall_Here;

	}  // if(is_there_wall_on_direction(Right))

	if (requested_manual_command != AUTON_CHAR) return 0;

	maze.cell_grid[c.y][c.x].visited = 1;


	// need to figure next direction to go to and also update rest of distance grid.
	desired_direction = minus_one_neighbor(&maze, c, &stack);

	if(desired_direction == Unknown)
	{
		while(!stack_is_empty(&stack))
		{
			if (requested_manual_command != AUTON_CHAR) return 0;
			if (stack.index >= 60)
			{
				char buf3[20];
				sprintf((char *)buf3, "&FAILED,,,,,,,,,,,,");
				HAL_UART_Transmit(&huart6, buf3, sizeof(buf3), 1000);
				return 0;
			}  // if (stack.index >= 100)
			// get the cell to test from the stack
			next_coordinate = pop_stack(&stack);
			// find a neighbor cell with distance one less than current
			minus_one_neighbor(&maze, next_coordinate, &stack);
		}  // while(stack.index != 0)
		// next_direction is the direction to go to next
		desired_direction = minus_one_neighbor(&maze, c, &stack);
	}  // if(next_direction == Unknown)
	int difference = desired_direction - direction + 4;
	char buf2[20];
	sprintf((char *)buf2, "^%i,%i,%i,,,,,,,,,,,,,", direction, desired_direction, difference % 4);
	HAL_UART_Transmit(&huart6, buf2, sizeof(buf2), 1000);
	switch(difference % 4)
	{
	case 0:
		break;
	case 1:
		rotate_direction_90(Right);
		break;
	case 2:
		rotate_180_degrees();
		break;
	case 3:
		rotate_direction_90(Left);
		break;
	}

	direction = desired_direction;

	set_servo_angle(Front);
	while(1)
	{
		if (requested_manual_command != AUTON_CHAR) return 0;

		switch(direction)
		{
		case North:
			c.y += 1;
			break;
		case East:
			c.x += 1;
			break;
		case South:
			c.y -= 1;
			break;
		case West:
			c.x -= 1;
			break;
		case Unknown:
			break;
		}  // switch(direction)

		LEFT_MOTOR_MULT = LEFT_MOTOR_MULT_DEFAULT;
		RIGHT_MOTOR_MULT = RIGHT_MOTOR_MULT_DEFAULT;
    
		if(!maze.cell_grid[c.y][c.x].visited)
		{
			// Move in direction for unvisited cell
			go_forward_one_unit();

			if(found_flood_fill_destination(c, &maze))
			{
				set_servo_angle(Front);

				printf("Currently at x=%i, y=%i facing direction=%i.\r\n", c.x, c.y, direction);
				char buf5[20];
				sprintf((char *)buf5, "@%i,%i,%i,,,,,,,,,,,,,", c.x, c.y, (uint8_t)direction);
				HAL_UART_Transmit(&huart6, buf5, sizeof(buf5), 1000);

				printf("Completed maze!\r\n");
				char buf[20];
				memcpy(buf, "&COMPLETED,,,,,,,,,", 20);
				HAL_UART_Transmit(&huart6, buf, sizeof(buf), 1000);
				return 1;
			}  // if(found_flood_fill_destination(&c, &maze))

			printf("Currently at x=%i, y=%i facing direction=%i.\r\n", c.x, c.y, direction);
			char buf[20];
			sprintf((char *)buf, "@%i,%i,%i,,,,,,,,,,,,,", c.x, c.y, (uint8_t)direction);
			HAL_UART_Transmit(&huart6, buf, sizeof(buf), 1000);

			set_servo_angle(Front);
			HAL_Delay(1000);

			float distance_front_cm = distance_of_object_in_cm();

			char buf_front[20];
			printf(distance_front_cm < WALL_DISTANCE_CM ? "There is a wall in front.\r\n" : "There is no wall in front.\r\n");
			memcpy(buf_front, distance_front_cm < WALL_DISTANCE_CM ? "%FRONT,1,,,,,,,,,,," : "%FRONT,0,,,,,,,,,,,", 20);

			HAL_UART_Transmit(&huart6, buf_front, sizeof(buf_front), 1000);


			set_servo_angle(Left);
			HAL_Delay(1000);
			float distance_left_cm = distance_of_object_in_cm();
			char buf_left[20];

			printf(distance_left_cm < WALL_DISTANCE_CM ? "There is a wall on the left.\r\n" : "There is no wall on the left.\r\n");
			memcpy(buf_left, distance_left_cm < WALL_DISTANCE_CM ? "\%LEFT,1,,,,,,,,,,,," : "\%LEFT,0,,,,,,,,,,,,", 20);

			HAL_UART_Transmit(&huart6, buf_left, sizeof(buf_left), 1000);



			set_servo_angle(Right);
			HAL_Delay(1000);
			float distance_right_cm = distance_of_object_in_cm();

			char buf_right[20];

			printf(distance_right_cm < WALL_DISTANCE_CM ? "There is a wall on the right.\r\n" : "There is no wall on the right.\r\n");
			memcpy(buf_right, distance_right_cm < WALL_DISTANCE_CM ? "%RIGHT,1,,,,,,,,,,," : "%RIGHT,0,,,,,,,,,,,", 20);

			HAL_UART_Transmit(&huart6, buf_right, sizeof(buf_right), 1000);

			set_servo_angle(Front);


//			if (distance_left_cm < WALL_DISTANCE_CM && distance_right_cm < WALL_DISTANCE_CM)
//			{
//
//				if (distance_left_cm < TOO_CLOSE_DISTANCE_CM || distance_right_cm < TOO_CLOSE_DISTANCE_CM)
//				{
//					motors_backward(0.5);
//					HAL_Delay(200);
//					stop_all_motors();
//					HAL_Delay(500);
//				}
//
//
//				float distance_difference_right_left_cm = distance_right_cm - distance_left_cm;
//				int proposed_left_motor_mult = LEFT_MOTOR_MULT - distance_difference_right_left_cm * MOTOR_MULT_CHANGE_MULTIPLIER;
//				// Subtract for the left motor multiplier because the left motor is actually the right one
//				LEFT_MOTOR_MULT = proposed_left_motor_mult < LEFT_MOTOR_MULT_DEFAULT - MAX_MULT_CHANGE_RANGE ? LEFT_MOTOR_MULT : proposed_left_motor_mult;
//				LEFT_MOTOR_MULT = proposed_left_motor_mult > LEFT_MOTOR_MULT_DEFAULT + MAX_MULT_CHANGE_RANGE ? LEFT_MOTOR_MULT : proposed_left_motor_mult;
//
//				if (distance_left_cm < TOO_CLOSE_DISTANCE_CM || distance_right_cm < TOO_CLOSE_DISTANCE_CM)
//				{
//					motors_forward(0.5);
//					HAL_Delay(200);
//					stop_all_motors();
//					HAL_Delay(500);
//				}
//			}

			// ALL NEW BELOW


			if (distance_left_cm < TOO_CLOSE_DISTANCE_CM || distance_right_cm < TOO_CLOSE_DISTANCE_CM)
			{
				motors_backward(1);
				HAL_Delay(500);
				stop_all_motors();
				HAL_Delay(500);
			}

			float right_remainder_cm = distance_right_cm;
			while (right_remainder_cm > 18.0f)
			{
				right_remainder_cm -= 18.0f;
			}
			float left_remainder_cm = distance_left_cm;
			while (left_remainder_cm > 18.0f)
			{
				left_remainder_cm -= 18.0f;
			}


			float distance_difference_right_left_cm = right_remainder_cm - left_remainder_cm;
			int proposed_left_motor_mult = LEFT_MOTOR_MULT - distance_difference_right_left_cm * MOTOR_MULT_CHANGE_MULTIPLIER;
			// Subtract for the left motor multiplier because the left motor is actually the right one
			LEFT_MOTOR_MULT = proposed_left_motor_mult < LEFT_MOTOR_MULT_DEFAULT - MAX_MULT_CHANGE_RANGE ? LEFT_MOTOR_MULT : proposed_left_motor_mult;
			LEFT_MOTOR_MULT = proposed_left_motor_mult > LEFT_MOTOR_MULT_DEFAULT + MAX_MULT_CHANGE_RANGE ? LEFT_MOTOR_MULT : proposed_left_motor_mult;

			if (distance_left_cm < TOO_CLOSE_DISTANCE_CM || distance_right_cm < TOO_CLOSE_DISTANCE_CM)
			{
				if (distance_right_cm < TOO_CLOSE_DISTANCE_CM)
				{
					LEFT_MOTOR_MULT += 15;
				}
				else
				{
					LEFT_MOTOR_MULT -= 15;
				}
				motors_forward(1);
				HAL_Delay(500);
				stop_all_motors();
				HAL_Delay(500);
				if (distance_right_cm < TOO_CLOSE_DISTANCE_CM)
				{
					LEFT_MOTOR_MULT -= 15;
				}
				else
				{
					LEFT_MOTOR_MULT += 15;
				}
			}
			// ALL NEW ABOVE

			if(distance_left_cm < WALL_DISTANCE_CM)
			{
				maze.cell_grid[c.y][c.x].walls[(direction + 3) % 4] = Wall_Here;
				switch(direction)
				{
				case North:
					if(c.x + 1 < MAP_SIZE) maze.cell_grid[c.y][c.x + 1].walls[West] = Wall_Here;
					break;
				case East:
					if(c.y - 1 > -1) maze.cell_grid[c.y - 1][c.x].walls[North] = Wall_Here;
					break;
				case South:
					if(c.x - 1 > -1) maze.cell_grid[c.y][c.x - 1].walls[East] = Wall_Here;
					break;
				case West:
					if(c.y + 1 < MAP_SIZE) maze.cell_grid[c.y + 1][c.x].walls[South] = Wall_Here;
					break;
				case Unknown:
					break;
				}  // switch(direction)
			}  // if(is_there_wall_on_direction(Left))

			if (requested_manual_command != AUTON_CHAR) return 0;

			if(distance_front_cm < WALL_DISTANCE_CM)
			{
				maze.cell_grid[c.y][c.x].walls[direction] = Wall_Here;
				switch(direction)
				{
				case North:
					if(c.y + 1 < MAP_SIZE) maze.cell_grid[c.y + 1][c.x].walls[South] = Wall_Here;
					break;
				case East:
					if(c.x + 1 < MAP_SIZE) maze.cell_grid[c.y][c.x + 1].walls[West] = Wall_Here;
					break;
				case South:
					if(c.y - 1 > -1) maze.cell_grid[c.y - 1][c.x].walls[North] = Wall_Here;
					break;
				case West:
					if(c.x - 1 > -1) maze.cell_grid[c.y][c.x - 1].walls[East] = Wall_Here;
					break;
				case Unknown:
					break;
				}  // switch(direction)

			}  // if(is_there_wall_on_direction(Front))

			if (requested_manual_command != AUTON_CHAR) return 0;

			if(distance_right_cm < WALL_DISTANCE_CM)
			{
				maze.cell_grid[c.y][c.x].walls[(direction + 1) % 4] = Wall_Here;
				switch(direction)
				{
				case North:
					if(c.x - 1 > -1) maze.cell_grid[c.y][c.x - 1].walls[East] = Wall_Here;
					break;
				case East:
					if(c.y + 1 < MAP_SIZE) maze.cell_grid[c.y + 1][c.x].walls[South] = Wall_Here;
					break;
				case South:
					if(c.x + 1 < MAP_SIZE) maze.cell_grid[c.y][c.x + 1].walls[West] = Wall_Here;
					break;
				case West:
					if(c.y - 1 > -1) maze.cell_grid[c.y - 1][c.x].walls[North] = Wall_Here;
					break;
				case Unknown:
					break;
				}  // switch(direction)

			}  // if(is_there_wall_on_direction(Right))

			if (requested_manual_command != AUTON_CHAR) return 0;

			maze.cell_grid[c.y][c.x].visited = 1;

		}  // if(!maze.cell_grid[c.y][c.x].visited)
		else
		{
			// Move in direction for visited cell
			go_forward_one_unit();

			printf("Currently at x=%i, y=%i facing direction=%i.\r\n", c.x, c.y, direction);
			char buf[20];
			sprintf((char *)buf, "@%i,%i,%i,,,,,,,,,,,,,", c.x, c.y, (uint8_t)direction);
			HAL_UART_Transmit(&huart6, buf, sizeof(buf), 1000);

			print_maze(&maze, c, direction);
		}

		// DONE TO MAKE SURE CORRECT ANGLE

		if(found_flood_fill_destination(c, &maze))
		{
			set_servo_angle(Front);

			printf("Currently at x=%i, y=%i facing direction=%i.\r\n", c.x, c.y, direction);
			char buf5[20];
			sprintf((char *)buf5, "@%i,%i,%i,,,,,,,,,,,,,", c.x, c.y, (uint8_t)direction);
			HAL_UART_Transmit(&huart6, buf5, sizeof(buf5), 1000);

			printf("Completed maze!\r\n");
			char buf[20];
			memcpy(buf, "&COMPLETED,,,,,,,,,", 20);
			HAL_UART_Transmit(&huart6, buf, sizeof(buf), 1000);
			return 1;
		}  // if(found_flood_fill_destination(&c, &maze))


		// need to figure next direction to go to and also update rest of distance grid.
		desired_direction = minus_one_neighbor(&maze, c, &stack);

		if(desired_direction == Unknown)
		{
			while(!stack_is_empty(&stack))
			{
				if (stack.index >= 60)
				{
					char buf3[20];
					sprintf((char *)buf3, "&FAILED,,,,,,,,,,,,");
					HAL_UART_Transmit(&huart6, buf3, sizeof(buf3), 1000);
					return 0;
				}  // if (stack.index >= 100)
				if (requested_manual_command != AUTON_CHAR) return 0;
				// get the cell to test from the stack
				next_coordinate = pop_stack(&stack);
				// find a neighbor cell with distance one less than current
				minus_one_neighbor(&maze, next_coordinate, &stack);
			}  // while(stack.index != 0)
			// next_direction is the direction to go to next
			desired_direction = minus_one_neighbor(&maze, c, &stack);
		}  // if(next_direction == Unknown)
		int difference = desired_direction - direction + 4;
		char buf2[20];
		sprintf((char *)buf2, "^%i,%i,%i,,,,,,,,,,,,,", direction, desired_direction, difference % 4);
		HAL_UART_Transmit(&huart6, buf2, sizeof(buf2), 1000);
		switch(difference % 4)
		{
		case 0:
			break;
		case 1:
			rotate_direction_90(Right);
			break;
		case 2:
			rotate_180_degrees();
			break;
		case 3:
			rotate_direction_90(Left);
			break;
		}

		direction = desired_direction;

	}  // while(1)
}  // do_hug_left_algorithm()

uint8_t stack_is_empty(stack *s)
{
	return s->index == 0;
}

coordinate pop_stack(stack *s)
{
	s->index = s->index - 1;
	return s->coordinates[s->index + 1];
}  // void pop_stack(Stack* s)

void push_stack(stack* s, coordinate c)
{
	s->index = s->index + 1;
	s->coordinates[s->index] = c;
}  // void push_stack(Stack* s, uint8_t x, uint8_t y)

uint8_t found_flood_fill_destination(coordinate c, flood_fill_maze *maze)
{
	return maze->distance_grid[c.y][c.x] == 0;
}  // uint8_t found_flood_fill_destination(coordinate c, Flood_Fill_Maze *maze)

maze_direction minus_one_neighbor(flood_fill_maze *maze, coordinate c, stack *s)
{
	print_distance_grid(maze);

	/*
	 This functions returns the direction that leads to what it thinks will be
	 the fastest way to get to the solution. It does this by finding the direction
	 to the neighbor tile that has a distance that is 1 less than that of the current
	 tile.
	 */

	// TODO CHANGE WHEN BACK TO 16X16 MAZE
	/*
	uint16_t min_dist = MAP_SIZE * MAP_SIZE + 4;
	 */
	uint16_t min_dist = 20;

	// need to find target distance by looking through neighbors
	int16_t target = maze->distance_grid[c.y][c.x] - 1;
	for(uint8_t i = 0; i < 4; ++i)
	{
		if(maze->cell_grid[c.y][c.x].walls[i] == No_Wall_Here)
		{
			switch(i)
			{
			case North:
				if(maze->distance_grid[c.y+1][c.x] == target)
				{
					return i;
				}  // if(maze->distance_grid[c.y+1][c.x] == target)
				if(maze->distance_grid[c.y+1][c.x] < min_dist)
				{
					min_dist = maze->distance_grid[c.y+1][c.x];
				}  // if(maze->distance_grid[c.y+1][c.x] < min_dist)
				break;
			case East:
				if(maze->distance_grid[c.y][c.x+1] == target)
				{
					return i;
				}  // if(maze->distance_grid[c.y][c.x+1] == target)
				if(maze->distance_grid[c.y][c.x+1] < min_dist)
				{
					min_dist = maze->distance_grid[c.y][c.x+1];
				}  // if(maze->distance_grid[c.y][c.x+1] < min_dist)
				break;
			case South:
				if(maze->distance_grid[c.y-1][c.x] == target)
				{
					return i;
				}  // if(maze->distance_grid[c.y-1][c.x] == target)
				if(maze->distance_grid[c.y-1][c.x] < min_dist)
				{
					min_dist = maze->distance_grid[c.y-1][c.x];
				}  // if(maze->distance_grid[c.y-1][c.x] < min_dist)
				break;
			case West:
				if(maze->distance_grid[c.y][c.x-1] == target)
				{
					return i;
				}  // if(maze->distance_grid[c.y][c.x-1] == target)
				if(maze->distance_grid[c.y][c.x-1] < min_dist)
				{
					min_dist = maze->distance_grid[c.y][c.x-1];
				}  // if(maze->distance_grid[c.y][c.x-1] < min_dist)
				break;
			case Unknown:
				break;
			}  // switch(i)
		}  // if(maze->cell_grid[c.y][c.x].walls[i] == No_Wall_Here)
	}  // for(uint8_t i = 0; i < 4; ++i)

	// update distance of coordinate to 1 plus minimum distance
	maze->distance_grid[c.y][c.x] = min_dist + 1;

	// Since we did not find a cell we push onto the stack
	for(uint8_t i = 0; i < 4; ++i)
	{
		if(maze->cell_grid[c.y][c.x].walls[i] == No_Wall_Here)
		{
			coordinate temp;
			switch(i)
			{
			case North:
				init_coordinate(&temp, c.x, c.y + 1);
				break;
			case East:
				init_coordinate(&temp, c.x + 1, c.y);
				break;
			case South:
				init_coordinate(&temp, c.x, c.y - 1);
				break;
			case West:
				init_coordinate(&temp, c.x - 1, c.y);
				break;
			}  // switch(i)
			push_stack(s, temp);
		}  // if(maze->cell_grid[c.y][c.x].walls[i] == No_Wall_Here)
	}  // for(uint8_t i = 0; i < 4; ++i)
	// return unknown
	return Unknown;
}

void init_coordinate(coordinate *c, uint8_t x, uint8_t y)
{
	c->x = x;
	c->y = y;
}  // void init_coor(coordinate c, uint8_t x, uint8_t y)

void print_maze(flood_fill_maze *maze, coordinate c, maze_direction direction)
{
	printf("Printing maze grid. \r\n");
	char maze_map[MAP_SIZE][MAP_SIZE];

	for (uint8_t i = 0; i < MAP_SIZE; ++i)
	{
		for (uint8_t j = 0; j < MAP_SIZE; ++j)
		{
			uint8_t number = maze->cell_grid[i][j].walls[North];
			number |= maze->cell_grid[i][j].walls[East] << 1;
			number |= maze->cell_grid[i][j].walls[South] << 2;
			number |= maze->cell_grid[i][j].walls[West] << 3;
			maze_map[i][j] = 'a' + number;
		}  // for (uint8_t j = 0; j < MAP_SIZE; ++j)
	}  // for (uint8_t i = 0; i < MAP_SIZE; ++i)

	switch(direction)
	{
	case North:
		maze_map[c.y][c.x] = 'N';
		break;
	case East:
		maze_map[c.y][c.x] = 'E';
		break;
	case South:
		maze_map[c.y][c.x] = 'S';
		break;
	case West:
		maze_map[c.y][c.x] = 'W';
		break;
	case Unknown:
		break;
	}  // switch(i)

	for (int8_t i = MAP_SIZE - 1; i >= 0; --i)
	{
		for (uint8_t j = 0; j < MAP_SIZE; ++j)
		{
			printf("%c", maze_map[i][j]);
		}  // for (uint8_t j = 0; j < MAP_SIZE; ++j)

		printf("\r\n");
	}  // for (int8_t i = MAP_SIZE - 1; i >= 0; --i)
}  // void print_maze(flood_fill_maze *m, coordinate c)

void print_distance_grid(flood_fill_maze *maze)
{

	printf("Printing distance grid. \r\n");

	for (int8_t i = MAP_SIZE - 1; i >= 0; --i)
	{
		for (uint8_t j = 0; j < MAP_SIZE; ++j)
		{
			printf("%c", 'a' + maze->distance_grid[i][j]);
		}  // for (uint8_t j = 0; j < MAP_SIZE; ++j)
		printf("\r\n");
	}  // for (int8_t i = MAP_SIZE - 1; i >= 0; --i)
}  // void print_distance_grid(flood_fill_maze *maze)
