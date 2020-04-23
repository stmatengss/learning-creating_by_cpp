#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define FILE_LEGNTH (128 * 1024 * 1024)
#define ITER_NUM (512 * 1024 * 1024)
//#define USE_MADV

int main() {
	
	srand(time(NULL));

	int fd = open("./test", O_RDWR);
	if (-1==fd) {
		perror("open error");
		return 0;
	}

	ftruncate(fd, FILE_LEGNTH);

	void* p = mmap(NULL, FILE_LEGNTH, PROT_READ, MAP_SHARED, fd, 0);
	if (MAP_FAILED==p) {
		perror("map error");
		return 0;
	}

#ifdef USE_MADV
	madvise(p, FILE_LEGNTH, MADV_RANDOM);
#endif
	int sum = 0;
	for (int i = 0; i < ITER_NUM; i ++ ) {
		size_t offset = rand() % (FILE_LEGNTH - 16);
		sum += *(int *)(p + offset);
	}

	return 0;
}
