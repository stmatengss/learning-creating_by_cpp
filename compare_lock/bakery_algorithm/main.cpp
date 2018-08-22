#include <atomic>
#include <thread>
#include <functional>
#include <algorithm>
#include <iostream>

using namespace std;

const int NUM_THREADS = 8;
const int ITER = 100;
bool Enter[NUM_THREADS];
int Number[NUM_THREADS];
std::thread::id Id[NUM_THREADS];
int res = 0;
std::atomic<int> a(0);

bool barkey_cmp(int x, int y) {
	if (Number[x] < Number[y])
		return true;
	if (Number[x] == Number[y] && Id[x] < Id[y])
		return true;
	return false;
}

void lock(int i) {
	Enter[i] = true;
	Number[i] = *std::max_element(Number, Number + NUM_THREADS) + 1;
	Enter[i] = false;
	for (int j = 0; j < NUM_THREADS; j ++ ) {
		while (Enter[j]);
		while ((Number[j] != 0) && barkey_cmp(j, i));
	}
}

void unlock(int i) {
	Number[i] = 0;
}

void barrier() {
	a ++;
	while (a != NUM_THREADS);
}

void run(int i) {
	Id[i] = std::this_thread::get_id();
	barrier();
	for (int t = 0; t < ITER; t ++ ) {
		lock(i);
		res += i;
		std::cout << "[NOW]"<< i << ":" << res << std::endl;
		unlock(i);
	}
}

void test() {
	std::thread th[NUM_THREADS];
	for (int i = 0; i < NUM_THREADS; i ++ ) {
		th[i] = std::thread(run, i);
	}

	for (int i = 0; i < NUM_THREADS; i ++ ) {
		th[i].join();
	}
	std::cout << "[RES]:" << res << std::endl;
}

int main() {
	test();
	return 0;
}
