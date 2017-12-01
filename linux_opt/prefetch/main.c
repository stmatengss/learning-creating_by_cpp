#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

#define CAP (128 * 1024 * 1024)
#define N (1024 * 1024)

int do_work(int a)
{
	int i = 0;
	for(i = 0; i < 110; i++) {
		a = a ^ i;
	}
	return a;
}

/*
 * __builtin_prefetch
 * @param:
 *   0: read, 1: write
 *   0: weak, 1: strong, 2: strongest
 * */

int main(int argc, char **argv)
{
	int prefetch = atoi(argv[1]);
	int *A = (int *) malloc(CAP * sizeof(int));
	int *Ind = (int *) malloc(N * sizeof(int));

	int i;
	for(i = 0; i < CAP; i++) {
		A[i] = i;
	}
	for(i = 0; i < N; i++) {
		Ind[i] = rand() % CAP;
	}

	printf("Finished assigning data and indices\n");

	int ans = 0;
	struct timespec start, end;
	clock_gettime(CLOCK_REALTIME, &start);

	if(prefetch) {
		for(i = 0; i < N; i ++) {
			int index = Ind[i];
			if(index != N - 1) {
				int next_index = Ind[i + 1];
				__builtin_prefetch(&A[next_index], 0, 0);
			}
			int load = A[index];
			ans += do_work(load);
		}
		printf("ans = %d\n", ans);
	} else {
		for(i = 0; i < N; i ++) {
			int index = Ind[i];
			int load = A[index];
			ans += do_work(load);
		}
		printf("ans = %d\n", ans);
	}
	clock_gettime(CLOCK_REALTIME, &end);
	printf("Time = %f\n", (end.tv_sec -start.tv_sec) + 
		(double) (end.tv_nsec - start.tv_nsec) / 1000000000);
	
}
