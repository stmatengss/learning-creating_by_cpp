#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/uio.h>

#define NUMBUFS 3

int
main(int argc, char *argv[])
{
	char buf1[10];
	char buf2[10];
	char buf3[10];

	struct iovec bufs[NUMBUFS];

	bufs[0].iov_base = (void*) buf1;
	bufs[0].iov_len = 3;

	bufs[1].iov_base = (void*) buf2;
	bufs[1].iov_len = 3;

	bufs[2].iov_base = (void*) buf3;
	bufs[2].iov_len = 3;

	if (-1 == readv(STDIN_FILENO, bufs, NUMBUFS))
	{
		perror("writev()");
		exit(EXIT_FAILURE);
	}

	printf("out: %s", buf1);
	printf("out: %s", buf2);
	printf("out: %s", buf3);

	return 0;
}
