
#include "polynomial.h"

/*  Initialize a polynomial:
    Index of poly cooeficients (c) 
     is used as the exponent of domain. 
    Up to 'MAX_COEFFICIENTS'  */
void 
init_poly(poly_t* p, int term_count){
    if(term_count > MAX_COEFFICIENTS){
        term_count = MAX_COEFFICIENTS;
        printf("Error, too many terms specified..");
    } else if(term_count < 0) {
        term_count = 0;
    }
    p->term_count = term_count;
    for(int i=0; i < term_count; i++){
        p->c[i] = 1;
    }
}

// simply prints out a serialized/stringified 
// version of the data structure..
void
print_poly(poly_t* p){
    printf("%f", p->c[0]);
    for (int i = 1; i < p->term_count; ++i)
        printf(" + %fx^%f", p->c[i], (double)i);
    printf("\n");
}

double
evaluate_poly(poly_t* p, double x){
    double retval = 0;
    for(int i=0; i < p->term_count; i++){
        retval += (p->c[i]*pow(x,i));
    }
    return retval;
}

poly_t*
derivative(poly_t* p){
    poly_t* d = (poly_t*)malloc(sizeof(poly_t));
    init_poly(d, p->term_count-1);
    for (int i = 1; i < p->term_count; ++i){
        d->c[i-1] = (p->c[i] * i);
    }
    return d;
}

void    
free_poly(poly_t* p){
    free(p);
}
