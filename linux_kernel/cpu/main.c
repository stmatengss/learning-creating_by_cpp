#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <string.h>
#include <sys/types.h>

inline int set_cpu(int i) {
		cpu_set_t mask;
		CPU_ZERO(&mask);
		CPU_SET(i, &mask);

		printf("thread: %u, i = %d\n", pthread_self(), i);
		if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask)) {
				return -1;
		}
		return 0;
}

void *fun(void *i) {
		if (set_cpu(*(int *)i)) {
				printf("set cpu erro\n");
		}
		long long a = 0;
		while (1) {
				a += rand();
		}
		return NULL;
}

int main() {
		int i;
		int cpu_num = sysconf(_SC_NPROCESSORS_CONF);

		printf("cpu_num = %d\n", cpu_num);

		int tmp[10];
		pthread_t Thread[10];

		for (i = 0; i < 10; i ++) {
				tmp[i] = i;
				pthread_create(&Thread[i], NULL, fun, &tmp[i]);
		}

		for (i = 0; i < 10; i ++) {
				pthread_join(Thread[i], NULL);
		}

		return 0;
}

