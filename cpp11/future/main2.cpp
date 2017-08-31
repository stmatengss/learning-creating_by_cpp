#include <iostream>
#include <future>
#include <chrono>
#include <thread>

using namespace std;

int main() {
 	future<int> f = async(launch::async, []() {
	  	this_thread::sleep_for(chrono::seconds(3));
	  	return 10;
	});

	cout << "---------" << endl;
	future_status status;
	do {
	 	status = f.wait_for(chrono::seconds(1));	
		if (status == future_status::deferred) {
		 	cout << "defer" << endl;
		} else if (status == future_status::timeout) {
		 	cout << "timeout" << endl;
		} else if (status == future_status::ready) {
		 	cout << "ready" << endl;
		}
	} while (status != future_status::ready);
	
	cout << f.get() << endl;

 	return 0;
}
