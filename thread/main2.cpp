/*************************************************************************
    > File Name: main2.cpp
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: Tue Jan  3 23:26:00 2017
 ************************************************************************/

#include <iostream>
#include <thread>
 
int main() {

     unsigned int n = std::thread::hardware_concurrency();
     std::cout << n << " concurrent threads are supported.\n";
 
}
