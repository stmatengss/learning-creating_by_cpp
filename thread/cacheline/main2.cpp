#include <thread>
#include <cstdio>

using namespace std;

struct Counter {
	int counter;
} __attribute__((aligned(64)));


Counter counter[2];
const int iter_num = 100000000;

void test1() {
	for (int i = 0; i < iter_num; i ++ ) {
		counter[0].counter ++;
	}
	printf("%d", counter[0].counter);
}

void test2() {
	for (int i = 0; i < iter_num; i ++ ) {
		counter[1].counter ++;
	}
	printf("%d", counter[1].counter);
}

int main() {
	thread t1(test1);
	thread t2(test2);
	t1.join();
	t2.join();
	return 0;
}
