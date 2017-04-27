#include <atomic>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netdb.h>
#include <cstdio>
#include <pthread.h>

using namespace std;

#define SHM_KEY 1001
#define SHM_LOCK_KEY 1002
#define SHM_FLAG IPC_CREAT | 0666
#define SHM_SIZE 10000

pthread_mutex_t *mutex;
atomic_char *mem;

int main(int argc, char **argv) {

		struct timespec nano;
		nano.tv_sec = 0;
		nano.tv_nsec = 1000;
		int m_id = shmget(SHM_KEY, SHM_SIZE, SHM_FLAG);
		mem = (atomic_char *)shmat(m_id, 0, 0);
		m_id = shmget(SHM_LOCK_KEY, sizeof (pthread_mutex_t), SHM_FLAG);
		mutex = (pthread_mutex_t *)shmat(m_id, 0, 0);
		printf("%c\n", argv[1][0]);
		char out;
		for (int i = 0; i < 100; i ++ ) {
//				mem[0] = argv[1][0];
				nanosleep(&nano, NULL);
				printf("%c running %d\n", argv[1][0], i);
				pthread_mutex_lock(&mutex[0]);
				mem[0].store(argv[1][0]);
				nanosleep(&nano, NULL);
				out = mem[0].load();
				if (argv[1][0] != out) printf("%c: fuck\n", argv[1][0]);
				pthread_mutex_unlock(&mutex[0]);
//if (argv[1][0] != out) printf("%c: %c\n", argv[1][0], out);
		}
		return 0;
}
