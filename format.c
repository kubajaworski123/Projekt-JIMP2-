#include "format.h"
#include "structure.h"
#include <math.h>

void right_on(uint8_t** right, int row, int column){
	right[row][column/8]+=(uint8_t)pow(2.0, 7.0-(double)(column%8));
}

void bottom_on(uint8_t** bottom, int row, int column){
	bottom[row][column/8]+=(uint8_t)pow(2.0, 7.0-(double)(column%8));
}
<<<<<<< HEAD
=======

int right_exists(uint8_t** right, int row, int column){
	uint8_t mask = (uint8_t)pow(2.0,7.0-(double)(column%8));
	if((right[row][column/8]&mask) == mask){
		return 1;
	}else{
	      return 0;
	      }
}

int bottom_exists(uint8_t ** bottom , int row , int column){
	uint8_t mask = (uint8_t)pow(2.0,7.0-(double)(column%8));
	if((bottom[row][column/8]&mask) == mask){
	return 1;
	}else{
		return 0;
	}
}
>>>>>>> 99cc524 (dodanie search)
