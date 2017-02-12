/*************************************************************************
    > File Name: sem.c
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: 2017年01月15日 星期日 22时32分23秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

sem_t sem;

void *foo(void *arg) {
	printf("sem_wait:foo\n");
	sem_wait(&sem);
	printf("sem_wait\n");
	while(1) {

	}
}

void *bar(void *arg) {
	printf("sem_post:bar\n");
	sem_post(&sem);
	printf("sem_wait\n");
	while(1) {

	}
}

int main() {
	
	int res;
	pthread_t a;
	void *thread_res;

	res = sem_init(&sem, 0 , 0);
	if (res != 0) {
		perror("failed\n");
	}

	printf("sem_init\n");

	pthread_create(&a, NULL, foo, NULL);

	printf("foo\n");
	sleep(5);
	printf("sleep\n");

	pthread_create(&a, NULL, bar, NULL);

	while(1) {

	}

	return 0;
}

