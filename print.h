#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
int* vertice_to_ancestor(int* vertice , FILE* IN , FILE* OUT);
long convert_output(int* start_end);
void reverse_output(long lines);
void steps(long lines);
#endif
