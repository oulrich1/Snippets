/****************************************************/
/* // simple gettime with 6 digits of precision
*/
/*****************************************************/ 


#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <unistd.h>
#include <pthread.h>
#include <exception>
#include <map>
#include <algorithm>
#include <math.h>
#include <time.h>
#include <vector>
#include <stdlib.h>

#include <stdio.h>

#include <limits.h>
#include <sstream>
#include <sys/time.h>
#include <time.h>
#include <iomanip>


#ifndef TIME_STRING_H
#define	TIME_STRING_H


typedef unsigned char u_char;

typedef long double		l_double;

#define PRINT_OUT_FALSE 0
#define PRINT_OUT_TRUE  1

/* NOTE: use timespec instead of timespec if wanting to use nanoseconds */

using namespace std;

/* 
	toString using stringstream 
*/
string
toString(int d);

/* 
	@params:  struct timespec *				pointer to the timespec 

						u_char print_out_bool - if 1 then print out from within, else if 0 dont print,
																		set to 0 if it should not print to an ostream
																		only return the long double time value

						ostream out		*					pointer to the ostream
																		note: prints out in fixed notation


	@return:	time in decimal notation as a long double

*/

l_double
print_time(	struct timespec* tv_st, 
						u_char print_out_bool = PRINT_OUT_FALSE,
						ostream &out = cout);


/*	getTime   NOTE: switch to timespec if possible
	
	@params:	struct timespec * time_st :  set to the current timespec struct with 
																				the seconds and micro seconds (10^-6 [s])

									sets time_st which is of type struct timespec
										to the current timespec struct
									with gettimeofday(,)
																				
	@returns:	error value returned 1 is success, else its a failure

*/

int
get_timespec(timespec* time_st, clockid_t clk_id = CLOCK_MONOTONIC);

#endif
// end file
