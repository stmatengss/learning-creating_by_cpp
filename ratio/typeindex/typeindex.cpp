/*************************************************************************
    > File Name: typeindex.cpp
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: Sun Dec 25 15:22:19 2016
 ************************************************************************/

#include<iostream>
#include<typeinfo>
#include<typeindex>
#include<unordered_map>
#include<string>

using namespace std;

class factory{
public:
	factory() {
		ref_map[typeid(int)] = "int";
		ref_map[typeid(double)] = "double";
		ref_map[typeid(string)] = "string";
		ref_map[typeid(bool)] = "bool";
		ref_map[typeid(long long)] = "long long";
	}
	~factory() {

	}
	string ref(type_index type) {
		return ref_map[type];
	}
private:
	unordered_map<type_index, string> ref_map;
};

int main() {
	factory* a = new factory();
	cout << a->ref(typeid(double)) << endl;
	cout << a->ref(typeid(int)) << endl;
	cout << a->ref(typeid(string)) << endl;
	bool b = false;
	cout << a->ref(typeid(decltype(b))) << endl;

	return 0;
}
