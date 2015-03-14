
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H 

#include "helper.h"

#define MAX_COEFFICIENTS    100

struct poly{
    int term_count;
    double c[MAX_COEFFICIENTS];
    struct function terms[MAX_COEFFICIENTS]; 
};
typedef struct poly poly_t;

void    init_poly(poly_t* p, int term_count);
void    print_poly(poly_t* p);
double  evaluate_poly(poly_t* p, double x);  //wrapper for evaluate
poly_t* derivative(poly_t* p);
void    free_poly(poly_t* p);

#endif
