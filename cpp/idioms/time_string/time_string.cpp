/****************************************************/
/* // simple gettime with 6 digits of precision
*/
/*****************************************************/ 

/* usage: create a struct timespec pointer and allocate it memory */

/* OR: create struct timespec. */

using namespace std;

#include "time_string.h"


/* NOTE: use timespec instead of timespec if wanting to use nanoseconds */

string
toString(int d){
	stringstream ss;
	ss << d;
	return ss.str();
}

/* 
	@params:  struct timespec * pointer to the timespec 

	@return:	time in decimal notation as a long double

*/

l_double
print_time(struct timespec* tv_st, u_char print_out_bool, ostream &out ){
	if(!tv_st){
		cerr << "Error: Incorrect Usage of \"print_time()\". Needs valid timespec." << endl;
		return -1;
	}
	
	string full_time = toString(tv_st->tv_sec) + "." + toString(tv_st->tv_nsec);

	if(print_out_bool && out)
		out << fixed << full_time << endl;

	return atof(full_time.c_str());	
}


int
get_timespec(timespec* time_st, clockid_t clk_id){

	//int error = gettimeofday(time_st, 0); // use if using timeval struct for usec isntead of nsec
	//CLOCK_REALTIME
	//CLOCK_PROCESS_CPUTIME_ID
	//CLOCK_THREAD_CPUTIME_ID
	int error = clock_gettime(clk_id, time_st); // and specify the clock id

	if(error){
		cerr << "Error: time not set!" << endl;
		return 0;
	}

	return 1; // success

}

