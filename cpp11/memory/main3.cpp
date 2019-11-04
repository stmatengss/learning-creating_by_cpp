#include <cstdio>
#include <memory> 

int main() {
	std::size_t a = alignof(int);
	void *p;
	std::align(a, sizeof(int), p, 100);
	return 0;
}
