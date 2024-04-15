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
	
	fseek(IN , 0 , SEEK_SET);
	int* key = vertice;
	int* input = malloc(sizeof(int)*2);
	int* ancestor = malloc(sizeof(int)*2);
	while((input[0] == key[0] && input[1] == key[1]) == 0){
		fscanf(IN,"%d %d %d %d",&ancestor[0],&ancestor[1],&input[0],&input[1]);
	}
	fseek(OUT,0,SEEK_SET);
	fprintf(OUT,"%04d %04d\n",ancestor[0],ancestor[1]);
	free(key);
	free(input);
	return ancestor;
}

long convert_output(int* start_end){
	
	FILE* A = fopen("ancestors.txt","r");
	FILE* O = fopen("path.txt","a+");
	int* start = malloc(sizeof(int)*2);
	int* finish = malloc(sizeof(int)*2);
	start[0] = start_end[0];
	start[1] = start_end[1];
	finish[0] = start_end[2];
	finish[1] = start_end[3];
	long i = 1;
	i++;
	fprintf(O,"%04d %04d\n", finish[0] , finish[1]);
	int* para = vertice_to_ancestor(finish , A , O);
	while((para[0] == start[0] && para[1] == start[1]) == 0){
		para = vertice_to_ancestor(para , A , O);
		i++;
	}
	free(finish);
	free(start);
	fclose(A);
	fclose(O);
	return i;
}

void reverse_output(long lines){
	FILE* P = fopen("path.txt" , "r");
	FILE* N = fopen("new_path.txt" , "a+");
	char* buff = malloc(32);
	for(int j = lines-1 ; j >= 0 ; j--){
		for(int i = 0 ; i < j ; i++){
			fgets(buff , 32 , P);
		}
		fgets(buff , 32 , P);
		fprintf(N ,"%s",buff);
		fseek(P , 0 , SEEK_SET);
	}
	fclose(P);
	fclose(N);
	free(buff);	
}

void steps(long lines){
	FILE* N = fopen("new_path.txt","r");
	int x1 ,y1 , x2 , y2;
	printf("POCZĄTEK\n");
	fscanf(N,"%d %d",&x1,&y1);
	fgetc(N);
	for(int i = 1 ; i < lines ; i++){
		fscanf(N,"%d %d",&x2,&y2);
		fgetc(N);
		if(x1 == x2 && y1 > y2){
			printf("KROK W LEWO\n");
		}else if(x1 == x2 && y1 < y2){
			printf("KROK W PRAWO\n");
		}else if(x1 < x2 && y1 == y2){
			printf("KROK W DÓŁ\n");
		}else if(x1 > x2 && y1 == y2){
			printf("KROK W GÓRĘ\n");
		}
		x1 = x2;
		y1 = y2;
	}
	printf("KONIEC\n");
}

