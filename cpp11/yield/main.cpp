#include <iostream>
#include <chrono>
#include <thread>
#include <atomic> 
// "busy sleep" while suggesting that other threads run 
// for a small amount of time
void little_sleep(std::chrono::microseconds us)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start + us;
    do {
        std::this_thread::yield();
    } while (std::chrono::high_resolution_clock::now() < end);
}
 
const int iter_num = 10;
const int th_num = 4;

std::atomic<int> counter(0);

void test(int index) {
	// Wait
	counter ++;
	while (counter != th_num);
	// Run
	for (int i = 0; i < iter_num; i ++ ) {
		std::this_thread::yield();
		printf("%d\n", index);
	}
}

int main()
{
	std::thread th[th_num];
	for (int i = 0; i < th_num; i ++ ) {
		th[i] = std::thread(test, i);
	}

	for (int i = 0; i < th_num; i ++ ) {
		th[i].join();
	}
	/*
    auto start = std::chrono::high_resolution_clock::now();
 
    little_sleep(std::chrono::microseconds(100));
 
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    std::cout << "waited for "
              << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()
              << " microseconds\n";
	*/
}
