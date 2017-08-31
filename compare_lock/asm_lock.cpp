#include <future>
#include <iostream>
#include <thread>

using namespace std;

int counter = 0;
int thread_num = 2;
const int limit_iter = 10000000;

void f() {
	for (int i = 0; i < limit_iter; i ++ ) {
// 		asm("LOCK");
		counter ++;
	}
}

int main() {
	thread a[thread_num];

	for (int i = 0; i < thread_num; i ++ ) {
	 	a[i] = thread(f);
	}

	for (int i = 0; i < thread_num; i ++ ) {
	 	a[i].join();
	}

	cout << counter << endl;
}
