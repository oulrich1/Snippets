
#include "numerical.h"

double iterations_count = 0;

/* - - - - Root finding techniques - - - - */

double  
bisection_method_func_t(func_t* f, double a, double b){
    double c = (double)(a+b)/2.0;   // cut in half..
    double f_c = evaluate_func(f, c);
    double iteration_error = min(fabs(c-a), fabs(b-c)); // prevent infinitely dividing the intervals.. 

    iterations_count++;
    //printf("(%f,%f); (%f,%f); (%f,%f);\n", a, evaluate(p, a), c, evaluate(p, c), b, evaluate(p, b));
    if(within(f_c, ACCEPTED_ERROR, 0) == true){  //  we found a root, definitely stop (f_c = 0)
#ifdef PRINT_ITERATIONS
        printf("Iterations: %f\n", iterations_count);
#endif
        iterations_count = 0;
        return c;
    } else if(iteration_error < ACCEPTED_ERROR){ // we "should" stop now
#ifdef PRINT_ITERATIONS
        printf("Iterations: %f\n", iterations_count);
#endif
        iterations_count = 0;
        return c;
    } else {
        double f_a = evaluate_poly(f, a);
        
        if(f_a * f_c < 0){ // then one f(?) is negative and below the line y=0
            return bisection_method(f, a, c);
        } else { // (both are the same sign) (check other half of I)
            return bisection_method(f, c, b);
        }
    }
}

/* Bisection Method: returns p from domain [a,b] */
double
bisection_method(poly_t* p, double a, double b){
    double c = (double)(a+b)/2.0;   // cut in half..
    double f_c = evaluate_poly(p, c);
    double iteration_error = min(fabs(c-a), fabs(b-c)); // prevent infinitely dividing the intervals.. 

    iterations_count++;
    //printf("(%f,%f); (%f,%f); (%f,%f);\n", a, evaluate(p, a), c, evaluate(p, c), b, evaluate(p, b));
    if(within(f_c, ACCEPTED_ERROR, 0) == true){  //  we found a root, definitely stop (f_c = 0)
#ifdef PRINT_ITERATIONS
        printf("Iterations: %f\n", iterations_count);
#endif
        iterations_count = 0;
        return c;
    } else if(iteration_error < ACCEPTED_ERROR){ // we "should" stop now
#ifdef PRINT_ITERATIONS
        printf("Iterations: %f\n", iterations_count);
#endif
        iterations_count = 0;
        return c;
    } else {
        double f_a = evaluate_poly(p, a);
        
        if(f_a * f_c < 0){ // then one f(?) is negative and below the line y=0
            return bisection_method(p, a, c);
        } else { // (both are the same sign) (check other half of I)
            return bisection_method(p, c, b);
        }
    }
}

/*  Kinda like linear interpolation 
    used to estimate the next point */
double
false_position_method(poly_t* p, double a, double b){
    // C is the root estimate..
    double f_a = evaluate_poly(p, a);
    double f_b = evaluate_poly(p, b);
    double c = a - (f_a / (f_b - f_a)) * (b-a);
    double f_c = evaluate_poly(p, c);

    double iteration_error = min(fabs(c-a), fabs(b-c)); // prevent infinitely dividing the intervals..
    //printf("(%f,%f); (%f,%f); (%f,%f);\n", a, evaluate(p, a), c, evaluate(p, c), b, evaluate(p, b));
    if(within(f_c, ACCEPTED_ERROR, 0) == true){  //  we found a root, definitely stop (f_c = 0)
        return c;
    } else if(iteration_error < ACCEPTED_ERROR){ // we "should" stop now
        return c;
    } else {
        if(f_a * f_c < 0){ // then one f(?) is negative and below the line y=0
            return false_position_method(p, a, c);
        } else { // (both are the same sign) (check other half of I)
            return false_position_method(p, c, b);
        }
    }
    return c;
}

// secant (linear interpolated line with slope m) is extimated:
// this is used to find the next point in the sequence ... 
double
secant_method(poly_t* p, double a, double b){
    double root_estimate = (a+b)/2.0;
    double prev_root = root_estimate + 1;  // TODO: estimate vaguely where the root might be..
    int i = 0;
    for (i = 0; i < 100; ++i) {            // just enough iterations?
        root_estimate = root_estimate - ( (evaluate_poly(p, root_estimate) * (root_estimate - prev_root)) 
                                            / (evaluate_poly(p, root_estimate) - evaluate_poly(p, prev_root))  );
        if (within(evaluate_poly(p, root_estimate), ACCEPTED_ERROR, 0)){
            // the f(root_approx) sorta equals 0..
            break;
        } else if (fabs(root_estimate - prev_root ) < ACCEPTED_ERROR){
            // the root hasnt changed very much 
            // since the last root estimate..
            // lets just stop.. (might be risky)
            break;
        }
    }
    //printf("Secant Iterations: %d\n", i);
    return root_estimate;
}

// continuous secant method essentially..
double 
newton_method(poly_t* p, double a, double b){
    double error = 0;
    poly_t* d = derivative(p);

    double x = a + 0.001;
    double prev_x;
    do{
        prev_x = x;
        x = x - evaluate_poly(p, x)/evaluate_poly(d, x);
        error = x - prev_x;
    } while(error > ACCEPTED_ERROR);

    free(d);
    return x;
}

/* returns the estimated p_n */
double 
fixed_point_method(poly_t* polynomial, double fixed_point_estimate, int iterations){
    double p_n = fixed_point_estimate;
    double prev_p_n = p_n;
    for (int i = 0; i < iterations; ++i) {
        p_n = evaluate_poly(polynomial, p_n); 
        if (within(p_n, ACCEPTED_ERROR, prev_p_n)){
            return p_n;
        }
    }
    return p_n;
}
// = = = = = = = = = = = = = = = = = = = = = =
// End root finding techniques...


//  Generates a g(X) | x - g(x) = f(x) 
// returns a g(x) polynomial that calculates
// the next value of X ( of course there are 
//  many varieties of the g(x) )
func_t* 
generate_fixed_point_function(func_t* p){
    func_t* g = (func_t*)malloc(sizeof(func_t)); 
    free(g);
    // manipulate a function f(x)
    // into the form x=g(x)...
}   
