/*************************************************************************
  > File Name: main2.cpp
  > Author: stmatengss
  > Mail: stmatengss@163.com 
  > Created Time: 2017年02月20日 星期一 17时02分36秒
 ************************************************************************/

#include<iostream>
#include<atomic>
using namespace std;

struct foo { int* a; int* b; };
std::atomic<struct foo *> foo_head[10];

int foo_array[10][10];

[[carries_dependency]] struct foo* f(int i) {

	return foo_head[i].load(memory_order_consume);
}

[[carries_dependency]] int g(int* x, int* y) {

	return kill_dependency(foo_array[*x][*y]);
}
// Translation unit B. 
//[[carries_dependency]] struct foo* f(int i);
//[[carries_dependency]] int* g(int* x, int* y);

void do_something_with(int a) {
	std::cout << a << endl;
}

int c = 3;
void h(int i) {

	struct foo* p;
	p = f(i);
	do_something_with(g(&c, p->a));
	do_something_with(g(p->a, &c));
}

int main() {
	h(2);
	return 0;
}
