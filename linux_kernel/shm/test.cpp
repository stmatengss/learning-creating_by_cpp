#include <atomic>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <netdb.h>
#include <cstdio>
#include <pthread.h>

using namespace std;

#define SHM_KEY 1001

#define SHM_FLAG IPC_CREAT | 0666

#define SHM_SIZE 10000

int main(int argc, char **argv) {

		pthread_mutex_t mutex;
		int m_id = shmget(SHM_KEY, SHM_SIZE, SHM_FLAG);
		atomic_char *mem = (atomic_char *)shmat(m_id, 0, 0);
		printf("%c\n", argv[1][0]);
		char out;
		for (int i = 0; i < 1000000; i ++ ) {
//				mem[0] = argv[1][0];
				pthread_mutex_lock(&mutex);
				mem[0].store(argv[1][0]);
				out = mem[0].load();
				pthread_mutex_unlock(&mutex);
				if (i % 100000 == 0) printf("%c: %c\n", argv[1][0], out);
		}
		return 0;
}
