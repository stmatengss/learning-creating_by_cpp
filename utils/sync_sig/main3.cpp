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
//		fd = open(f, O_CREAT | O_RDWR , S_IRUSR | S_IWUSR);
//		ff = fopen(f, "wb+");
//		fread(num, 4, 1, ff);
		ifstream in(f);
//		out.read(counter, 1);
		in >> counter;
		in.close();
		printf("[A]%d\n", (int)*counter);
		counter[0] = counter[0] + 1;
		printf("[B]%d\n", (int)*counter);
		ofstream out(f);
		out << counter;
//		out.write(counter, 1);
//		fwrite(num, 4, 1, ff);
		out.close();
		//wait();
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
	return 0;
}
