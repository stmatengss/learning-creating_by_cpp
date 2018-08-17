#include <thread>
#include <cstdio>

using namespace std;

int counter[2];
const int iter_num = 1000000000;

void test1() {
	for (int i = 0; i < iter_num; i ++ ) {
		counter[0] ++;
	}
	printf("%d\n", counter[0]);
}

void test2() {
	for (int i = 0; i < iter_num; i ++ ) {
		counter[1] ++;
	}
	printf("%d\n", counter[1]);
}

int main() {
	thread t1(test1);
	thread t2(test2);
	t1.join();
	t2.join();
	return 0;
}
