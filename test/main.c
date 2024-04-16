#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <unistd.h>
#include "format.h"
#include "read_txt.h"
#include "read_binary.h"
#include "search.h"
#include "print.h"
#include <math.h>

int main(int argc, char **argv){
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
				fprintf(stderr,"Błąd: opcja wywołania -%c wymaga podania argumentu.\n",optopt);
				return 1;
			}
			else
				fprintf(stderr,"Nieznana opcja wywołania -%c - zostanie zignorowana przez program.\n",optopt);
			break;
		    default:
			abort();
		}
	if (binaryfile==1 && textfile==1){
		fprintf(stderr,"Błąd: proszę wczytać plik binarny LUB tekstowy.\n");
		return 2;
	}
	if (help==1){
		// Komunikat o pomocy
	}
	else {
		// Tutaj właściwy program
	}
	return 0;
}
