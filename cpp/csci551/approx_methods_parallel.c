#include "approx_methods.h" /* Includes the util.h */

#include <mpi.h>            /* For MPI functions, etc */ 


// TODO: use these to express 
// math functions and operations
// #include <gsl/gsl_sf_bessel.h>
// #include <gsl/gsl_math.h>

/* 
 * Compile:    
 *    mpicc -g -Wall -std=c99 -o mpi_hello main.c
 * Usage:        
 *    mpirun  -n<number of processes> ./mpi_hello
 */

const int  MAX_STRING   = 100;
const LD_T T_approx     = 3; // Trapazoid count approximation
const LD_T TRUE_VALUE   = 4003.7209001513268265929;

int main(int argc, char const *argv[])
{
  //char       greeting[MAX_STRING];  /* String storing message */
    int        comm_sz;               /* Number of processes    */
    int        my_rank;               /* My process rank        */

    LD_T x_0 = 100;
    LD_T x_n = 600;

    if (my_rank == 0) { 

        /* 0th process Master processor:
           perform user i/o */
        #ifdef INPUT_ASK_AB
            printf("Please input [a,b]:\n");
            scanf("%Lf", &x_0);
            scanf("%Lf", &x_n);
            printf("Thanks.. approximating integral\n");
        #endif

    }


    // LD_T root1 = approx_root_bisection(-100, 600, 0.001);
    // printf("x=%.23Lf, y=%.23Lf\n", root1, f(root1));

    /* Start up MPI */
    MPI_Init(NULL, NULL); 

    /* Get the number of processes */
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 

    /* Get my rank among all the processes */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 

    // should be global constants...
    if (comm_sz == 1) {
        exit(0);
    }

    LD_T dxPT  = (x_n - x_0)/T_approx;      // dx Per Trapazoid 
    LD_T T_per_process = T_approx/(comm_sz-1); // Traps per process = total traps / processes used to calc
    

    
    LD_T dxPP  = T_per_process*dxPT;        // dx Per Processor

    // LD_T total_true_integral = 4003.7209001513;

    if (my_rank != 0) { 
        printf("Greetings from process %d of %d!\n", my_rank, comm_sz);
        
        // process rank dependant
        LD_T a    = x_0 + (my_rank-1)*dxPP;         // find the left bound of this processor's data
        LD_T b    = a + dxPP;
        LD_T accepted_relative_error = 0.0000000000005;
        //LD_T accepted_relative_error = 0.0000005;

        operation_constants_t operation_constants = {{a,b, T_per_process}, {0, accepted_relative_error}, TRUE_VALUE};

        // double time_start = MPI_Wtime();
        // approx_result_t local_solution = approx_min_interval(x_0, x_n, T_approx, accepted_relative_error);
        // double time_end = MPI_Wtime();
        
        double time_start = MPI_Wtime();
        //approx_result_t solution = approx_min_interval(a, b, T_per_process, accepted_relative_error);
        approx_result_t solution = approx_integral_find_min_trapezoids(&f1, operation_constants);
        
        double time_end = MPI_Wtime();

        operation_constants.interval.N = solution.N;

        LD_T T1     = abs_ld(time_start - time_end);
        LD_T T_min  = T1;
        for (int i = 0; i < 5; ++i)
        {
            printf("Rank#: %d:\n\
                approximate    =  %.14Lf;\n\
                t              =  %.14Lf;\n\
                approx error   =  %.14Lf;\n\
                rel_approx_err =  %.14Lf;\n\
                run-time (sec) =  %.9Lf;\n\n", 
                    my_rank, solution.approximate, solution.N, solution.error.absolute, 
                    solution.error.relative,
                    abs_ld(time_end - time_start));

            time_start = MPI_Wtime();
            //solution = approx_min_interval(a, b, solution.N, accepted_relative_error);
            solution = approx_integral_find_min_trapezoids(&f1, operation_constants);

            time_end = MPI_Wtime();

            T1 = abs_ld(time_start - time_end);
            if(T1 < T_min){
                T_min = T1;
            }
        }

        printf("Rank#: %d : Finished Minimum Time (using t trapazoids): %0.9Lf\n", my_rank, T_min);

        /* Send message to process 0 */ 
        MPI_Send(&solution, sizeof(approx_result_t), MPI_BYTE, 
                        0, 0, MPI_COMM_WORLD); 


    } else if (my_rank == 0) {  
        printf("Greetings from process %d of %d!\n", my_rank, comm_sz);

        approx_result_t solution;
        LD_T total_approximate = 0;
        LD_T total_traps = 0;
        for (int processor_id = 1; processor_id < comm_sz; processor_id++) {
            /* Receive message from process q */
            MPI_Recv(&solution, sizeof(approx_result_t), MPI_BYTE,  // MPI_LONG_DOUBLE
                    processor_id, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_approximate += solution.approximate;
            total_traps += solution.N;
        } 
        printf("Total Sum:          %.10Lf\n", total_approximate);
        printf("Total Trapazoids:   %.10Lf\n", total_traps);
    } 

    /* Shut down MPI */
    MPI_Finalize(); 

    return 0;
}
