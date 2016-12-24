/*************************************************************************
    > File Name: decltype.cpp
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: Sun Dec 25 01:27:53 2016
 ************************************************************************/

#include<iostream>
#include<array>
using namespace std;

template <typename T>
struct test {
	array<T, 4> testA;
	test() {
		testA = {
			1,2,3,4
		};
	};
};

template<class U, class V>
auto mul(U u, V v) -> decltype(u * v) {
	return u * v;
}

int main() {
	test<int>* a = new test<int>();
	for (auto i: a->testA) {
		cout << i << endl;
	}
	decltype(a->testA) b = {
		4,3,2,1
	};
	for (auto i: b) {
		cout << i <<endl;
	}
	cout << mul (100, -2) <<endl;
	return 0;
}
