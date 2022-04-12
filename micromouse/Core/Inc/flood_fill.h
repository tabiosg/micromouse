#ifndef INC_FLOOD_FILL_H_
#define INC_FLOOD_FILL_H_

#include <wall_sensor.h>
#include "stdint.h"
#include "stdio.h"
#include "manual_control.h"
#include "mouse.h"

#define MAP_SIZE 16

typedef enum
{
	North, East, South, West, Unknown
} maze_direction;

typedef enum
{
	No_Wall_Here, Wall_Here
} wall_bool;

typedef enum
{
	Is_Not_Visited, Is_Visited
} visited_bool;

typedef struct
{
	uint8_t walls[4];
	uint8_t visited;
} cell;

typedef struct
{
	cell cell_grid[MAP_SIZE][MAP_SIZE];
	uint8_t distance_grid[MAP_SIZE][MAP_SIZE];
} flood_fill_maze;

typedef struct
{
	uint8_t x;
	uint8_t y;
} coordinate;

typedef struct
{
	coordinate coordinates[MAP_SIZE * MAP_SIZE];
	uint8_t index;
} stack;

uint8_t do_flood_fill_algorithm();

uint8_t stack_is_empty(stack *s);

coordinate pop_stack(stack *s);

void push_stack(stack *s, coordinate c);

void move_forward_and_update(maze_direction d, coordinate c, flood_fill_maze *m);

maze_direction minus_one_neighbor(flood_fill_maze *maze, coordinate c, stack *s);

uint8_t found_flood_fill_destination(coordinate c, flood_fill_maze *maze);

void init_coordinate(coordinate *c, uint8_t x, uint8_t y);

void print_maze(flood_fill_maze *maze, coordinate c, maze_direction direction);

void print_distance_grid(flood_fill_maze *maze);

#endif /* INC_FLOOD_FILL_H_ */
