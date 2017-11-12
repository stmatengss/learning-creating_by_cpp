#include <sys/mman.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

using namespace std;

//const static int key = 10086;
const static int n_process = 4;
const static char* f = "./key";

class IPCLock {
public:
	int shmid;
	int fd;
	char *counter;
	IPCLock() {
		fd = open(f, O_CREAT | O_RDWR | O_TRUNC, 00777);
		write(fd, "", 1);
		counter = (char *)mmap(NULL, 1, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
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
		msync(counter, 1, MS_SYNC);
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
