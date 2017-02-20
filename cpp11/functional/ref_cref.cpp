/*************************************************************************
  > File Name: ref_cref.cpp
  > Author: stmatengss
  > Mail: stmatengss@163.com 
  > Created Time: 2017年02月18日 星期六 13时56分07秒
 ************************************************************************/

#include <functional>
#include <iostream>

void f(int& n1, int& n2, const int& n3)
{

	std::cout << "In function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
	++n1; // increments the copy of n1 stored in the function object
	++n2; // increments the main()'s n2
	//++n3; // compile error
}

int main()
{
	int n1 = 1, n2 = 2, n3 = 3;
	std::function<void()> bound_f = std::bind(f, n1, std::ref(n2), std::cref(n3));
	n1 = 10;
	n2 = 11;
	n3 = 12;
	std::cout << "Before function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
	bound_f();
	std::cout << "After function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
}

