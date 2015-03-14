
#ifndef FUNCTION_H
#define FUNCTION_H 

#include "polynomial.h"

struct function{
    // a function is either broken
    // into smaller functions
    struct function*    top;
    struct function*    bottom;   // divisor or NULL
    struct function*    exponent; // wraps top and bottom

    // Or a function is a polynomial 
    // (not both) 
    poly_t*             polynomial;
};
typedef struct function func_t;

void    init_func(func_t* p, char const* expr);
void    print_func(func_t* p);
double  evaluate_func(func_t* f, double x);
void    free_func(func_t* f);

#endif
