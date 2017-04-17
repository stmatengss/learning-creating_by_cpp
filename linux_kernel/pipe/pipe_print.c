#include <stdlib.h>
#include <unistd.h>
#define MAXLINE 80

int main() {
		int n;
		int fd[2];
		pid_t  pid;
		char line[MAXLINE];
		if (pipe(fd) < 0) {
				exit(1);
		}
		pid = fork();
		if (pid > 0) {
			close(fd[0]);
			write(fd[1], "hello\n", 6);
		} else {
			close(fd[1]);
			n = read(fd[0], line, MAXLINE);
			write(STDOUT_FILENO, line, n);
		}
		return 0;
}
