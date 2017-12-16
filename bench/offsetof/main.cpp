#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <chrono>
#include <unistd.h>
#include <stddef.h>

using namespace std;

//const int iter_num = 100;
const uint64_t iter_num = 200000000ULL;
const int length = 16;
uint64_t co = 0xdeadbeaf;

struct test {
	int a[length];
};

int main() {
	auto start = chrono::system_clock::now();
	for (int i = 0; i < iter_num; i ++ ) {
		offsetof(struct test, a[i]);
	}
	auto end = chrono::system_clock::now();
	std::chrono::duration<double> diff = end-start;
	printf("[TIME]%lf\n", diff.count());
	return 0;
}
