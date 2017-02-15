#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void writer(const char* message, int count, FILE* stream) {
		for (; count > 0; -- count) {
				fprintf(stream, "%s\n", message);
				fflush(stream);
				sleep(1);
		}
}

void reader(FILE* stream) {
		char* buffer[1024];
		while(!feof(stream) && !ferror(stream) && fgets(buffer, sizeof(buffer), stream) != NULL) {
				fputs(buffer, stdout);
		}
}

int main() {
		int fd[2];
		pid_t pid;

		pipe(fd);

		pid = fork();

		if(pid == 0) {
				FILE* stream;
//				close(fd[1]);
				stream = fdopen(fd[0], "r");
				reader(stream);
//				close(fd[0]);
		} else {
				FILE* stream;
//				close(fd[0]);

				stream = fdopen(fd[1], "w");
				writer("Hello War\n", 5, stream);
//				close(fd[1]);
		}

}
