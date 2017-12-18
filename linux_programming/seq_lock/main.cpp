#include <atomic>
#include <thread>

using namespace std;

//int sequence = 0;
atomic<int> sequence(0);
atomic_flag locked = ATOMIC_FLAG_INIT;
int data;

void lock() {
	while(locked.test_and_set(memory_order_acquire));
}

void unlock() {
	locked.clear(memory_order_release); 	
}

void inc() {
	sequence ++;
}

void write_lock() {
	lock();
	inc();
}

void write_unlock() {
	inc();
	unlock();
}

int read_lock() {
	volatile int ret;
	do {
		ret = sequence;
	} while (ret & 1);
	return (int)ret;
}

bool read_unlock(int start) {
	return sequence	!= start;
}

const int iter_num = 10;
const int thread_num = 10;

void reader() {
	int seq;
	int ret;
	for (int i = 0; i < iter_num; i ++ ) {

		do {
			seq = read_lock();
			ret = data; // CRITICAL SECTION XXX
		} while(read_unlock(seq));
		printf("[R]%d\n", ret);
	}	

}

void writer() {
	for (int i = 0; i < iter_num; i ++ ) {
		write_lock();
		data = i; // CRITICAL SECTION XXX
		printf("[w]%d\n", data);
		write_unlock();
	}
}

int main() {
	thread readers[thread_num];
	for (int i = 0; i < thread_num; i ++ ) {
		readers[i] = thread(reader);
	}
	writer();
	for (int i = 0; i < thread_num; i ++ ) {
		readers[i].join();
	}
	return 0;
}
