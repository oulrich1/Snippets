#include "arrays.h"



bool fill_array(int *array, int size){
	for(int i = 0; i < size; ++i ){
		array[i] = rand() % 100;
		cout << array[i] << " ";
	}
	cout << endl;
	return true;
}
bool print_array(const int *array, int size){
	for(int i = 0; i < size; ++i ){
		cout << array[i] << " ";
	}
	cout << endl;
	return true;
}
bool print_primes(const int *array, int size){
	for(int i = 0; i < size; ++i ){
		if( isPrime(array[i]) ){
			cout << array[i] << " " ;
		}
	}
	cout << endl;
	return true;
}
bool squares(const int *array, int size){
	for(int i = 0; i < size; ++i ){
		cout << array[i] *  array[i] << " ";
	}
	cout << endl;
	return true;
}

bool sum(const int *array, int size){
	for(int i = 0; i < size; ++i ){

	}
	return true;
}


bool isPrime(int num){
	for(int i = 2; i < sqrt(num); ++i){
		if(num % i == 0){
			return false; // its dividible by i
		}
	}
	return true;
}