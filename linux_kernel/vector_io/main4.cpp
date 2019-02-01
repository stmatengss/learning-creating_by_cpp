#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <random>
#include <chrono>
#include <time.h>

using namespace std;

#define N 32
#define LEN 100000
const int iter = 1000000;

int main(int argc, char **argv) {
	srand( (unsigned)time( NULL ) );
 	char buf[LEN + 10000];
		
	int batch_size = atoi(argv[1]);

	struct iovec bufs[N];

	auto start = std::chrono::system_clock::now();	

	for (int j = 0; j < iter; j ++ ) {

		for (int i = 0; i < batch_size; i ++ ) {
			bufs[i].iov_base = (void *)&buf[i + rand() / LEN];
			bufs[i].iov_len = 2;
		}

		if (writev(STDIN_FILENO, bufs, N) == -1) {
			perror("error, fuck!");
			exit(-1);
		}
	}

	auto end = chrono::system_clock::now();
	std::chrono::duration<double> diff = end-start;
	printf("[Time]%lf\n", diff.count());
	printf("[TPUT]%lf\n", 1.0 * iter / diff.count());

	for (int i = 0 ; i < 3; i ++ ) {

	 	printf("%c\n", buf[i]);
	}
 	
	return 0;
}
