#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "structure.h"
#include "format.h"

typedef struct {
	uint32_t file_id;
	uint8_t escape;
	uint16_t columns;
	uint16_t lines;
	uint16_t entry_x;
	uint16_t entry_y;
	uint16_t exit_x;
	uint16_t exit_y;
	uint32_t res1,res2,res3;
	uint32_t counter;
	uint32_t s_offset;
	uint8_t separator;
	uint8_t wall;
	uint8_t path;
} *Mazebin;
/*
int main(int argc, char**argv){
	int i;
	Maze maze = malloc(1024*256*sizeof(uint8_t)+4*sizeof(int));
	maze_init(maze);
*/

int read_binary(FILE *in, Maze maze){
	Mazebin mazebin = malloc(40);
	FILE *in = fopen(argv[1],"rb");
	char *buf = malloc(12);
	printf("Odczyt pliku binarnego:\n");
	//File ID:
	fread(buf,4,1,in);
	mazebin->file_id = 0;
	for (i=3; i>=0; i--)
		mazebin->file_id+=(int)pow(256,i)*buf[i];
	printf("File ID: 0x%x\n", mazebin->file_id);
	
	//Escape:
	fread(buf,1,1,in);
	mazebin->escape = buf[0];
	printf("Escape:  0x%x\n", mazebin->escape);
	
	//Columns:
	fread(buf,2,1,in);
	mazebin->columns = 0;
	for (i=1; i>=0; i--)
		mazebin->columns+=(int)pow(256,i)*buf[i];
	printf("Columns: 0x%x\n",mazebin->columns);

	//Lines:
	fread(buf,2,1,in);
	mazebin->lines = 0;
        for (i=1; i>=0; i--)
                mazebin->lines+=(int)pow(256,i)*buf[i];
        printf("Lines:   0x%x\n",mazebin->lines);

	//Entry X:
	fread(buf,2,1,in);
	mazebin->entry_x = 0;
        for (i=1; i>=0; i--)
                mazebin->entry_x+=(int)pow(256,i)*buf[i];
        printf("Entry X: 0x%x\n",mazebin->entry_x);
	if (mazebin->entry_x==1) maze->start[0] = 0;
	else maze->start[0] = mazebin->entry_x/2-1;

	//Entry Y:
	fread(buf,2,1,in);
        mazebin->entry_y = 0;
        for (i=1; i>=0; i--)
                mazebin->entry_y+=(int)pow(256,i)*buf[i];
        printf("Entry Y: 0x%x\n",mazebin->entry_y);
	if (mazebin->entry_y==1) maze->start[1] = 0;
	else maze->start[1] = mazebin->entry_y/2-1;

	//Exit X:
	fread(buf,2,1,in);
        mazebin->exit_x = 0;
        for (i=1; i>=0; i--)
                mazebin->exit_x+=(int)pow(256,i)*buf[i];
        printf("Exit X:  0x%x\n",mazebin->exit_x);
	if (mazebin->exit_x==mazebin->lines) maze->finish[0] = (mazebin->lines-1)/2-1;
	else maze->finish[0] = mazebin->exit_x/2-1;

	//Exit Y:
        fread(buf,2,1,in);
        mazebin->exit_y = 0;
        for (i=1; i>=0; i--)
                mazebin->exit_y+=(int)pow(256,i)*buf[i];
        printf("Exit Y:  0x%x\n",mazebin->exit_y);
	if (mazebin->exit_y==mazebin->columns) maze->finish[1] = (mazebin->columns-1)/2-1;
	else maze->finish[1] = mazebin->exit_y/2-1;

	//Reserved:
	fread(buf,4,1,in);
        mazebin->res1 = 0;
        for (i=3; i>=0; i--)
                mazebin->res1+=(int)pow(256,i)*buf[i];
	fread(buf,4,1,in);
	mazebin->res2 = 0;
	for (i=3; i>=0; i--)
		mazebin->res2+=(int)pow(256,i)*buf[i];
	fread(buf,4,1,in);
	mazebin->res3 = 0;
	for (i=3; i>=0; i--)
		mazebin->res3+=(int)pow(256,i)*buf[1];
        printf("Reserve: 0x%x%x%x\n", mazebin->res1, mazebin->res2, mazebin->res3);

	//Counter:
	fread(buf,4,1,in);
        mazebin->counter = 0;
        for (i=3; i>=0; i--)
                mazebin->counter+=(int)pow(256,i)*buf[i];
        printf("Counter: 0x%x\n", mazebin->counter);

	//Solution Offset:
	fread(buf,4,1,in);
        mazebin->s_offset = 0;
        for (i=3; i>=0; i--)
                mazebin->s_offset+=(int)pow(256,i)*buf[i];
        printf("SOffset: 0x%x\n", mazebin->s_offset);

	//Separator:
	fread(buf,1,1,in);
        mazebin->separator = buf[0];
        printf("Separat: 0x%x\n", mazebin->separator);

	//Wall:
	fread(buf,1,1,in);
        mazebin->wall = buf[0];
        printf("Wall:    0x%x\n", mazebin->wall);

	//Path:
	fread(buf,1,1,in);
	mazebin->path = buf[0];
	printf("Path:    0x%x\n", mazebin->path);

	//Odczyt właściwych danych:
	unsigned char value;
	unsigned char count;
	unsigned char c;
	int readno = 0;
	int curr_column = 0;
	int curr_row = 0;
	int mode = 2; // mode=0 - wczytano separator, mode=1 - value, mode=2 - count
	while (curr_row<mazebin->lines){
		c = fgetc(in);
		if (c==mazebin->separator && mode==2){
			mode = 0;
		}
		else if (mode==0){
			mode = 1;
			value = c;
		}
		else if (mode==1){
			mode = 2;
			count = c;
			printf("Odczyt nr %d:\n Value = 0x%x, Count = 0x%x\n",++readno,value,count);
			if (curr_row>0){
			    if (curr_row%2==1 && value==mazebin->wall){
				right_on(maze->right,(curr_row-1)/2,curr_column/2-1);
			    	if (count==0){
					curr_column++;
					if (curr_column==mazebin->columns){
						curr_column=0;
						curr_row++;
					}
				} else {
					curr_row++;
					curr_column=0;
					for (i=1; i<count+1; i++){
					    if (curr_column%2==1){
					    	bottom_on(maze->bottom,curr_row/2-1,(curr_column-1)/2);
					    }
					    curr_column++;
					}
				}
			    }
			    else if (curr_row%2==0 && value==mazebin->wall){
			        for (i=0; i<count+1; i++){
					if (curr_column%2==1){
					    bottom_on(maze->bottom,curr_row/2-1,(curr_column-1)/2);
					}
					else if (curr_column==mazebin->columns-1){
					    curr_row++;
					    curr_column=0;
					    break;
					}
					curr_column++;
				}
			    }
			    else if (value==mazebin->path){
			        for (i=0; i<count+1; i++){
					curr_column++;
					if (curr_column==mazebin->columns){
						curr_column=0;
						curr_row++;
					}
				}
			    }
			    else {
			    	fprintf("Błąd: niepoprawne słowo kodowe w pliku binarnym %s.\n",in);
				return -1;
			    }
			} else {
			    for (i=0; i<count+1; i++){
			    	curr_column++;
				if (curr_column==mazebin->columns){
					curr_column=0;
					curr_row++;
				}
			    }
			}
		}
	}
	free(mazebin);
	free(buf);
	return 0;
}
