#include "search.h"
#include "structure.h"
#include "format.h"
#include "file_handling.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int* solve_maze (Maze maze , FILE* F){ // funkcja zwraca początek i koniec labiryntu
	
	long qln = 0; // qln - queue line numerator
	FILE* V = fopen("visited.txt","a+");
	FILE* A = fopen("ancestors.txt","a+");
	FILE* Q = fopen("queue.txt","a+");
	
	//przypisanie wartości pierwszego elementu
	if(maze->start[0] == 0){ // wejście od góry
		add_visited(V , maze->start[0] , (maze->start[1]-1)/2);
		add_to_queue(Q , maze->start[0] , (maze->start[1]-1)/2);
		printf("start: %d %d\n" , maze->start[0] , (maze->start[1]-1)/2);
	}
	if(maze->start[1] == 0){ // wejście od boku (i na ukos)
		add_visited(V , (maze->start[0]-1)/2 , maze->start[1]);
		add_to_queue(Q , (maze->start[0]-1)/2 , maze->start[1]);
		printf("start: %d %d\n" , (maze->start[0]-1)/2 , maze->start[1]);
	}
	int* output = malloc(sizeof(int)*4);
	int* end = malloc(sizeof(int)*2);
	int* dim = maze_dim(F);

	// przypisanie wartości ostatniego elementu
	if(dim[0] == maze->finish[0]){
		end[0] = (maze->finish[0] - 1)/2;
        	end[1] = maze->finish[1]/2;	
	}else if(dim[1] == maze->finish[1]){
		end[0] = maze->finish[0]/2;
		end[1] = (maze->finish[1]-1)/2;
	 }
	output[0] = (maze->start[0]-1)/2;
	output[1] = maze->start[1];
	output[2] = end[0];
	output[3] = end[1];

	printf("end: %d %d \n" , end[0] , end[1]);

	int* current = malloc(sizeof(int)*2);	
	while((current[0] == end[0] && current[1] == end[1]) == 0){
		current = pop_queue(Q , qln);
		printf("current: %d %d\n", current[0] , current[1]);
		fflush(stdout);
		qln++;
		if(right_exists(maze->right , current[0] , current[1]) == 0){ //dodajemy komórkę na prawo o ile jest ona dostępna
			if(is_visited(V , current[0] , current[1]+1) == 0){
				add_to_queue(Q , current[0] , current[1]+1);
				add_visited(V , current[0],current[1]+1);
				add_ancestors(A , current[0] ,current[1] , current[0] , current[1]+1);
			}
		}
		if(bottom_exists(maze->bottom , current[0] , current[1]) == 0){ // dodajemy komórkę na dole o ile jest ona dostępna
			if(is_visited(V , current[0]+1 , current[1]) == 0){
                                add_to_queue(Q , current[0]+1 , current[1]);
                                add_visited(V , current[0]+1,current[1]);
                                add_ancestors(A , current[0] ,current[1] , current[0]+1 , current[1]);
                        }
		}
		if(current[1]!= 0){ // dodajemy komórkę na lewo o ile jest dostępna
			if(right_exists(maze->right , current[0] , current[1]-1) == 0){
				if(is_visited(V , current[0] , current[1]-1) == 0){
                                	add_to_queue(Q , current[0] , current[1]-1);
                                	add_visited(V , current[0],current[1]-1);
                                	add_ancestors(A , current[0] ,current[1] , current[0] , current[1]-1);
                        	}
			}
		}
		if(current[0] != 0){ // dodajemy komórkę na górze o ile jest dostępna
			if(bottom_exists(maze->bottom , current[0]-1 , current[1]) == 0){
				if(is_visited(V , current[0]-1 , current[1]) == 0){
                                	add_to_queue(Q , current[0]-1 , current[1]);
                                	add_visited(V , current[0]-1,current[1]);
                                	add_ancestors(A , current[0] ,current[1] , current[0]-1 , current[1]);
                        	}
			}
		}
	}
	remove("visited.txt");
	remove("queue.txt");
	fclose(A);
	fclose(V);
	fclose(Q);
	return output;
}


