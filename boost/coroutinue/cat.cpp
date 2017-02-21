/*************************************************************************
    > File Name: cat.cpp
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: 2017年02月21日 星期二 11时44分26秒
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/coroutine/all.hpp>

using namespace std;

const int buffer_size = 1024;

typedef boost::coroutines::asymmetric_coroutine< string >::pull_type pull_coro_t;
typedef boost::coroutines::asymmetric_coroutine< string >::push_type push_coro_t;

char* file_name;

void read_file(push_coro_t& back) {
	cout << "file:" << string(file_name) << endl;
	ifstream fin(file_name, ios::in);

	if (!fin) {
		return;
	}

	string res;

	while(getline(fin, res)) {
//		auto num = back.get();
//		cout << num;
		back(res);	
	}
	fin.clear();
	fin.close();
	
}

void run_cat() {
	pull_coro_t sink(read_file);
	int counter = 0;
	while(sink) {
		cout << counter++ << ":";
		//sink(to_string(counter++));
		cout << sink.get() << endl;
		sink();
	}
}

int main(int argv, char** argc) {

	if (argv == 2) {
		file_name = argc[1];
	}
	run_cat();
	return 0;
}
