#include "helper.h"

double
sqrt_iterative(double number){
    double approx_root = 2; 
    double quotient = 0;
    double difference = 0;
    do{   
        quotient = number/approx_root;
        difference = quotient - approx_root;
        approx_root += difference/2;
    } while (!within(difference, 0.0000001, 0.00));
    return approx_root;
}

// Is F_approx within the expected value, Given some error "epsilon"?
int   
within(double f_approx, double epsilon, double expected){
    if (fabs(f_approx - expected) < epsilon){
        return 1;
    }
    return 0;
}