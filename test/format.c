#include "format.h"
#include "structure.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

void right_on(uint8_t** right, int row, int column){
	right[row][column/8]+=(uint8_t)pow(2.0, 7.0-(double)(column%8));
}

void bottom_on(uint8_t** bottom, int row, int column){
	bottom[row][column/8]+=(uint8_t)pow(2.0, 7.0-(double)(column%8));
}
