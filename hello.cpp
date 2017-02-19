/*************************************************************************
  > File Name: hello.cpp
  > Author: stmatengss
  > Mail: stmatengss@163.com 
  > Created Time: Sun Feb 19 23:01:58 2017
 ************************************************************************/

#include <boost/python.hpp>
char const* greet()
{

	return "hello, world";
}

BOOST_PYTHON_MODULE(hello)
{

	using namespace boost::python;
	def("greet", greet);
}

