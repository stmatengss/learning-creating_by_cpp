#include <numa.h>
#include <numaif.h>
#include <numacompat1.h>
#include <stdio.h>
#include <pthread.h>

#define TID_NUM 64
#define KB 1024
#define MB 1024 * 1024

char *mem;


void *foo() {
		
		int i = 0;
		for (;;) {
				i ++;
				mem[i % MB] = 'a' + i % 26;
		}
}

void run_full() {
		int i;
		pthread_t tid[TID_NUM];
		for (i = 0; i < TID_NUM; i ++ ) {
				pthread_create(&tid[i], NULL, foo, NULL);
		}
		for (i = 0; i < TID_NUM; i ++ ) {
				pthread_join(tid[i], NULL);
		}
}

void test() {
		printf("Max NUMA memory size is %ld\n", numa_node_size(1, NULL));
		mem = numa_alloc_onnode(MB + 4, 1);
		if (mem == NULL) {
				perror("NUMA alloc error\n");
				exit(1);
		}
		run_full();
		numa_free(mem, MB + 4);
}

int main() {
		if (numa_available() < 0) {
				printf("Do not support numa tech.\n");
				exit(1);
		}

		printf("Max NUMA node is %d\n", numa_max_node());

		nodemask_t mask;
		nodemask_zero(&mask);

		nodemask_set(&mask, 1);
		if (nodemask_isset(&mask, 1)) {
				printf("Set process to node 1 successful.\n");
		}
		numa_bind(&mask);
//		nodemask_clr(&mask, 1);
		test();
		return 0;
}
