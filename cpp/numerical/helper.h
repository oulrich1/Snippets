
#ifndef HELPER_H
#define HELPER_H 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef true
    #define true 1
#endif
#ifndef false
    #define false 0
#endif
#ifndef max
    #define max(a, b) ((a) > (b) ? (a) : (b))
#endif 

#ifndef min
    #define min(a, b) ((a) < (b) ? (a) : (b))
#endif 

#ifndef NULL
    #define NULL 0
#endif
// #ifndef bool
//     #define bool int
// #endif

#ifndef ACCEPTED_ERROR
    #define ACCEPTED_ERROR      0.01
#endif

double  sqrt_iterative(double number);
int     within(double, double, double); //is num, epsion offset away, from some value

#endif
