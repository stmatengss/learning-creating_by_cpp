/*************************************************************************
    > File Name: main.c
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: 2017年07月02日 星期日 22时15分33秒
 ************************************************************************/

#include<stdio.h>
#include <sys/time.h>

#define USE_SECTION
#define LEN 10000000

int a[LEN];

int main() {
	struct timeval begin, end;


	int i;
	gettimeofday(&begin, NULL);

#ifndef USE_SECTION
	for (i = 1; i < LEN; i ++ ) {
		a[i] = a[i - 1] + i;
	}
#endif

#ifdef USE_SECTION
#pragma omp parallel sections private(i)
{
	{
		for (i = 1; i < LEN / 2; i ++ )
		{
			a[i] = a[i - 1] + i;
		}
	}
#pragma omp section
	{
		for (i = LEN / 2 + 1; i < LEN; i ++ )
		{
			a[i] = a[i - 1] + i;
		}
	}
}
#endif

	gettimeofday(&end, NULL);
	printf("time: %ld\n", 
			(end.tv_sec - begin.tv_sec) * 1000000 + (end.tv_usec - begin.tv_usec) );
}
