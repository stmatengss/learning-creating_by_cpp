/*************************************************************************
  > File Name: unordered_map.cpp
  > Author: stmatengss
  > Mail: stmatengss@163.com 
  > Created Time: Sun Dec 25 13:27:40 2016
 ************************************************************************/

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>

using namespace std;

typedef unordered_map<string, string> Map;

template <typename T>
T merge(T a, T b) {
	a.insert(b.begin(), b.end());
	return a;
}

int main(){
	Map a({
			{
			"1","2"
			},
			{
			"3","4"
			}
			});
	cout << a["1"] <<endl;
	Map b(a);
	//	b["fuck"] = "hi";
	//	b["shit"] = "man";
	for (auto& x: a) {
		cout << x.first << x.second << endl;
	}
	for (auto& x: merge<Map>(a, b)) {
		cout << x.first << x.second << endl;
	}
	Map c(merge(a,b));
	for (auto i = c.begin(); i != c.end(); ++ i) {
		cout << i->first << i->second <<endl;
	}
	cout << endl;
	cout << c.bucket_count() << endl;
	cout << c.load_factor() << endl;
	cout << c.max_load_factor() << endl;
	cout << endl;
	int d[] = {
		1,2,3,4,5
	};
	vector<int> e(d, d + 5);
	for (auto i = e.begin(); i != e.end(); ++ i) {
		cout << *i <<endl;
	}
	std::unordered_map<std::string,std::string> mymap = {

		{
			"house","maison"},
		{
			"apple","pomme"},
		{
			"tree","arbre"},
		{
			"book","livre"},
		{
			"door","porte"},
		{
			"grapefruit","pamplemousse"}
	};

	unsigned n = mymap.bucket_count();

	std::cout << "mymap has " << n << " buckets.\n";
	mymap.emplace("hello", "shit");
	for (unsigned i=0; i<n; ++i) {

		std::cout << "bucket #" << i << " contains: ";
		for (auto it = mymap.begin(i); it!=mymap.end(i); ++it)
			std::cout << "[" << it->first << ":" << it->second << "] ";
		std::cout << "\n";
	}
	return 0;
}

