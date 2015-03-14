
#ifndef NUMERICAL_H
#define NUMERICAL_H

#include "function.h"

#ifndef PRINT_ITERATIONS
    #define PRINT_ITERATIONS
#endif


#ifndef ACCEPTED_ERROR
    #define ACCEPTED_ERROR      0.01
#endif


// should make a wrapper for this:
extern double  iterations_count;

double  bisection_method(poly_t* p, double a, double b);
double  bisection_method_func_t(func_t* f, double a, double b);
double  false_position_method(poly_t* p, double a, double b);
double  secant_method(poly_t* p, double a, double b);
double  newton_method(poly_t* p, double a, double b);
double  fixed_point_method(poly_t* polynomial, double fixed_point_estimate, int iterations);

func_t* generate_fixed_point_function(func_t* p);                        // constructor

#endif

