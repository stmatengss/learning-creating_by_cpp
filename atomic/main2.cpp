/*************************************************************************
    > File Name: main2.cpp
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: Fri Jan  6 20:27:30 2017
 ************************************************************************/

#include<iostream>
#include <vector>
#include <atomic>
#include <thread>
using namespace std;

atomic<int> foo(0);
atomic<int> bar(0);

void set_foo(int x) {

	foo = x;
}

void print_foo() {

	while (foo == 0 ) {

		this_thread::yield();
	}
	cout << "foo: " << foo << endl;
}

void copy_foo_to_bar() {
	while(foo == 0) {
		this_thread::yield();
	}
	bar = static_cast<int>(foo);
}

int main () {
	thread first(print_foo);
	thread second(set_foo, 10);
	thread third(copy_foo_to_bar);
	first.join();
	second.join();
	third.join();
	return 0;
}

