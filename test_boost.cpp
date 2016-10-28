#include<iostream>
#include<boost/bind.hpp>
#include<boost/scoped_ptr.hpp>

using namespace boost;
using namespace std;

//boost::scoped_ptr<std::string> p(new std::string("Hello"));

void test() {
	boost::scoped_ptr<std::string> p(new std::string("Hello"));
//	boost::auto_ptr<std::string> p(new std::string("Hello"));
	cout<<p->size()<<endl;
}

int main() {
	auto fun =[](int x,int y)->int{return x + y;};  
	int m = 1, n = 2;
	test();
	cout<<fun(2,3)<<endl;
	return 0;
}

