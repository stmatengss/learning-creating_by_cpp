#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

#define CAP (128 * 1024 * 1024)
#define N (32 * 1024 * 1024)
//#define INLINE 

long sum = 0;

#ifdef INLINE
__attribute__((always_inline)) void do_work(int a) 
{
	sum += a;
} 
#else 
void do_work(int a)
{
	sum += a;
}
#endif

/*
 * __builtin_prefetch
 * @param:
 *   0: read, 1: write
 *   0: weak, 1: strong, 2: strongest
 * */

int main(int argc, char **argv)
{
	printf("Finished assigning data and indices\n");

	int ans = 0;
	struct timespec start, end;
	clock_gettime(CLOCK_REALTIME, &start);
	
	int i;
	for (i = 0; i < 100000000; i ++ ) {
		do_work(i);
	}
	
	clock_gettime(CLOCK_REALTIME, &end);
	printf("Sum = %ld\n", sum);
	printf("Time = %f\n", (end.tv_sec -start.tv_sec) + 
		(double) (end.tv_nsec - start.tv_nsec) / 1000000000);
	
}
