#include "search.h"
#include "structure.h"
#include "format.h"
#include "file_handling.h"
#include "print.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// funkcja dostaje wierzchołek i zapisuje na początek pliku jego poprzednika
int* vertice_to_ancestor(int* vertice , FILE* IN , FILE* OUT){ // vertice[0] -> wiersz , vertice[1] -> kolumna
	int* key = vertice;
	int* input = malloc(sizeof(int)*2);
	int* ancestor = malloc(sizeof(int)*2);
	while((input[0] == key[0] && input[1] == key[1]) == 0){
		fscanf(IN,"%d %d %d %d",&ancestor[0],&ancestor[1],&input[0],&input[1]);
	}
	fseek(OUT,0,SEEK_SET);
	fprintf(OUT,"%d %d\n",ancestor[0],ancestor[1]);
	free(key);
	free(input);
	return ancestor;
}

void convert_output(int* start_end){
	
	FILE* A = fopen("ancestors.txt","r");
	FILE* O = fopen("path.txt","w");
	int* start = malloc(sizeof(int)*2);
	int* finish = malloc(sizeof(int)*2);
	start[0] = start_end[0];
	start[1] = start_end[1];
	finish[0] = start_end[2];
	finish[1] = start_end[3];
	int* loaded = malloc(sizeof(int)*2);
	while((loaded[0] == start[0] && loaded[1] == start[1]) == 0){
		loaded = vertice_to_ancestor(finish, A , O);
		finish = loaded;
	}
	free(finish);
	free(start);
}

