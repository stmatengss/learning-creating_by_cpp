#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

using namespace std;

#define N 3

int main() {
 	char buf[N][20];

	struct iovec bufs[N];
	
	for (int i = 0; i < 3; i ++ ) {
	 	bufs[i].iov_base = (void *)buf[i];
		bufs[i].iov_len = 2;
	}

	if (readv(STDIN_FILENO, bufs, N) == -1) {
	 	perror("error, fuck!");
		exit(-1);
	}

	for (int i = 0 ; i < 3; i ++ ) {

	 	printf("%s\n", buf[i]);
	}
 	
	return 0;
}
