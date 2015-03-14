
#include "function.h"

void    
init_func(func_t* f, char const* expr){

    /* default function */
    f->top = (func_t*)malloc(sizeof(func_t));
    f->exponent = (func_t*)malloc(sizeof(func_t));
    f->bottom = NULL;
    f->polynomial = NULL;

    f->top->polynomial = (poly_t*)malloc(sizeof(poly_t));
    f->exponent->polynomial = (poly_t*)malloc(sizeof(poly_t));

    init_poly(f->top->polynomial, 2);
    f->top->polynomial->c[1] = 1; // 1 
    f->top->polynomial->c[1] = 1; // + x

    init_poly(f->exponent->polynomial, 2);
    f->exponent->polynomial->c[0] = 0;
    f->exponent->polynomial->c[1] = 1;

    // creates: (1 + x) ^ x
    /* - - - - - - - - */

    // TODO:
    // Create a parser.
    // parser the string expr
    // generate a function object 
    // from the parsing..

}

void    
print_func(func_t* p){
    return;
}

double
evaluate_func(func_t* f, double x){
    if (!f){
        return -1;    
    }
    double  retval = 0;
    if (f->polynomial){
        retval = evaluate_poly(f->polynomial, x);
    } else {
        if(f->top){
            retval += evaluate_func(f->top, x);
        }
        if (f->bottom){
            retval /= evaluate_func(f->bottom, x);
        }
        if (f->exponent){
            retval = pow(retval, evaluate_func(f->exponent, x));
        } 
    }
    return retval;
}

void    
free_func(func_t* f){
    if (!f){
        return;    
    }
    if (f->polynomial){
        free_poly(f->polynomial);
    } else {
        if(f->top){
            free_func(f->top);
            free(f->top);
        }
        if (f->bottom){
            free_func(f->bottom);
            free(f->bottom);
        }
        if (f->exponent){
            free_func(f->exponent);
            free(f->exponent);
        }
        free(f);
    }
    return;
}
