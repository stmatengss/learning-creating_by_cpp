#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

using namespace std;

//int a = 1;

class test {
	int a;
	int b;
};

int main() {
#if 2 
	printf("%p\n", sbrk(0));
	char *mem = (char *)malloc(10);
	printf("%p\n", sbrk(0));
	char *mem2 = (char *)malloc(10);
	printf("%p\n", sbrk(0));
//	char *mem3 = new char[58];
	printf("%p\n", sbrk(0));
	char *mem4 = (char *)malloc(64);
//	printf("%p\n", &a); 
	int b = int(12); 
	printf("%p\n", &b); 
	printf("%p\n", mem); 
	printf("%p\n", mem2); 
//	printf("%p\n", mem3); 
	printf("%p\n", mem4); 
	printf("%p\n", sbrk(0));
	printf("%p\n", sbrk(10));
	printf("%p\n", sbrk(0));
#else
	printf("%p\n", sbrk(0));
	char *mem = (char *)malloc(10);
	printf("%p\n", mem); 
	printf("%p\n", sbrk(0));
#endif

	return 0;
}
