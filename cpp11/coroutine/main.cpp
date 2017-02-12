/*************************************************************************
    > File Name: main.cpp
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: 2017年02月08日 星期三 14时52分20秒
 ************************************************************************/

#include <iostream>
#include <boost/coroutine/all.hpp>
#include <string>

using namespace std;
using namespace boost;

//typedef coroutines::coroutine<void>::push_type push_coro_t;
//typedef coroutines::coroutine<void>::pull_type pull_coro_t;
typedef coroutines::coroutine<string(string)> coro_t;


int main() {
	coro_t coro([](coro_t::caller_type& caller){
		while(caller.has_result()) {
			if (caller.get() == "exit") return;

			cout << caller.get() << endl;	
			caller("ok");
		}
	}, "this your arg");
	
	if(coro.has_result())
		cout << coro.get() << endl;
	
	coro("give you the arg");

	if(coro.has_result())
		cout << coro.get() << endl;

	coro("exit");

	if(!coro)
		cout << "finish" << endl;

	return 0;
}

