#include <future>
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;

#define forceinline __attribute__((always_inline))

#define HAS_LOCK
#define USE_LOCK

typedef volatile uint32_t lock_t;

lock_t lock_val = 0; 

forceinline static void cpu_relax () {
	asm("pause");
}

static inline void lock() {
	size_t wait = 1;

	while (1) {

		if (__sync_bool_compare_and_swap(&lock_val, 0, 1)) {
			return;
		}
		
		for (int i = 0; i < wait; i ++ ) {
			cpu_relax();
		}

		while (lock_val) {
			wait *= 2;
			for (int i = 0; i < wait; i ++ ) {
				cpu_relax();
			}
		}
	}
}

static inline void unlock() {
	lock_val = 0;
	__sync_synchronize();
}

//atomic_int counter = atomic_int(0);

atomic<int> begin_counter(0);

int counter = 0;
int thread_num = 2;
const int limit_iter = 10000000;


/*
forceinline static void yield_sleep() {
	using namespace std::chrono;
	std::this_thread::sleep_for(500us);
}

forceinline static void backoff_exp(size_t &cur_max_iter) {

	thread_local std::uniform_int_distribution<size_t> dist;
	thread_local std::minstd_rand gen(std::random_device{}());
	const size_t spinIters = dist(gen, decltype(dist)::param_type{0, curMaxIters});
	for (size_t i = 0; i < spinIters; i ++)
		cpu_relax(); 
}
*/

void f() {
	begin_counter ++;

	while(begin_counter != thread_num);

	auto start = std::chrono::system_clock::now();

	for (int i = 0; i < limit_iter; i ++ ) {
		// 		asm("LOCK");
#ifdef USE_LOCK
#ifdef HAS_LOCK
		lock();
#endif
		counter ++;
#ifdef HAS_LOCK
		unlock();
#endif
#else
		__sync_fetch_and_add(&lock_val, 1);
#endif
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end-start;
	printf("[TIME]%lf [Tput]%lf\n", diff.count(), (double)limit_iter / 1000000 / diff.count());
}

int main(int argc, char** argv) {
	thread_num = atoi(argv[1]);
	thread a[thread_num];

	for (int i = 0; i < thread_num; i ++ ) {
		a[i] = thread(f);
	}

	for (int i = 0; i < thread_num; i ++ ) {
		a[i].join();
	}

	cout << counter << endl;
}
