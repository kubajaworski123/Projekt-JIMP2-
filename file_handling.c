#include "file_handling.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int* maze_dim(FILE* F){
	fseek(F,0,SEEK_SET);
	int* dim = malloc(2*sizeof(int));
	dim[0] = 0;
	dim[1] = 0;
	char* buf = malloc(2050*sizeof(char));
	while(fgets(buf , 2050 , F) != 0){
		dim[0]++;
		dim[1] = strlen(buf) - 1;
	}
	dim[0] --;
	dim[1] --;
	free(buf);
	return dim;
}


void add_visited (FILE *F , int row , int col){
	char* s = malloc(11);
	sprintf(s,"%04d %04d ", row , col);
	fprintf(F,"%s",s);
	free(s);
}

int is_visited (FILE* F , int row , int col){
	char* key = malloc(11);
	char* str = malloc(11);
	sprintf(key,"%04d %04d ", row , col);
	fseek(F , 0 , SEEK_SET);
	while(fgets(str,11,F) != NULL){
		if(strncmp(str,key,10) == 0){
		free(key);
		free(str);
	return 1;
	}
	}
	return 0;
}

void add_ancestors (FILE* F , int row , int col , int A_row , int A_col){
	char* buf = malloc(64);
	sprintf(buf,"%04d %04d %04d %04d\n", row , col , A_row , A_col);
	fprintf(F,"%s", buf);
	free(buf);
}

void add_to_queue(FILE* F , int row , int col){
	fprintf(F , "%d %d\n" , row , col);	
}

int* pop_queue(FILE* F, long line_nr){
	fseek(F , 0 , SEEK_SET);
	for(int i = 0 ; i < line_nr ; i++){
		while(fgetc(F)!=10);// ASCI 10 to \n
	}
	int* pair = malloc(sizeof(int)*2);
	fscanf(F,"%d %d",&pair[0], &pair[1]);
	fgetc(F);
	return pair;
}
