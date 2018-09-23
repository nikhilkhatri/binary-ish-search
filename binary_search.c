#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 1000000

int comp(const void *a, const void *b);
int binary_search(int *a, int size, int data);
long time_elapsed(struct timespec start, struct timespec end);

int main(){
	// seed
	srand((int)time(NULL));
	
	int *arr;
	arr = malloc(SIZE * sizeof(int));

	// Generate [SIZE] random numbers
	int i;
	for(i=0;i<SIZE;i++){
		arr[i] = rand();
	}

	int *brr;
	brr = malloc(SIZE * sizeof(int));
	memcpy(brr, arr, SIZE*sizeof(int));
	
	qsort(brr, SIZE, sizeof(int), comp);

	// begin search - use total time

	struct timespec start_time;
	struct timespec end_time;

	// This variable exists to ensure that the compiler does not optimise out the loop
	// There are probably neater ways to do this
	int throw = 0;
	
	clock_gettime(CLOCK_REALTIME, &start_time);
	for(int j=0;j<50;j++){
		for(i=0;i<SIZE;i++){
			throw += binary_search(brr, SIZE, arr[i]);
		}
	}
	clock_gettime(CLOCK_REALTIME, &end_time);

	// print time elapsed in microseconds
	printf("time: %ld us\n", time_elapsed(start_time, end_time));
	
	// ensure compiler doesnt eliminate throw, and hence the loop
	printf("%d\n", throw);
}

long time_elapsed(struct timespec start, struct timespec end){
	// gets time elapsed in microseconds
	return ((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_nsec - start.tv_nsec)/1000;
}

int comp(const void *a, const void *b){
	// Lightweight comparator required by qsort
	return (*((int *) a)) - (*((int *) b));
}

int binary_search(int *a, int size, int data){
	/*
		Perform standard binary search
		Nothing fancy
		
		@return index in array at which data occurs, -1 if it doesnt
	*/
	int l = 0;
	int r = size-1;
	int mid;
	
	while(l <= r){
		// printf("%d, %d\n", l , r);
		mid = (l+r) / 2;
		
		if(a[mid] == data){
			return mid;
		}
		if(data > a[mid]){
			l = mid + 1;
		}
		else{
			r = mid - 1;
		}
	}
	return -1;
}
