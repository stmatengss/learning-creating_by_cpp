/*************************************************************************
  > File Name: main.cpp
  > Author: stmatengss
  > Mail: stmatengss@163.com 
  > Created Time: 2017年02月21日 星期二 11时28分01秒
 ************************************************************************/

#include <iostream>
#include <boost/coroutine/all.hpp>

using namespace std;

typedef boost::coroutines::asymmetric_coroutine< void >::pull_type pull_coro_t;
typedef boost::coroutines::asymmetric_coroutine< void >::push_type push_coro_t;


void foo(push_coro_t & sink)
{

	std::cout << "1";
	sink();
	std::cout << "2";
	sink();
	std::cout << "3";
	sink();
	std::cout << "4";
}

int main(int argc, char * argv[])
{

	{

		pull_coro_t source(foo);
		while (source)
		{

			std::cout << "-";
			source();
		}
	}

	std::cout << "\nDone" << std::endl;

	return 0;
}
