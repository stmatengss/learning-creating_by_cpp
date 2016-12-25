/*************************************************************************
    > File Name: tuple_element.cpp
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: Sun Dec 25 14:23:05 2016
 ************************************************************************/

#include<iostream>
#include<tuple>
using namespace std;

int main() {
	tuple<int, char, string> b(2, 'b', "bc");
	decltype(b) a = make_tuple (10, 'a', "ab");
	tuple_element<0, decltype(a)>::type first = get<0>(b);
	cout << first << endl;
	return 0;
}
