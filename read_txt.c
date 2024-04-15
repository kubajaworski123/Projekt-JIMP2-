#include "read_txt.h"
#include "format.h"
#include "structure.h"
#include <stdint.h>
<<<<<<< HEAD

=======
#include <stdio.h>
#include <stdlib.h>
>>>>>>> 99cc524 (dodanie search)
/* Moduł read_txt.c służy do odczytywania pliku wejściowego z labiryntem i jego konwersji
 * na format, który nasz program będzie obsługiwać. */

// Funkcja read_txt odczyta i zapisze labirynt oraz zwróci jego wymiary jako jedną liczbę.
// Liczba będzie miała postać: 1024*(wiersze-1) + (kolumny-1).
uint32_t read_txt(FILE *in, Maze maze){
	uint32_t dim = 0;
	char *buf = malloc(2050*sizeof(char));
        int current_line = -1;
        int i,j;
        for (i=0; i<128; i++){
                for (j=0; j<128; j++){
                        maze->right[i][j]=0;
                        maze->bottom[i][j]=0;
                }
        }
        while (fgets(buf,2050,in)!=0){
                current_line++;
                for (i=0; i<2050; i++){
                        if (buf[i]=='\0'){
                                if (dim%1024==0)
                                        dim+=(i-1)/2-1;
                                break;
                        }
                        if (buf[i]=='P'){
                                maze->start[0]=current_line;
                                maze->start[1]=i;
                        }
                        else if (buf[i]=='K'){
                                maze->finish[0]=current_line;
                                maze->finish[1]=i;
                        }
                        else if (current_line>0 && i>0) {
                                if (current_line%2==1){
                                        if (i%2==0 && buf[i]=='X'){
                                                right_on(maze->right,(current_line-1)/2,i/2-1);
                                        }
                                }
                                else {
                                        if (i%2==1 && buf[i]=='X'){
                                                bottom_on(maze->bottom,current_line/2-1,(i-1)/2);
                                        }
                                }
                        }
                }
        }
        dim+=1024*(current_line/2-1);
        free(buf);
	return dim;
}
