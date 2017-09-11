#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {
	int fd = open("test", O_RDWR, 0666);
	char *mem = (char *)mmap(NULL, 1, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	mem[0] = 'b';
	fsync(fd);
	exit(1);
//	msync(mem, 1, MS_SYNC);
		
	return 0;
}
