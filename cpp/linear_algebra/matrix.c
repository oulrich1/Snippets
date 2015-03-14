
/* 

    Class:          CSCI 551
    By:             Oriah Ulrich

    Assignment:     P3

        Perform matrix multiplication, exploring the ijk forms.
        Collect and analyze empirical timing data.
*/

#include <time.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>

#include <string.h>
#include <math.h>

#ifndef NULL
#define NULL 0
#endif

typedef unsigned int uint;
typedef double DATA_TYPE ;


/* --------------------------------------------------------------- */



typedef struct {
    DATA_TYPE**  values;
    int row_count;
    int col_count;
} Matrix;


Matrix*     matrix_new(int height, int width);                      // create a new matrix with width and height
bool        matrix_resize(Matrix* matrix);                          // resize a matrix to the matrix's row and col count
bool        matrix_resize_tosize(Matrix* matrix, int height, int width);   // same, specify the num row and cols
bool        matrix_init(Matrix* matrix, int value);                 // initialize the elements in the matrix to the value
int         matrix_count_elements(Matrix* matrix);                  // returns the total number of elements in the Matrix
DATA_TYPE   matrix_getvalue(Matrix* matrix, int i, int j);          // returns the value in the matrix at the i and j 
                                                                    //  (or just matrix->values[i][j])
bool        matrix_isvalid(Matrix* matrix);             // determines if matrix is not null and value pointers are not null
bool        matrix_dealloc_values(Matrix*);
bool        matrix_delete(Matrix*);                                 // clears the memory used by the Matrix

void        matrix_print(Matrix* matrix);


bool        matrix_populate_random(Matrix* matrix, int m, int n);   // populates an existing matrix
Matrix*     matrix_generate_random(int m, int n);                   // generates a new matrix and populates it, randomly


/* Matrix Multiply Functions */
Matrix*     matrix_mult_ijk(Matrix* M1, Matrix* M2);
Matrix*     matrix_mult_ikj(Matrix* M1, Matrix* M2);
Matrix*     matrix_mult_kij(Matrix* M1, Matrix* M2);


/* --------------------------------------------------------------- */


/* allocates a new matrix,
    sets the row and col count to specified values
    then resizes and inits the matrix.. */
Matrix*  matrix_new(int height, int width) {
    Matrix* matrix = (Matrix*) malloc(sizeof(Matrix));
    matrix->row_count = height;
    matrix->col_count = width;
    bool success = matrix_resize(matrix);
    if (!success) {
        free(matrix);
        matrix = NULL;
    }
    return matrix;
}

bool matrix_resize(Matrix* matrix) {
    if (!matrix || matrix->row_count <= 0) {
        return false;
    }
    /* if values already exists then clear it.. we are resizing..*/
    if (matrix->values) {
        if (matrix->row_count > 0 && matrix->values[0]) {
            for (int i = 0; i < matrix->row_count; ++i) {
                free(matrix->values[i]);
            }
        }
        free(matrix->values);
    }
    matrix->values = (DATA_TYPE**) malloc(sizeof(DATA_TYPE*) * matrix->row_count);
    for (int i = 0; i < matrix->row_count; ++i) {
        matrix->values[i] = (DATA_TYPE*) malloc(sizeof(DATA_TYPE) * matrix->col_count);
    }
    return matrix_init(matrix, 0); //returns true if successful..
}


/* resize to a specified size [m x n] = width and height 
    then it initilizes the matrix's values to 0*/
bool matrix_resize_tosize(Matrix* matrix, int height, int width) {
    if (!matrix) {
        return false;
    }
    matrix->row_count = height;
    matrix->col_count = width;
    bool success = matrix_resize(matrix);
    return matrix_init(matrix, 0);
}


/* Checks if matrix is allocated..
    if so then it sets all of the elements
    data equal to 'value'

    returns true if success
    returns false if matrix was empty 
        or no rows 
        or no columns   */
bool matrix_init(Matrix* matrix, int value) {
    if (!matrix || matrix->row_count <= 0) {
        return false;
    }
    for (int i = 0; i < matrix->row_count; ++i) {
        for (int j = 0; j < matrix->col_count; ++j) {
            matrix->values[i][j] = value;
        }
    }
    return true;
}

/* returns the total number of elements */
int matrix_count_elements(Matrix* matrix){
    return matrix->row_count * matrix->col_count;
}

/* get value at i,j.. could just matrix->value[i][j] */
DATA_TYPE matrix_getvalue(Matrix* matrix, int i, int j){
    return matrix->values[i][j];
}

bool matrix_dealloc_values(Matrix* matrix) {
    if (!matrix || !matrix->values || matrix->row_count <= 0) {
        return false;
    }
    for (int i = 0; i < matrix->row_count; ++i) {
        free(matrix->values[i]); // deletes a row vector
    }
    return true;
}

/* clears the matrix and frees the pointers  */
bool matrix_delete(Matrix* matrix){
    bool success = matrix_dealloc_values(matrix);
    if (!success) {
        return false;
    }
    free(matrix->values); // free pointer to pointers
    free(matrix);
    return true;
}     

void matrix_print(Matrix* matrix) {
    char comma[] = "  ";
    char brace_left = '[';
    char brace_right = ']';

    printf("%c \n", brace_left);
    for (int i = 0; i < matrix->row_count; ++i) {
        printf(" %c ", brace_left);
        strncpy(comma, ", ", 2);
        /* print the results */
        for (int j = 0; j < matrix->col_count; ++j) {
            if (j == matrix->col_count-1) {
                strncpy(comma, "  ", 2);
            }
            printf("%0.2f%s ", matrix->values[i][j], comma);
        }
        
        strncpy(comma, ", ", 2);
        /* determine conditional string */
        if (i == matrix->row_count-1) {
            strncpy(comma, "  ", 2);
        }

        printf(" %c%s", brace_right, comma);
        printf("\n");
    }
    printf("%c\n\n", brace_right);
}

bool matrix_isvalid(Matrix* matrix){
    if (!matrix || !matrix->values 
            || matrix->row_count <= 0 
            || !matrix->values[0]) {
        return false;
    }
    return true;
}


/* populates a matrix with random values if it is a valid matrix */
bool matrix_populate_random(Matrix* matrix, int m, int n){
    if ( !matrix_isvalid(matrix)) {
        return false;
    }
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++) {

            /* just some garbage random numbers.. */
            srand((((rand() % 213) % 43) + 1) * (i+1 * j 
                    + (rand()%7)*j*(i+1)) + time(NULL) 
                    * (rand() % 2000 + i * j) *j);

            int multiplier_val = 20;
            matrix->values[i][j] = rand() % 
                (4* (int)sqrt(n*multiplier_val)) - multiplier_val/2;
            // printf("%f\n", C->values[i][j] ); 
        }
    }
    return true;
}

/* simply generates a random new matrix */
Matrix* matrix_generate_random(int m, int n){
    Matrix* C = matrix_new(m, n);
    matrix_populate_random(C, m, n);
    return C;
}



/* --------------------------------------------------------------- */



/*
     
    Main Multiply Methods :
        Forms: ijk, ikj, kij
                            
                                */


/* M1 * M2 --- ijk form */
Matrix* matrix_mult_ijk(Matrix* M1, Matrix* M2) {
    int vector_size = M1->col_count;

    /*  if vectors size, or matrix width is 
        not appropriate. the number of elements 
        being multiplied must be equal      */
    if (vector_size != M2->row_count) {
        return NULL;
    }

    int new_row_count = M1->row_count;
    int new_col_count = M2->col_count;

    Matrix* M3 = matrix_new(new_row_count, new_col_count);

    for (int i = 0; i < M1->row_count; ++i) {
        for (int j = 0; j < M2->col_count; ++j) {
            // M3->values[i][j] = 0;
            for (int k = 0; k < vector_size; ++k) {
                M3->values[i][j] += M1->values[i][k] * M2->values[k][j];
            }
        }
    }

    return M3;
}


Matrix*  matrix_mult_ikj(Matrix* M1, Matrix* M2){
    int vector_size = M1->col_count;

    /*  if vectors size, or matrix width is 
        not appropriate. the number of elements 
        being multiplied must be equal      */
    if (vector_size != M2->row_count) {
        return NULL;
    }

    int new_row_count = M1->row_count;
    int new_col_count = M2->col_count;

    Matrix* M3 = matrix_new(new_row_count, new_col_count);

    for (int k = 0; k < vector_size; ++k) {
        for (int i = 0; i < M1->row_count; ++i) {
            for (int j = 0; j < M2->col_count; ++j) {
                M3->values[i][j] += M1->values[i][k] * M2->values[k][j];
            }
        }
    }

    return M3;
}


Matrix* matrix_mult_kij(Matrix* M1, Matrix* M2){
    int vector_size = M1->col_count;

    /*  if vectors size, or matrix width is 
        not appropriate. the number of elements 
        being multiplied must be equal      */
    if (vector_size != M2->row_count) {
        return NULL;
    }

    int new_row_count = M1->row_count;
    int new_col_count = M2->col_count;

    Matrix* M3 = matrix_new(new_row_count, new_col_count);

    for (int i = 0; i < M1->row_count; ++i) {
        for (int k = 0; k < vector_size; ++k) {
            for (int j = 0; j < M2->col_count; ++j) {
                M3->values[i][j] += M1->values[i][k] * M2->values[k][j];
            }
        }
    }

    return M3;
}


enum matrix_mult_state_t
{
    NULL_MODE = 0,
    IJK_MODE = 1,
    IKJ_MODE = 2,
    KIJ_MODE = 4
};


/* 
    Main:
    
    Reads from command line or from standard input.
        If command line, expects 2 more arguments:
            matrix mult form, and also the size of the square matrix
            then the values are expected in standard in
        else if not enough arguments or arguments are not as epected
            then read the matrix mult form and the size of the square
            matrix from stdin. then the values are, again, expected 
            through stdin.

    Performs the matrix mult as specified by the user's input to the program
        matrix mult forms: ijk, ikj, kij.

*/
int main(int argc, char const *argv[])
{
    int n = 0;
    int height, width = 0;
    Matrix* M1 = NULL;
    Matrix* M2 = NULL;
    uint matrix_mult_state = IJK_MODE; // ijk, ikj, kij forms

    char state_str[4] = "ijk";

    /* collect arguments and store in argument object */
    if (argc != 3) {
        n = 2;
        printf("input multiply form: ");
        scanf("%s", &state_str);
        printf("input square matrix size: ");
        scanf("%d", &n);
    } else {
        printf("Read values from command line arguments.. \n");
        strncpy(state_str, argv[1], 3);
        n = atoi(argv[2]);
    }

    if (!strcmp(state_str, "ijk")) { 
        matrix_mult_state = IJK_MODE;
    } else if (!strcmp(state_str, "ikj")) { 
        matrix_mult_state = IKJ_MODE;
    } else if (!strcmp(state_str, "kij")) { 
        matrix_mult_state = KIJ_MODE;
    } else {
        printf("unknown matrix mode.. defaulting to ijk.\n");
        matrix_mult_state = IJK_MODE;
    }



    /*     INITIALIZE THE MATRICIES     */

    const int num_matricies = 2;

    height = n;
    width = n;

    M1 = matrix_new(height, width); // n x n matrix
    M2 = matrix_new(height, width); // n x n matrix

    Matrix* matricies[2] = {M1, M2};
    Matrix* cur_matrix = NULL;

    /*  */
    DATA_TYPE element_value = 0;

    /* initialize the matricies with the std input */

    for (int matrix_iter = 0; matrix_iter < num_matricies; ++matrix_iter) {
        printf("input %d values for matrix: #%d (row major form) \n", 
                    height*width, matrix_iter + 1);
        cur_matrix = matricies[matrix_iter];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                scanf("%lf", &element_value);
                cur_matrix->values[i][j] = element_value;
            }
        }
    }
    
    /* test print */

    for (int matrix_iter = 0; matrix_iter < num_matricies; ++matrix_iter) {
        cur_matrix = matricies[matrix_iter];
        printf("Matrix: #%d\n", matrix_iter+1);
        matrix_print(cur_matrix);
    }



    /* PERFORM MATRIX OPERATIONS */


    Matrix* M3 = NULL;
    switch(matrix_mult_state){
        case NULL_MODE:
            return 1;
        break;
        
        case IJK_MODE:
            // printf("IJK\n");
            M3 = matrix_mult_ijk(M1, M2);
        break;
        
        case IKJ_MODE:
            // printf("IKJ\n");
            M3 = matrix_mult_ikj(M1, M2);
        break;

        case KIJ_MODE:
            // printf("KIJ\n");
            M3 = matrix_mult_kij(M1, M2);
        break;

        default:
        break;
    }

    printf("Matrix Result: \n");
    matrix_print(M3);

    return 0;
}