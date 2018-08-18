#include <numaif.h>
#include <numa.h>
#include <string.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>

#define ITER_NUM 1000000000
//#define USE_LOCAL

void test() {
	if(numa_available() < 0){
		printf("System does not support NUMA API!\n");
	}
	int n = numa_max_node();
	int size = 1024*1024;
	printf("There are %d nodes on your system\n", n + 1);
	int i;
	assert(numa_run_on_node(0) == 0);
#ifdef USE_LOCAL
	printf("LOCAL\n");
	char *str = numa_alloc_local(ITER_NUM);
#else
	printf("OTHER\n");
	char *str = numa_alloc_onnode(ITER_NUM, 1);
#endif
	assert(str != NULL);
    for (i = 0; i < ITER_NUM; i ++ ) {
		str[i] = (char)(i % 256);
	}
}

int main() {
	test();
}
