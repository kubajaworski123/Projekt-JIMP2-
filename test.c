#include "read_txt.h"
#include "structure.h"
#include "format.h"
#include "file_handling.h"
#include "search.h"
#include "print.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char**argv){

	FILE* F = fopen(argv[1],"r");
	Maze maze = malloc(sizeof(*maze));
	maze_init(maze);
	read_txt(F,maze);
	int* start_end = malloc(sizeof(int)*4);
	start_end = solve_maze(maze,F);
	FILE* O = fopen("wwwwwwwwwyjscie.txt" , "w");
	FILE* A = fopen("ancestors.txt" , "r");
	int* para = malloc(sizeof(int)*2);
	int* para2 = malloc(sizeof(int)*2);
	para[0] = 3;
	para[1] = 2;
	para2[0] = 2;
	para2[1] = 2;
	vertice_to_ancestor(para , A , O);
	vertice_to_ancestor(para2 , A , O);
	convert_output(start_end);
	return 0;
	
}


