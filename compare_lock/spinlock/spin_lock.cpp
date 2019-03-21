#include <future>
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;

#define HAS_LOCK

typedef volatile uint32_t lock_t;

lock_t lock_val = 0; 

static inline void lock() {
    while(!__sync_bool_compare_and_swap(&lock_val, 0, 1));
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

void f() {
    begin_counter ++;

    while(begin_counter != thread_num);

    auto start = std::chrono::system_clock::now();

	for (int i = 0; i < limit_iter; i ++ ) {
// 		asm("LOCK");
#ifdef HAS_LOCK
		lock();
#endif
		counter ++;
#ifdef HAS_LOCK
		unlock();
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
