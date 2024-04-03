#include "structure.h"
#include <stdint.h>

// Funkcja maze_init alokuje pamięć na nową strukturę labiryntu,
// natomiast funkcja maze_free ją zwalnia.

void maze_init(Maze maze){
	maze.right = malloc(128*128*sizeof(uint8_t));
	maze.bottom = malloc(128*128*sizeof(uint8_t));
	maze.start = malloc(2*sizeof(int));
	maze.finish = malloc(2*sizeof(int));
}

void maze_free(Maze maze){
	free(maze.right);
	free(maze.bottom);
	free(maze.start);
	free(maze.finish);
}
