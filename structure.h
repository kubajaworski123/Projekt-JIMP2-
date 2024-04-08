#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdint.h>
typedef struct {
	uint8_t ** right;
	uint8_t ** bottom;
	int r,c;
	int* start;
	int* finish;
} *Maze;

void maze_init(Maze maze);
void maze_free(Maze maze);

#endif
