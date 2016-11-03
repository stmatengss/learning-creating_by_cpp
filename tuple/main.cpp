#include <iostream>
#include <algorithm>
#include <tuple>
#include <map>
#include <typeinfo>


using namespace std;

int main() {
	auto t = make_tuple("1123", 2, 'x');
	tuple<string, int> h("123", 12);
	// auto tp = tie(1, "12");
	cout<<(get<0>(t))<<endl;
	auto tt = get<1>(t);	
	auto cnt = tuple_size(decltype(h))::value;
	cout<<""<<endl;
	// cout<<typeid(tt).name()<<endl;
	// cout<<decltype(tt)<<endl;
	int a = 5;
	decltype(a) b = 4;
	cout<<b<<endl;

	return 0;
}