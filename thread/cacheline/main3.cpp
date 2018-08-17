#include <thread>
#include <cstdio>

using namespace std;

__thread int counter;
const int iter_num = 1000000000;

void test1() {
	for (int i = 0; i < iter_num; i ++ ) {
		counter ++;
	}
	printf("%d", counter);
}

void test2() {
	for (int i = 0; i < iter_num; i ++ ) {
		counter ++;
	}
	printf("%d", counter);
}

int main() {
	thread t1(test1);
	thread t2(test2);
	t1.join();
	t2.join();
	return 0;
}
