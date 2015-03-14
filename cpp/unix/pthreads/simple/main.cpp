#include "arrays.h"
#include <pthread.h>


void* fill_array_(void *value);
void* print_primes_(void *value);
void* print_array_(void *value);
void* squares_(void *value);
void* sum_(void *value);


    const int size = 100000;
    int array[size];


int main() {

    if(234.2 %2){
        printf("Hey");
    }

	int  iret1, iret2, iret3, iret4, iret5;

	pthread_t thread1, thread2, thread3, thread4, thread5;
	const char *message5 = "Thread 5";
	const char *message4 = "Thread 4";
	const char *message3 = "Thread 3";
	const char *message2 = "Thread 2";
	const char *message1 = "Thread 1";


     iret1 = pthread_create( &thread1, NULL, fill_array_, (void*) message1);
     iret2 = pthread_create( &thread2, NULL, print_primes_, (void*) message2);
     iret3 = pthread_create( &thread3, NULL, print_array_, (void*) message3);
     iret4 = pthread_create( &thread4, NULL, squares_, (void*) message4);
     iret5 = pthread_create( &thread5, NULL, sum_, (void*) message5);

     pthread_join( thread1, NULL);
     pthread_join( thread2, NULL);
     pthread_join( thread3, NULL);
     pthread_join( thread4, NULL);
     pthread_join( thread5, NULL);


     printf("Thread 1 returns: %d\n",iret1);
     printf("Thread 2 returns: %d\n",iret2);




	cout << "array:" << endl;
	fill_array(array, size);

	cout << "found primes in array:" << endl;
	print_primes(array, size);
	cout << endl;
	
	print_array(array, size);
	cout << endl;
	
	squares(array, size);
	print_array(array, size);
	
	cout << endl;
	

	int total = sum(array, size);
	cout << " sum of squares of elements: " << total << endl;
	return 0;
}


void  *fill_array_(void *value){
	while(true){
		cout << " filling array " << endl;
                fill_array(array, size);
	}
}
void  *print_primes_(void *value){
	while(true){
		cout << " print primes " << endl;
             print_primes(array, size);
	}
}
void  *print_array_(void *value){
	while(true){
		cout << " print_array" << endl;
             print_array(array, size);
	}
}
void  *squares_(void *value){
	while(true){
		cout << " squares " << endl;
                squares(array, size);
	}
}
void  *sum_(void *value){
	while(true){
		cout << " sum " << endl;
                print_array(array, size);
	}
}
