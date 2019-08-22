#include <cstdio>
#include <cstdlib> 
#include <new>

int main() {
	int *b = new int;
	//int *a = new (std::malloc(4)) int;
	int *a = new (malloc(4)) int;
	return 0;
}
