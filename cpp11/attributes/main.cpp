/*************************************************************************
    > File Name: main.cpp
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: 2017年02月20日 星期一 16时57分39秒
 ************************************************************************/

#include<iostream>
using namespace std;

[[ noreturn ]] void f() {
	throw "error";
}

int main() {
	f();
	return 0;
}
