#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <unistd.h>
#include "file_handling.h"
#include "format.h"
#include "read_txt.h"
#include "read_binary.h"
#include "search.h"
#include "print.h"
#include <math.h>

int main(int argc, char **argv){
	Maze maze = malloc(1024*256*sizeof(uint8_t)+4*sizeof(int));
	maze_init(maze);
	int help = 0;
	int binaryfile = 0;
	int textfile = 0;
	char* file;
	opterr = 0;
	while ((c = getopt(argc,argv,"hb:t:"))!=-1)
		switch(c){
		    case 'h':
			help = 1;
			break;
		    case 'b':
			binaryfile = 1;
			strcpy(file,optarg);
		    case 't':
			textfile = 1;
			strcpy(file,optarg);
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
	if (binaryfile+textfile!=1){
		fprintf(stderr,"Błąd: proszę wczytać plik binarny LUB tekstowy.\n");
		return 2;
	}
	if (help==1){
		printf("=== PROGRAM DO ROZWIĄZYWANIA LABIRYNTU ===\n
			Instrukcja:\n
			1. Skompiluj program przy użyciu komendy "/* jakiej? */".\n
			2. Wywołaj program i podaj jako argument plik z labiryntem:\n
			./a.out -t <nazwa_pliku>, jeżeli chcesz podać plik tekstowy\n
			./a.out -b <nazwa_pliku>, jeżeli chcesz podać plik binarny\n
			");
	}
	else {
		if (binaryfile==1){
			int tmp = read_binary(file,maze);
			if (tmp==-1) return 3;
		} else if (textfile==1) {
			uint32_t dims = read_txt(file,maze);
			if (dims==1) return 4;
		}
		// search i print...
	}
	maze_free(maze);
	return 0;
}
