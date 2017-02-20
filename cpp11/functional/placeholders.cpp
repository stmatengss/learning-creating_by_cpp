/*************************************************************************
  > File Name: placeholders.cpp
  > Author: stmatengss
  > Mail: stmatengss@163.com 
  > Created Time: 2017年02月18日 星期六 14时03分10秒
 ************************************************************************/
#include <functional>
#include <string>
#include <iostream>

void goodbye(const std::string& s)
{

	std::cout << "Goodbye " << s << '\n';
}

class Object {

	public:
		void hello(const std::string& s)
		{

			std::cout << "Hello " << s << '\n';
		}
};

int main(int argc, char* argv[])
{

	typedef std::function<void(const std::string&)> ExampleFunction;
	Object instance;
	std::string str("World");
	ExampleFunction f = std::bind(&Object::hello, &instance, 
			std::placeholders::_1);

	//equivalent to instance.hello(str)
		f(str);
	f = std::bind(&goodbye, std::placeholders::_1);

	// equivalent to goodbye(str)
	f(str);    
	return 0;
}
