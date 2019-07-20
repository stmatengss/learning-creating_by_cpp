#include <mutex>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

mutex a;
mutex b;

//#define USE_RAII

#ifdef USE_RAII

int main() {

	thread A([](){
		unique_lock<mutex> la(a, std::defer_lock);
		this_thread::sleep_for(chrono::seconds(2));
		unique_lock<mutex> lb(b, std::defer_lock);
		lock(la, lb);
		cout << "OK A" << endl; 
	});

	thread B([](){
		unique_lock<mutex> lb(b, std::defer_lock);
		this_thread::sleep_for(chrono::seconds(1));
		unique_lock<mutex> la(a, std::defer_lock);
		lock(la, lb);
		cout << "OK B" << endl; 
	});

	A.join();
	B.join();

	return 0;
}

#else 

int main() {

	thread A([](){
		lock_guard<mutex> la(a);
		this_thread::sleep_for(chrono::seconds(1));
		lock_guard<mutex> lb(b);
		cout << "OK A" << endl; 
	});

	thread B([](){
		lock_guard<mutex> lb(b);
		this_thread::sleep_for(chrono::seconds(1));
		lock_guard<mutex> la(a);
		cout << "OK B" << endl; 
	});

	A.join();
	B.join();

	return 0;
}

#endif
