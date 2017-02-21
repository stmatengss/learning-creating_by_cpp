/*************************************************************************
  > File Name: main2.cpp
  > Author: stmatengss
  > Mail: stmatengss@163.com 
  > Created Time: 2017年02月21日 星期二 11时42分26秒
 ************************************************************************/
#include <iostream>
#include <boost/coroutine/all.hpp>

typedef boost::coroutines::asymmetric_coroutine< int >::pull_type pull_coro_t;
typedef boost::coroutines::asymmetric_coroutine< int >::push_type push_coro_t;


void runit(push_coro_t & sink1)
{

	std::cout << "1" << std::endl;
	sink1(10);
	std::cout << "2" << std::endl;
	sink1(20);
	std::cout << "3" << std::endl;
	sink1(30);
	std::cout << "4" << std::endl;
}

int main(int argc, char * argv[])
{

	{

		pull_coro_t source(runit);
		while (source)
		{

			int ret = source.get();
			std::cout << "ret: " << ret << std::endl;
			source();
		}
	}

	std::cout << "\nDone" << std::endl;

	return 0;
}
