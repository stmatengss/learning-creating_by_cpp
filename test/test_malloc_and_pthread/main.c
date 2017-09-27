/*************************************************************************
 *     > File Name: test_fuck.c
 *         > Author: stmatengss
 *             > Mail: stmatengss@163.com 
 *                 > Created Time: 2017年08月24日 星期四 13时32分29秒
 *                  ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

const int num = 4;

void *foo(void *arg) {


	int counter = (int )arg;
	printf("[%d]%p\n", counter,  (char *)sbrk(0));
	char *data = (char *)malloc(16);
	printf("[%d]%p\n", counter, data);
}

int main() {

	pthread_t threads[num];

	printf("[host]%p\n", (char *)sbrk(0));
	sbrk(1LL<<30);
	printf("[host]%p\n", (char *)sbrk(0));
	sbrk(-1LL<<30);

	for (int i = 0; i < num; i ++) {

		pthread_create(&threads[i], NULL, foo, (void *)i);
	}

	for (int i = 0; i < num; i ++) {

		pthread_join(threads[i], NULL);
	}

	return 0;
}
