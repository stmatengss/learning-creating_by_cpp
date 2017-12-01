#include <stdio.h>
#include <unistd.h>
#include <sys/poll.h>

int main() {
	pollfd fds[2];
	int ret;

	fds[0].fd = STDIN_FILENO;
	fds[0].events = POLLIN;

	fds[1].fd = STDOUT_FILENO;
	fds[1].events = POLLOUT;

	ret = poll(fds, 2, 5000);

	if (fds[0].revents & POLLIN) 
		printf("stdin is read\n");

	if (fds[1].revents & POLLOUT)
		printf("stdout is write\n");

	return 0;
}
