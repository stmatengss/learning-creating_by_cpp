/*************************************************************************
    > File Name: main3.cpp
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: 2017年01月04日 星期三 10时57分30秒
 ************************************************************************/

#include <stdexcept>
#include<iostream>

void print(const char *s) {
	while(*s) {
		if (*s == '%' && *(++s) != '%')
			throw std::runtime_error("invalid");
		std::cout << *s++;
	}
}

template<typename T, typename... Args>
void print(const char *s, T value, Args... args) {
	while(*s) {
		if (*s == '%' && *(++s) != '%' ) {
			std::cout << value;
			print(*s ? ++s : s, args...);
			return ;
		}
		std::cout << *s++;
	}
	throw std::logic_error("extra arguments");
}

int main() {
	std::string s = "number"; 
	print("%s is %d", s, 123);
}
