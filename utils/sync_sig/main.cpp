#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstdio>
#include <iostream>

using namespace std;

const static int key = 10086;
const static int n_process = 4;

class IPCLock {
public:
	int shmid;
	char *counter;
	IPCLock() {
		if ((shmid = shmget(key, 1, IPC_CREAT | 0666)) < 0 ) {
			perror("shmget error");
		}	
		counter = (char *)shmat(shmid, NULL, 0);
	}
	~IPCLock() {
		
	}
	void incre() {
		if (int(*counter) == n_process) {
			*counter = 0;
			return;
		}
		printf("[A]%d\n", int(*counter));
		*counter = *counter + 1;
		printf("[B]%d\n", int(*counter));
		wait();
	}

	void wait() {
		while(true) {
			if (int(*counter) == n_process) {
				printf("break\n");
				break;
			}
		}
	}
};

int main(int argc, char **argv) {
	IPCLock *lock = new IPCLock();
	lock->incre();
	return 0;
}
