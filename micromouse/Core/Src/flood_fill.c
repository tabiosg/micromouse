#include "flood_fill.h"

void do_flood_fill_algorithm()
{
	// Initialize the maze
	Flood_Fill_Maze maze;

	for (uint8_t i = 0; i < 16; ++i)
	{
		for (uint8_t j = 0; j < 16; ++j)
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

			if(i == 0) maze.cell_grid[i][j].walls[West] = Wall_Here;
			if(j == 0) maze.cell_grid[i][j].walls[South] = Wall_Here;
			if(i == 15) maze.cell_grid[i][j].walls[East] = Wall_Here;
			if(j == 15) maze.cell_grid[i][j].walls[North] = Wall_Here;

		}  // for (uint8_t j = 0; j < 16; ++j)
	}  // for (uint8_t i = 0; i < 16; ++i)

	// Do flood fill algorithm

	Maze_Direction desired_direction = North;  // the direction that we want to move in next
	Maze_Direction direction = desired_direction;  // the direction we're currently facing
	Coordinate next_coordinate;
	init_coordinate(&next_coordinate, 0, 0);

	Coordinate c = next_coordinate;  // c is the coordinate that we want to be in

	Stack stack;

	while(1)
	{
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

		// Go forward one cell
		go_forward_one_unit();
		// visiting_coord should now be the coordinate that we're on.

		if(!maze.cell_grid[c.x][c.y].visited)
		{
			if(is_there_wall_on_direction(Left))
			{
				maze.cell_grid[c.x][c.y].walls[(direction - 1) % 4] = Wall_Here;
				switch(direction)
				{
				case North:
					if(c.x + 1 < 16) maze.cell_grid[c.x + 1][c.y].walls[West] = Wall_Here;
					break;
				case East:
					if(c.y - 1 > -1) maze.cell_grid[c.x][c.y - 1].walls[North] = Wall_Here;
					break;
				case South:
					if(c.x - 1 > -1) maze.cell_grid[c.x - 1][c.y].walls[East] = Wall_Here;
					break;
				case West:
					if(c.y + 1 < 16) maze.cell_grid[c.x][c.y + 1].walls[South] = Wall_Here;
					break;
				case Unknown:
					break;
				}  // switch(direction)
			}  // if(is_there_wall_on_direction(Left))
			else if(is_there_wall_on_direction(Front))
			{
				maze.cell_grid[c.x][c.y].walls[direction] = Wall_Here;
				switch(direction)
				{
				case North:
					if(c.y + 1 < 16) maze.cell_grid[c.x][c.y + 1].walls[South] = Wall_Here;
					break;
				case East:
					if(c.x + 1 < 16) maze.cell_grid[c.x + 1][c.y].walls[West] = Wall_Here;
					break;
				case South:
					if(c.y - 1 > -1) maze.cell_grid[c.x][c.y - 1].walls[North] = Wall_Here;
					break;
				case West:
					if(c.x - 1 > -1) maze.cell_grid[c.x - 1][c.y].walls[East] = Wall_Here;
					break;
				case Unknown:
					break;
				}  // switch(direction)

			}  // else if(is_there_wall_on_direction(Front))
			else if(is_there_wall_on_direction(Right))
			{
				maze.cell_grid[c.x][c.y].walls[(direction + 1) % 4] = Wall_Here;
				switch(direction)
				{
				case North:
					if(c.x - 1 > -1) maze.cell_grid[c.x - 1][c.y].walls[East] = Wall_Here;
					break;
				case East:
					if(c.y + 1 < 16) maze.cell_grid[c.x][c.y + 1].walls[South] = Wall_Here;
					break;
				case South:
					if(c.x + 1 < 16) maze.cell_grid[c.x + 1][c.y].walls[West] = Wall_Here;
					break;
				case West:
					if(c.y - 1 > -1) maze.cell_grid[c.x][c.y - 1].walls[North] = Wall_Here;
					break;
				case Unknown:
					break;
				}  // switch(direction)

			}  // if(is_there_wall_on_direction(Right))


			maze.cell_grid[c.x][c.y].visited = 1;

		}  // else if(!maze.cell_grid[c.x][c.y].visited)

		if(found_flood_fill_destination(&c, &maze))
		{
			return;
		}  // if(found_flood_fill_destination(&c, &maze))


		// need to figure next direction to go to and also update rest of distance grid.
		desired_direction = minus_one_neighbor(&maze, &c, &stack);

		if(desired_direction == Unknown)
		{
			while(!stack_is_empty(&stack))
			{
				// get the cell to test from the stack
				next_coordinate = pop_stack(&stack);
				// find a neighbor cell with distance one less than current
				minus_one_neighbor(&maze, &next_coordinate, &stack);
			}  // while(stack.index != 0)
			// next_direction is the direction to go to next
			desired_direction = minus_one_neighbor(&maze, &c, &stack);
		}  // if(next_direction == Unknown)

		int difference = direction - desired_direction;
		switch(difference % 4)
		{
		case 0:
			break;
		case 1:
			rotate_direction(Left);
			// TODO - might need to calibrate
			break;
		case 2:
			rotate_180_degrees();
			// TODO - might need to calibrate
			break;
		case 3:
			rotate_direction(Right);
			// TODO - might need to calibrate
			break;
		}

		direction = desired_direction;

	}  // while(1)
}  // do_hug_left_algorithm()

uint8_t stack_is_empty(Stack *s)
{
	return s->index == 0;
}

Coordinate pop_stack(Stack *s)
{
	s->index = s->index - 1;
	return s->coordinates[s->index + 1];
}  // void pop_stack(Stack* s)

void push_stack(Stack* s, Coordinate *c)
{
	s->index = s->index + 1;
	s->coordinates[s->index] = *c;
}  // void push_stack(Stack* s, uint8_t x, uint8_t y)

void move_forward_and_update(Maze_Direction d, Coordinate *c, Flood_Fill_Maze *m)
{
	switch(d)
	{
	case North:
		m->cell_grid[c->x][c->y].walls[West] = Wall_Here;
		m->cell_grid[c->x][c->y].walls[East] = Wall_Here;
		if(c->x > 0) m->cell_grid[c->x - 1][c->y].walls[East] = Wall_Here;
		if(c->x < 15) m->cell_grid[c->x + 1][c->y].walls[West] = Wall_Here;
		break;
	case East:
		m->cell_grid[c->x][c->y].walls[North] = Wall_Here;
		m->cell_grid[c->x][c->y].walls[South] = Wall_Here;
		if(c->y > 0) m->cell_grid[c->x][c->y - 1].walls[North] = Wall_Here;
		if(c->y < 15) m->cell_grid[c->x][c->y + 1].walls[South] = Wall_Here;
		break;
	case South:
		m->cell_grid[c->x][c->y].walls[West] = Wall_Here;
		m->cell_grid[c->x][c->y].walls[East] = Wall_Here;
		if(c->x > 0) m->cell_grid[c->x - 1][c->y].walls[East] = Wall_Here;
		if(c->x < 15) m->cell_grid[c->x + 1][c->y].walls[West] = Wall_Here;
		break;
	case West:
		m->cell_grid[c->x][c->y].walls[North] = Wall_Here;
		m->cell_grid[c->x][c->y].walls[South] = Wall_Here;
		if(c->y > 0) m->cell_grid[c->x][c->y - 1].walls[North] = Wall_Here;
		if(c->y < 15) m->cell_grid[c->x][c->y + 1].walls[South] = Wall_Here;
		break;
	case Unknown:
		break;
	}  // switch(d)
}  // void move_forward_and_update(Maze_Direction d, Coordinate *c, Flood_Fill_Maze *m)

uint8_t found_flood_fill_destination(Coordinate *c, Flood_Fill_Maze *maze)
{
	return maze->distance_grid[c->x][c->y] == 0;
}  // uint8_t found_flood_fill_destination(Coordinate *c, Flood_Fill_Maze *maze)

Maze_Direction minus_one_neighbor(Flood_Fill_Maze *maze, Coordinate *c, Stack *s)
{
	/*
	 This functions returns the direction that leads to what it thinks will be
	 the fastest way to get to the solution. It does this by finding the direction
	 to the neighbor tile that has a distance that is 1 less than that of the current
	 tile.
	 */

	uint16_t min_dist = 260;

	// need to find target distance by looking through neighbors
	int16_t target = maze->distance_grid[c->x][c->y] - 1;
	for(uint8_t i = 0; i < 4; ++i)
	{
		if(maze->cell_grid[c->x][c->y].walls[i] == No_Wall_Here)
		{
			switch(i)
			{
			case North:
				if(maze->distance_grid[c->x][c->y + 1] == target)
				{
					return i;
				}  // if(maze->distance_grid[c->x][c->y + 1] == target)
				if(maze->distance_grid[c->x][c->y + 1] < min_dist)
				{
					min_dist = maze->distance_grid[c->x][c->y + 1];
				}  // if(maze->distance_grid[c->x][c->y + 1] < min_dist)
				break;
			case East:
				if(maze->distance_grid[c->x + 1][c->y] == target)
				{
					return i;
				}  // if(maze->distance_grid[c->x + 1][c->y] == target)
				if(maze->distance_grid[c->x + 1][c->y] < min_dist)
				{
					min_dist = maze->distance_grid[c->x + 1][c->y];
				}  // if(maze->distance_grid[c->x + 1][c->y] < min_dist)
				break;
			case South:
				if(maze->distance_grid[c->x][c->y-1] == target)
				{
					return i;
				}  // if(maze->distance_grid[c->x][c->y-1] == target)
				if(maze->distance_grid[c->x][c->y-1] < min_dist)
				{
					min_dist = maze->distance_grid[c->x][c->y-1];
				}  // if(maze->distance_grid[c->x][c->y-1] < min_dist)
				break;
			case West:
				if(maze->distance_grid[c->x-1][c->y] == target)
				{
					return i;
				}  // if(maze->distance_grid[c->x-1][c->y] == target)
				if(maze->distance_grid[c->x-1][c->y] < min_dist)
				{
					min_dist = maze->distance_grid[c->x-1][c->y];
				}  // if(maze->distance_grid[c->x-1][c->y] < min_dist)
				break;
			case Unknown:
				break;
			}  // switch(i)
		}  // if(maze->cell_grid[c->x][c->y].walls[i] == No_Wall_Here)
	}  // for(uint8_t i = 0; i < 4; ++i)

	// update distance of coordinate to 1 plus minimum distance
	maze->distance_grid[c->x][c->y] = min_dist + 1;

	// Since we did not find a cell we push onto the stack
	for(uint8_t i = 0; i < 4; ++i)
	{
		if(maze->cell_grid[c->x][c->y].walls[i] == No_Wall_Here)
		{
			Coordinate temp;
			switch(i)
			{
			case North:
				init_coordinate(&temp, c->x, c->y + 1);
				break;
			case East:
				init_coordinate(&temp, c->x + 1, c->y);
				break;
			case South:
				init_coordinate(&temp, c->x, c->y - 1);
				break;
			case West:
				init_coordinate(&temp, c->x - 1, c->y);
				break;
			}  // switch(i)
			push_stack(s, &temp);
		}  // if(maze->cell_grid[c->x][c->y].walls[i] == No_Wall_Here)
	}  // for(uint8_t i = 0; i < 4; ++i)
	// return unknown
	return Unknown;
}

void init_coordinate(Coordinate *c, uint8_t x, uint8_t y)
{
	c->x = x;
	c->y = y;
}  // void init_coor(Coordinate *c, uint8_t x, uint8_t y)
