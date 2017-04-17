/*************************************************************************
    > File Name: affinity.cpp
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: 2017年04月02日 星期日 16时32分12秒
 ************************************************************************/

#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
using namespace std;


void *test(void *in) {
	cpu_set_t cpu_set;
	int mask;
	int index = *((int *)in);
	printf("index: %d\n", index);
	CPU_ZERO(&cpu_set);
	CPU_SET(index, &cpu_set);
	pthread_setaffinity_np(pthread_self(), sizeof cpu_set, &cpu_set);
	if(CPU_ISSET(index, &cpu_set)) {
		mask = index;
	}
	printf("thread %d bitmask %d\n", index, mask);

	while(true) {

	}
}

int main() {
	int core_num = sysconf(_SC_NPROCESSORS_CONF);
	printf("cpu cores: %d\n", core_num);
	pthread_t th[core_num];
	int a[core_num];
	for(int i = 0; i < core_num; i ++) {
		a[i] = i;
		pthread_create(&th[i], NULL, test, (void *)(&a[i]) );
	}
	for(int i = 0; i < core_num; i ++) {
		pthread_join(th[i], NULL);
	}
	return 0;
}

