#ifndef INC_FLOOD_FILL_H_
#define INC_FLOOD_FILL_H_

#include <wall_sensor.h>
#include "stdint.h"
#include "mouse.h"

typedef enum
{
	North, East, South, West, Unknown
} Maze_Direction;

typedef enum
{
	No_Wall_Here, Wall_Here
} Wall_Bool;

typedef enum
{
	Is_Not_Visited, Is_Visited
} Visited_Bool;

typedef struct
{
	uint8_t walls[4];
	uint8_t visited;
} Cell;

typedef struct
{
	Cell cell_grid[16][16];
	uint8_t distance_grid[16][16];
} Flood_Fill_Maze;

typedef struct
{
	uint8_t x;
	uint8_t y;
} Coordinate;

typedef struct
{
	Coordinate coordinates[256];
	uint8_t index;
} Stack;

void do_floodfill_algorithm();

uint8_t stack_is_empty(Stack *s);

Coordinate pop_stack(Stack *s);

void push_stack(Stack *s, Coordinate *c);

void move_forward_and_update(Maze_Direction d, Coordinate *c, Flood_Fill_Maze *m);

Maze_Direction minus_one_neighbor(Flood_Fill_Maze *maze, Coordinate *c, Stack *s);

uint8_t found_flood_fill_destination(Coordinate *c, Flood_Fill_Maze *maze);

void init_coordinate(Coordinate *c, uint8_t x, uint8_t y);

#endif /* INC_FLOOD_FILL_H_ */
