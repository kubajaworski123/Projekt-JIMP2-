#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <unistd.h>
#include <stddef.h>
#include "file_handling.h"
#include "format.h"
#include "read_txt.h"
#include "read_binary.h"
#include "search.h"
#include "print.h"
#include "search_bin.h"
#include <math.h>

int main(int argc, char **argv){
	Maze maze = malloc(sizeof(*maze));
	maze_init(maze);
	int help = 0;
	int binaryfile = 0;
	int textfile = 0;
	char c;
	char *file = malloc(64);
	opterr = 0;
	while ((c = getopt(argc,argv,"hb:t:"))!=-1)
		switch(c){
		    case 'h':
			help = 1;
			break;
		    case 'b':
			binaryfile = 1;
			strcpy(file,optarg);
			break;
		    case 't':
			textfile = 1;
			strcpy(file,optarg);
			break;
		    case '?':
			if (optopt=='b' || optopt=='t'){
				fprintf(stderr,"Błąd: opcja wywołania -%c wymaga podania argumentu.\nWpisz ./a.out -h, aby uzyskać pomoc.\n",optopt);
				return 1;
			}
			else
				fprintf(stderr,"Nieznana opcja wywołania -%c - zostanie zignorowana przez program.\n",optopt);
			break;
		    default:
			abort();
		}
	if (help==1){
		printf("=== PROGRAM DO ROZWIĄZYWANIA LABIRYNTU ===\n");
		printf("Instrukcja:\n");
		printf("1. Skompiluj program przy użyciu komendy \"make -f Makefile\".\n");
		printf("2. Wywołaj program i podaj jako argument plik z labiryntem:\n");
		printf("./a.out -t <nazwa_pliku>, jeżeli chcesz podać plik tekstowy\n");
		printf("./a.out -b <nazwa_pliku>, jeżeli chcesz podać plik binarny\n");
	}
	else if (binaryfile+textfile!=1){
                fprintf(stderr,"Błąd: proszę wczytać plik binarny LUB tekstowy.\n");
                return 2;
        }
	else {
		int *dim = malloc(2*sizeof(int));
		FILE *in;
		if (binaryfile==1){
			in = fopen(file,"rb");
			int tmp = read_binary(in,maze,dim);
			if (tmp==-1) return 3;
		} else if (textfile==1) {
			in = fopen(file,"r");
			uint32_t dims = read_txt(in,maze);
			if (dims==1) return 4;
			dim = maze_dim(in);
		}
		int* start_end = malloc(sizeof(int)*4);
		if (binaryfile==1)
			start_end = solve_maze_bin(maze,dim[0],dim[1]);
		else if (textfile==1)
			start_end = solve_maze(maze,dim[0],dim[1]);
		long lines = convert_output(start_end);
		reverse_output(lines);
		steps(lines);
		free(dim);
		free(start_end);
	}
	remove("ancestors.txt");
	remove("path.txt");
	remove("new_path.txt");
	free(file);
	maze_free(maze);
	return 0;
}
