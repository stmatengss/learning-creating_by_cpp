#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <chrono>

using namespace std;

//const int iter_num = 100;
const uint64_t iter_num = 200000000ULL;
const int length = 8;
uint64_t co = 0xdeadbeaf;

int main() {
	char *mem = new char[iter_num * length];
	auto start = chrono::system_clock::now();
	for (int i = 0; i < iter_num; i ++ ) {
		co += 1;
//		memcpy(mem + i * length, &co, length);
		*(uint64_t *)(mem + i * length) = co;
//		printf("num=%d\n", a);
	}
	auto end = chrono::system_clock::now();
	std::chrono::duration<double> diff = end-start;
	printf("[TIME]%lf\n", diff.count());
	return 0;
}
