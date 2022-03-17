#ifndef INC_FLOOD_FILL_H_
#define INC_FLOOD_FILL_H_

#include <wall_sensor.h>
#include "stdint.h"
#include "mouse.h"

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
	cell cell_grid[16][16];
	uint8_t distance_grid[16][16];
} flood_fill_maze;

typedef struct
{
	uint8_t x;
	uint8_t y;
} coordinate;

typedef struct
{
	coordinate coordinates[256];
	uint8_t index;
} stack;

void do_flood_fill_algorithm();

uint8_t stack_is_empty(stack *s);

coordinate pop_stack(stack *s);

void push_stack(stack *s, coordinate *c);

void move_forward_and_update(maze_direction d, coordinate *c, flood_fill_maze *m);

maze_direction minus_one_neighbor(flood_fill_maze *maze, coordinate *c, stack *s);

uint8_t found_flood_fill_destination(coordinate *c, flood_fill_maze *maze);

void init_coordinate(coordinate *c, uint8_t x, uint8_t y);

#endif /* INC_FLOOD_FILL_H_ */
