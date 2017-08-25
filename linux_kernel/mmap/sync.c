#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	int fd, err;
	char *mm;
	fd = open("test.txt", O_RDWR);
	mm = (char *)mmap()
}
