#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

#define NUM_PKTS (1024 * 1024 * 1024)
#define SIZE 1024		/**< A[] fits in cache */
#define SIZE_ 1023

int main(int argc, char **argv)
{
	printf("Starting computing hashes\n");
	struct timespec start, end;

	int A[SIZE], i, sum = 0;

	for(i = 0; i < SIZE; i ++) {
		A[i] = i;
	}

	clock_gettime(CLOCK_REALTIME, &start);

	for(i = 0; i < NUM_PKTS; i ++) {
		//__builtin_prefetch(&A[i & SIZE_], 0, 0);
		sum += A[i & SIZE_];
	}

	clock_gettime(CLOCK_REALTIME, &end);

	double seconds = (end.tv_sec - start.tv_sec) + 
		(double) (end.tv_nsec - start.tv_nsec) / 1000000000;
	double nanoseconds = (end.tv_sec - start.tv_sec) * 1000000000 + 
		(end.tv_nsec - start.tv_nsec);

	printf("Time = %f, time prefetch = %f ns, sum = %d\n", 
		seconds, nanoseconds / NUM_PKTS, sum);

	return 0;
}
