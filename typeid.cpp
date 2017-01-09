/*************************************************************************
    > File Name: typeid.cpp
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: 2016年12月31日 星期六 15时27分08秒
 ************************************************************************/

#include<iostream>
#include<typeinfo>
using namespace std;

int main() {
	int a = 100;
	string b = "123";
	cout << typeid(a).name() <<endl;
	cout << typeid(b).name() <<endl;
	cout << (typeid(a) == typeid(int)) <<endl;
	cout << (typeid(b) == typeid(string)) <<endl;
	return 0;
}
