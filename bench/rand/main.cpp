#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>

using namespace std;

//const int iter_num = 100;
const int iter_num = 10000000;

int main() {
	auto start = chrono::system_clock::now();
	for (int i = 0; i < iter_num; i ++ ) {
		int a = rand();
//		printf("num=%d\n", a);
	}
	auto end = chrono::system_clock::now();
	std::chrono::duration<double> diff = end-start;
	printf("[TIME]%lf\n", diff.count());
	return 0;
}
