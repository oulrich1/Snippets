#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H 

#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <utility>
#include <map>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <math.h>

using namespace std;

#ifndef LD_T
typedef long double LD_T;
#else
#warning "Typedef error:   cannot define 'long double' as 'LD_T'. LD_T already defined."
#warning "Typedef warning: defining LD_T as a double instead... could cause problems.."
typedef double LD_T
#endif

typedef std::vector<LD_T> vector_t;
typedef vector<vector_t>  _2D;

/* inline */
LD_T dot ( std::vector<LD_T> &v1, 
           std::vector<LD_T> &v2);

/* inline */
_2D multiply_matrix(_2D &A, _2D &B);
_2D ijk_multiply_matrix(_2D &A, _2D &B);    // ijk 
_2D ikj_multiply_matrix(_2D &A, _2D &B);
_2D kij_multiply_matrix(_2D &A, _2D &B);

/* determinant */
LD_T det(_2D A); 

// MATRIX M is the matrix that is disconnected
// from the x_iter and y_iter column and row 
// (where the scaler exists)
_2D findM(_2D &A, int y_iter, int x_iter, int SIZE);   
                                                

void print_matrix(_2D &A, int m, int n);

void sendMatrixToFile(_2D &C, ofstream &fout);

#endif
