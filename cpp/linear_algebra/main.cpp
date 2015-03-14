#include "linear_algebra.h"

#ifndef WRITE_TO_FILE
#define WRITE_TO_FILE       // write results to file 
#endif

#ifndef TEST_DETERMINANT
//#define TEST_DETERMINANT    // test det() function
#endif


char stdinAskUserForNumber();
void sendMatrixToFile(_2D &C, ofstream &fout);
_2D generateRandomMatrix(int m, int n);


char stdinAskUserForNumber(){
    cout << "Enter a number, any number: ";
    char t;
    cin >> t;
    cout << endl;
    return t;
}

void sendMatrixToFile(_2D &C, ofstream &fout){
    int m = C.size();
    int n = C[0].size();
    fout << "{";
    for(int i =0;i < m;i++){
        fout << "{";
        for(int j=0;j < n;j++){
            fout << C[i][j] << ((j==n-1) ? "" : ",");
        }
        fout << "}";
        fout << ((i == m-1) ? "" : ",\n") ;
    }
    fout << "}\n\n";
}

_2D generateRandomMatrix(int m, int n){

    _2D C (m, vector_t(n,0));

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++) {
            srand((((rand() % 213) % 43) + 1) * (i+1 * j 
                    + (rand()%7)*j*(i+1)) + time(NULL) 
                    * (rand() % 2000 + i * j) *j);

            C[i][j] = rand() % (4 * (int)sqrt(n)) - 2;
            //cout << C[i][j] << " ";
        }
        //cout << endl;
    }
    //cout << endl;
    return C;
}


typedef struct 
{
    int argc;
    int m;
    int n;
    int l;
} args_t;

void stdin_args(args_t* args){
    cin >> args->m;
    cin >> args->n;
    cin >> args->l;
    cout << endl;
}

void collect_arguments(void (*collect_mnl)(args_t*), args_t* args){
    cout << "\n Hi there. This tests out the matrix methods, such as" << endl;
    cout << "  matrix multiply, and vector dot products as well as " << endl;
    cout << "  a method of finding determinants." << endl << endl;

    cout << " The matrix methods start out first. Just enter in 3 numbers" << endl;
    cout << "  that specifty the sizes of the Matricies M1 & M2 " << endl;
    cout << "   (ie. M1 = [m x n] &  M2 = [n x L]) " << endl;
    cout << "   [m, n, L]:   ";

    collect_mnl(args);
}

int main(int argc, char const *argv[])
{
    if (argc >= 2) {
        cerr << "\nWarning: does not expect command line arguments..\n" << endl;
    } 

    int iterationsSoFar = 0;
    int m = 1;
    int n = 1;
    int l = 1;

    args_t args = {3}; // 3 args..

    collect_arguments(&stdin_args, &args);

    while(args.m > 0 && args.n > 0 && args.l > 0) {

        m = args.m;
        n = args.n;
        l = args.l;

        _2D M1;
        _2D M2;
        _2D M3;

        M1 = generateRandomMatrix(m, n);
        M2 = generateRandomMatrix(n, l);


    #ifdef WRITE_TO_FILE
            ofstream fout ("matrix.in",  std::fstream::app);

            fout << "=---- Iteration# " << iterationsSoFar << " ----=\n";
            fout << " M1:\n";
            sendMatrixToFile(M1, fout);
            fout << " M2:\n";
            sendMatrixToFile(M2, fout);
            fout << "==============================\n\n";

            fout.close();
            fout.open("matrix.results",  std::fstream::app);
    #endif 



            /* IJK METHOD */
            //printf(" >> M1 * M2 (ijk) = \n\n");
            M3 = multiply_matrix(M1, M2);
            //print_matrix(M3, M3.size(), M3[0].size());
            //printf("\n");
    #ifdef WRITE_TO_FILE
            fout << "=---- Iteration# " << iterationsSoFar << " ----=\n M1 * M2 (ijk) = M3:\n";
            sendMatrixToFile(M3, fout);
    #endif 



            /* IKJ METHOD */
            //printf(" >> M1 * M2 (ikj) = \n\n");
            M3 = ikj_multiply_matrix(M1, M2);
            //print_matrix(M3, M3.size(), M3[0].size());
            //printf("\n");
    #ifdef WRITE_TO_FILE
            fout << " M1 * M2 (ikj) = M3:\n";
            sendMatrixToFile(M3, fout);
    #endif 



            /* KIJ METHOD */
            //printf(" >> M1 * M2 (kij) = \n\n");
            M3 = kij_multiply_matrix(M1, M2);
            //print_matrix(M3, M3.size(), M3[0].size());
            //printf("\n");
    #ifdef WRITE_TO_FILE
            fout << " M1 * M2 (kij) = M3:\n";
            sendMatrixToFile(M3, fout);
            fout << "\n";
    #endif 
        

        /* Matrix Multiply Result... */
        printf("\n\n >> M3 (final result) = \n");
        print_matrix(M3, M3.size(), M3[0].size());

    #ifdef TEST_DETERMINANT
        /* determinant */
        printf("\n >> Determinant(M1) = %Lf\n\n", det(M1));
    #endif

        collect_arguments(&stdin_args, &args);
        iterationsSoFar++;
    }

    cout << "\nDone. \n" << endl;

  return 0;
}