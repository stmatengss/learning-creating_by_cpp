#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FILE_NAME "./test"
#define FILE_LEN 1024 * 1024

int main() {
	int fd = open(FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC,
			    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1) {
		perror("ERROR\n");
	}
	fallocate(fd, FALLOC_FL_KEEP_SIZE, 0, FILE_LEN);
	close(fd);
	return 0;
}
