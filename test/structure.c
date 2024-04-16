#include "structure.h"
#include <stdint.h>
#include <stdlib.h>

// Funkcja maze_init alokuje pamięć na nową strukturę labiryntu,
// natomiast funkcja maze_free ją zwalnia.

void maze_init(Maze maze){
        int i;
        maze->right = malloc(1024*128*sizeof(uint8_t));
        for (i=0; i<1024; i++)
                maze->right[i]=malloc(128*sizeof(uint8_t));
        maze->bottom = malloc(1024*128*sizeof(uint8_t));
        for (i=0; i<1024; i++)
                maze->bottom[i]=malloc(128*sizeof(uint8_t));
        maze->start = malloc(2*sizeof(int));
        maze->finish = malloc(2*sizeof(int));
}

void maze_free(Maze maze){
        free(maze->right);
        free(maze->bottom);
        free(maze->start);
        free(maze->finish);
	free(maze);
}
