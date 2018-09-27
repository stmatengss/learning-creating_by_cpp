#include <sys/mman.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

using namespace std;

//const static int key = 10086;
const static int n_process = 4;
const static char* f = "./key";

class IPCLock {
public:
	int shmid;
	int fd;
	char counter[1];
	int num[1];
	FILE *ff;
	IPCLock() {
	}
	~IPCLock() {
		
	}
	void incre() {
		ifstream in(f);
		in >> counter;
		in.close();
		printf("[A]%d\n", (int)*counter);
		counter[0] = counter[0] + 1;
		printf("[B]%d\n", (int)*counter);
		ofstream out(f);
		out << counter;
		out.close();
	}

	void clear() {
		ofstream out(f);
		out << 0;
		out.close();
	}

	void wait() {
		while(true) {
			fd = open(f, O_RDONLY, S_IRUSR | S_IWUSR);
			read(fd, counter, 1);
			if (int(*counter) == n_process) {
				printf("break\n");
				break;
			}
			close(fd);
		}
	}
};

int main(int argc, char **argv) {
	IPCLock *lock = new IPCLock();
	lock->incre();
	lock->wait();
	return 0;
}
