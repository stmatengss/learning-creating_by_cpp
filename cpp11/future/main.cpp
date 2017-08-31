#include <iostream>
#include <future>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main() {
	std::future<int> f = std::async(std::launch::async, []() { //deferred
	  	cout << "+++++++" << endl;
	  	sleep(4);
		return 100;	
	});
	f.wait();
	cout << "--------" << endl;
	cout << f.get() << endl;
}
