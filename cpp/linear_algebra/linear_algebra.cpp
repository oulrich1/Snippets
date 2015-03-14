/****************************************************/
/*     
    Name          :   Oriah Ulrich
   
       Implementations:
            Dot
            Matrix Multiply
                ijk, ikj, kij  (examine)
     
*/

#include "linear_algebra.h"

using namespace std;

void print_matrix(_2D &A, int m, int n){
    for (int i = 0; i < m; i++){
        for (int j= 0; j < n; j++){
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}


/*inline*/ 
LD_T dot ( std::vector<LD_T> &v1, 
           std::vector<LD_T> &v2) {
    // if the user tries to dot two evectors of different sizes..
    // default operation is to just dot the minimum number of values
    int min_elements = (v1.size() < v2.size() ? v1.size() : v2.size());
    LD_T result = 0;
    for (int i = 0; i < min_elements; ++i)
    {
        result += v1[i] * v2[i];
    }
    return result;
}


/*inline*/ 
_2D multiply_matrix(_2D &A, _2D &B){
    return ijk_multiply_matrix(A, B);
}  

_2D ijk_multiply_matrix(_2D &A, _2D &B){
    LD_T    result = 0;         // at C_row_column

    int A_row_count = A.size();
    int B_row_count = B.size(); // or just A[0].size();
    int B_col_count = B[0].size();

    _2D     C(A_row_count, vector_t(B_col_count, 0));

    for (int row = 0; row < A_row_count; ++row) {
        for (int col = 0; col < B_col_count; ++col) {
            for (int k = 0; k < B_row_count; ++k) {
                C[row][col] += A[row][k] * B[k][col];
            }
        }
    }

    return C;
}  

/* MIDDLE DOT PRODUCT.. (Adds the elements in column 
    major order for each row) */
_2D ikj_multiply_matrix(_2D &A, _2D &B){
    LD_T    result = 0;         // at C_row_column

    int A_row_count = A.size();
    int B_row_count = B.size(); // or just A[0].size();
    int B_col_count = B[0].size();

    _2D     C(A_row_count, vector_t(B_col_count, 0));

    for (int row = 0; row < A_row_count; ++row) {
        for (int k = 0; k < B_row_count; ++k) {
            for (int col = 0; col < B_col_count; ++col) {
                C[row][col] += A[row][k] * B[k][col];
            }
        }
    }

    return C;
}  

/* OUTER DOT PRODUCT.. (Adds the elements in column major order, 
    for ) */
_2D kij_multiply_matrix(_2D &A, _2D &B){
    LD_T    result = 0;         // at C_row_column

    int A_row_count = A.size();
    int B_row_count = B.size(); // or just A[0].size();
    int B_col_count = B[0].size();

    _2D     C(A_row_count, vector_t(B_col_count, 0));

    for (int k = 0; k < B_row_count; ++k) {
        for (int row = 0; row < A_row_count; ++row) {
            for (int col = 0; col < B_col_count; ++col) {
                C[row][col] += A[row][k] * B[k][col];
            }
        }
    }
    return C;
}  


LD_T det(_2D A){
    LD_T determinant_SUBSUM = 0;
    int rowP = 0;
    for(int x_iter=0; x_iter<A.size(); x_iter++){
        if(A.size() > 2){
            // since this is defined as a ROW EXPANSION DETERMINANT.. the 0th row is chosen
            LD_T r = A[rowP][x_iter] * (pow(-1, (rowP + x_iter))) 
                      * det( findM(A, rowP, x_iter, A.size()));
            determinant_SUBSUM += r;
        }
        else{
            //cout << "returning with value " << (A[0][0] * A[1][1] - A[1][0] * A[0][1]) << endl;
            return (A[0][0] * A[1][1] - A[1][0] * A[0][1]);
        }
    }// end for
    return determinant_SUBSUM;
}


// SIZE is the size of the _2D (SIZE * SIZE) 
_2D findM(_2D &A, int i, int j, int SIZE){
    _2D B(SIZE-1, vector_t(SIZE-1,0)); 
    // it is known that the MATRIX B will be 1 less the SIZE 
    // of matrix A ( such that it is still square)_

    // for the entire matrix A... move values that arn't within
    //   the column and not within the ROW of the matrix A.... INTO B
    //   in other wrods.. move values from A into B.. such that
    //   the values arnt in common with the element that is being 
    //   EXPANDED in other words the values in common with the element 
    //   selected are in the same row or same column
    int new_row_iter = 0;
    int new_col_iter = 0;
    for(int row_iter = 0; row_iter < SIZE; row_iter++){
        if((row_iter == i)){
            continue;
        }
        else{
            for(int col_iter = 0; col_iter < SIZE ; col_iter++){
                if((col_iter == j)){
                    continue;
                }
                else{
                    B[new_row_iter][new_col_iter] = (A[row_iter][col_iter]);
                    new_col_iter++;
                }
            } // end col for
            new_col_iter = 0;
            new_row_iter++;
        }
    } // end row for

    return B;
};
