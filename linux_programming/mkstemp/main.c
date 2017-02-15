#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int write_temp_file(char * buffer, size_t len) {
		printf("write\n");
		char filename[] = "/tmp/ffffff";
		int fd = mkstemp(filename);
		unlink(filename);
		printf("Template file name: %s\n", filename);
		write(fd,&len, sizeof(len));
		write(fd, buffer, len);
		return fd;
}	

char read_temp_file(int fd, size_t* len) {
		printf("read\n");
		char* buffer;
		lseek(fd, 0, SEEK_SET);
		read(fd, len, sizeof(size_t));
		buffer = (char *) malloc(*len);
		read(fd, buffer, *len);
		close(fd);
		return buffer;
}

int main() {
		char buffer[] = "Hello temp file";
		int fd = write_temp_file(buffer, strlen(buffer));
		int len = 0;
		char* result = read_temp_file(fd, &len);
		printf("Len:%d\nContent:%s\n", len, result);
		free(result);
		return 0;
}
