
#include "numerical.h"

/* Different implementations of simple root-finding techniques..
    The simpler ones do well, provided a correct and usable interval 
    is passed in. The better ones will handle really large intervals 
    that contain multiple zeros, discontinuities.. 

    Currently, interval must be sufficiently close to the root    */

#define TEST_ROOT_FINDING
// #define TEST_FIXED_POINT
#define TEST_EVALUATE_FUNC

int 
main(int argc, char** argv){

    /* Initialize the objects */
    poly_t* p = (poly_t*)malloc(sizeof(poly_t));

    /* Test the Polynomial */

    double root = 0;

#ifdef TEST_ROOT_FINDING
    init_poly(p, 5);  
    p->c[0] = 4;
    p->c[1] = 4;
    p->c[2] = -4;
    p->c[3] = -2;
    p->c[4] = 1;
    printf("Polynomial-P\n");
    print_poly(p);
    printf("\n");

    root = bisection_method(p, -2, -1);  
    printf("Binary Method:  root: (%f, %f)\n", root, evaluate_poly(p, root));


    func_t* f_test = (func_t*)malloc(sizeof(func_t));

    printf("Creating Function: %s \n", "x - (2^-x)");
    init_func(f_test, "x - (2^-x)"); // 2nd arg is char* expression to match to an equation..
    root = bisection_method_func_t(f, -2, -1);  
    printf("Binary Method Using Custom Function:  root: (%f, %f)\n", root, evaluate_func(f, root));

    free_func(f_test);

    root = false_position_method(p, -7, 5);
    printf("RP Method:      root: (%f, %f)\n", root, evaluate_poly(p, root));

    // this method requires knowing sorta 
    // where the individual roots are.
    // like: [-2, -1] or [0, 2] or [-2. 5]
    // (as do all, but with this one 
    // it is absolutely necessary..)
    root = secant_method(p, -7, 5); 
    printf("Secant Method:  root: (%f, %f)\n", root, evaluate_poly(p, root));

    root = newton_method(p, -7, 5); 
    printf("Newton Method:  root: (%f, %f)\n", root, evaluate_poly(p, root));
    
    printf("sqrt(25) = %f (actual: %f) \n", sqrt_iterative(25), sqrt(25));
    printf("sqrt(49) = %f (actual: %f) \n", sqrt_iterative(49), sqrt(49));
    printf("sqrt(42) = %f (actual: %f) \n", sqrt_iterative(42), sqrt(42));
    printf("sqrt(2345) = %f (actual: %f) \n", sqrt_iterative(2345), sqrt(2345));
    printf("sqrt(2234235) = %f (actual: %f) \n", sqrt_iterative(2234235), sqrt(2234235));
    printf("\n");
#endif 

#ifdef TEST_FIXED_POINT
    init_poly(p, 3);  
    p->c[0] = -3;
    p->c[1] = 1;
    p->c[2] = 2;
    printf("Polynomial-P\n");
    print_poly(p);
    printf("\n");

    double fixed_point_estimate = 1;
    root = fixed_point_method(p, fixed_point_estimate, 3); 
    printf("Fixed Point Method:  root: (%f, %f)\n", root, evaluate_poly(p, root));    
#endif

#ifdef TEST_EVALUATE_FUNC
    func_t* f = (func_t*)malloc(sizeof(func_t));
    printf("Creating Function: %s \n", "(1+x)^x");
    init_func(f, "(1+x)^x"); // 2nd arg is char* expression to match to an equation..
    double x = 3;
    double value = evaluate_func(f, x);
    printf("Evaluate Function: f(%f) = %f\n", x, value);
    free_func(f);

#endif

/* Clean allocated memory, Program complete.. */
    if(p){
        free_poly(p);
    }

    return 0;
}



