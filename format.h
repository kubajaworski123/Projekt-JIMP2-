#ifndef FORMAT_H
#define FORMAT_H
<<<<<<< HEAD

void right_on(uint8_t** right, int row, int column);
void bottom_on(uint8_t** bottom, int row, int column);
=======
#include <stdint.h>
void right_on(uint8_t** right, int row, int column);
void bottom_on(uint8_t** bottom, int row, int column);
int bottom_exists(uint8_t** bottom , int row , int column);
int right_exists(uint8_t** right , int row , int column);
>>>>>>> 99cc524 (dodanie search)

#endif
