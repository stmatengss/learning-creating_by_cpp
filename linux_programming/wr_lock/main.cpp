#include <iostream>
#include <cstdio>
#include <atomic>
#include <thread>

using namespace std;

atomic_flag locked_g = ATOMIC_FLAG_INIT;
atomic_flag locked_r = ATOMIC_FLAG_INIT;
int counter = 0;

int num;

const static int iter_num = 100;
const static int reader_num = 10;

void lock_g() {
	while(locked_g.test_and_set(memory_order_acquire));
}

void unlock_g() {
	locked_g.clear(memory_order_release);
}

void lock_r() {
	while(locked_r.test_and_set(memory_order_acquire));
}

void unlock_r() {
	locked_r.clear(memory_order_release);
}

void begin_read() {
	lock_r();
	counter ++;
	if (counter == 1) lock_g();
	unlock_r();
}

void end_read() {
	lock_r();
	counter ++;
	if (counter == 0) unlock_g();
	unlock_r();
}

void begin_write() {
	lock_g();
}

void end_write() {
	unlock_g();
}

void reader() {
	for (int i = 0; i < iter_num; i ++ ) {
		begin_read();
		printf("[R]%d\n", num);
		end_read();
	}
}

void writer() {
	for (int i = 0; i < iter_num; i ++ ) {
		begin_read();
		num ++;
		printf("[W]%d\n", num);
		end_read();
	}
}
int main() {
	thread write(reader);
	thread read[reader_num];

	for (int i = 0; i < reader_num; i ++ ) {
		read[i] = thread(reader);
	}

	write.join();
	for (int i = 0; i < reader_num; i ++ )
		read[i].join();
	return 0;
}
