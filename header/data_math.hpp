#ifndef __DATA_MATH__
#define __DATA_MATH__

#include "structs.hpp"

struct data mean_d(struct data* d, const int size); //calcs mean of data array
struct data stdev_d(struct data m, struct data* d, const int size); //calcs stdev of of data array using mean of data array 
float pyth(float a, float b); //does pythagorian theorem
void printS(struct data d); //prints data in comma separeted line

#endif
