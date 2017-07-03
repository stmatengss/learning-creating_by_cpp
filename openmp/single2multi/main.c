/*************************************************************************
    > File Name: main.c
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: 2017年07月03日 星期一 20时11分58秒
 ************************************************************************/

#include<stdio.h>
#include <omp.h>

#define ITER 100

int fuck[ITER * 10];

void foo(int num) {

	for (int i = 0; i < num * ITER; i ++ ) {
		fuck[i] += i; 
	}
}

int main() {

#pragma omp parallel num_threads(4) 
	{
		int tid = omp_get_thread_num();
#pragma omp for nowait
		for (int i = 0; i < 1000; i ++ ) {
			foo(tid);
		}
		printf("[%d] Round 1 is over!\n", tid);

#pragma omp for nowait
		for (int i = 0; i < 1000; i ++ ) {
			foo(tid);
		}
		printf("[%d] Round 2 is over!\n", tid);
#pragma omp master
		{
			printf("Barrier 1 is there\n");
		}
#pragma omp barrier
#pragma omp for nowait
		for (int i = 0; i < 1000; i ++ ) {
			foo(tid);
		}
		printf("[%d] Round 3 is over!\n", tid);
#pragma omp single
		printf("[%d] Thread rush to the end\n", tid);
	}

	return 0;
}
