/*************************************************************************
    > File Name: keyword.cpp
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: 2017年02月08日 星期三 14时14分22秒
 ************************************************************************/

#include <iostream>
#include <pthread.h>
#include <unistd.h>


using namespace std;

__thread int var = 5;

void* fun1(void* arg) {

	cout << ++ var << endl;
}

void* fun2(void* arg) {

	sleep(1);
	cout << ++ var << endl;
}

int main() {

	pthread_t pid1, pid2;
	static __thread int temp = 10;
	pthread_create(&pid1, NULL, fun1, NULL);
	pthread_create(&pid2, NULL, fun2, NULL);
	pthread_join(pid1, NULL);
	cout << "after:" << var << endl;
	pthread_join(pid2, NULL);
	cout << "after:" << var << endl;
	cout << temp << endl;
	return 0;
}
