/*************************************************************************
  > File Name: main2.cpp
  > Author: stmatengss
  > Mail: stmatengss@163.com 
  > Created Time: 2017年01月04日 星期三 10时41分04秒
 ************************************************************************/

#include<iostream>
using namespace std;

template <typename...> class Foo;

template <typename A, typename B>
class Foo<A, B>
{

	public:
		Foo(A a, B b):a_(a), b_(b) {

		}
		void output() {

			std::cout << a_ << " " << b_ << '\n';
		}
		A a_;
		B b_;
};

template <typename A, typename B, typename C>
class Foo<A, B, C>
{

	public:
		Foo(A a, B b, C c):a_(a), b_(b), c_(c) {

		}
		void output() {

			std::cout << a_ << " " << b_ << " " << c_ << '\n';
		}
		A a_;
		B b_;
		C c_;
};


int main() {
	Foo<int, double, string> test(1, 123.1234, "Hello");
	test.output();
	Foo<int, double> test2(1, 123.1234);
	test2.output();
	return 0;
}
