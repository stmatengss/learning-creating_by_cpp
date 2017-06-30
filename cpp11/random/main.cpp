/*************************************************************************
    > File Name: main.cpp
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: 2017年06月30日 星期五 14时24分55秒
 ************************************************************************/

#include<iostream>
#include <random>

using namespace std;

int main() {
	std::random_device rd;
	for (auto i = 0; i < 10; i ++ ) {
		std::cout << rd() << std::endl;
	}
	return 0;
}

