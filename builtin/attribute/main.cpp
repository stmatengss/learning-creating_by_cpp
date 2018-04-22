#include <iostream>
#include <cstdio>
#include <chrono>

using namespace std;

void test () {
	const int iter_num = 100000;
	long sum = 0;
	for (int i = 0; i < iter_num; i ++ ) {
		if (i % 100 == 0) {
			__attribute__((cold, unused));
			sum -= i;
		} else {
			__attribute__((hot, unused));
			sum += i;
		}
	}
}

int main () {
	auto start = chrono::system_clock::now();
	test();
	auto end = chrono::system_clock::now();
	std::chrono::duration<double> diff = end-start;
	printf("[TIME]%lf\n", diff.count());
}
