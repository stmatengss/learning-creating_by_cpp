/*************************************************************************
    > File Name: array.cpp
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: Sun Dec 25 01:02:32 2016
 ************************************************************************/
#include <iostream>
#include <array>

using namespace std;

int main() {
	array<int, 5> myarray = {
		1,2,3,4,5
	};
	for (auto i: myarray) {
		cout << i <<endl;
	}
	for (int i = 0; i < 5; i ++ ) {
		cout << myarray.at(i) <<endl;
	}
	cout << myarray.front() << endl;
	cout << myarray.back() << endl;
	array< array<int, 2>, 2> a = {{	{1,2}, {4,5} }};
	a.emplace(get<0>(a));
	cout << a.max_size() <<endl;
	cout << endl;
	for (auto i: get<0>(a))
		cout << i << endl;
	return 0;
}
