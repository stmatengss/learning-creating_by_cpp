/*************************************************************************
  > File Name: mutex1.cpp
  > Author: stmatengss
  > Mail: stmatengss@163.com 
  > Created Time: Sun Dec 25 14:58:52 2016
 ************************************************************************/

#include<iostream>
using namespace std;
#include <thread>         // std::thread
#include <mutex>          // std::mutex

std::mutex mtx;           // mutex for critical section

void print_block (int n, char c) {

	// critical section (exclusive access to std::cout signaled by locking mtx):
	mtx.lock();
	for (int i=0; i<n; ++i) {
		std::cout << c; }
	std::cout << '\n';
	mtx.unlock();
}

int main ()
{

	std::thread th1 (print_block,50,'*');
	std::thread th2 (print_block,50,'$');

	th1.join();
	th2.join();

	return 0;
}
