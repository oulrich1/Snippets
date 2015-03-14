/****************************************************/
/* // simple gettime with 6 digits of precision
*/
/*****************************************************/ 


#include "time_string.h"



using namespace std;

int main()
{
	//struct timespec* time_st = (struct timespec*)malloc(sizeof(struct timespec));
	struct timespec time_st;

	get_timespec(&time_st);

	l_double t1, t2;
	t1 = print_time(&time_st, 0);

	while(true){

		t2 = print_time(&time_st, 0);

		cout << fixed << t2 << endl;

		//sleep(1);
		//cout << fixed << t2 - t1 << endl;
		//t1 = t2;
	  get_timespec(&time_st);
	}
	
	
  return 0;
}
