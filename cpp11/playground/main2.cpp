#include <stdio.h>

using namespace std;

//#define ALIGN

#ifdef ALIGN

struct alignas(16) A {
	long a;
};

#else

struct A {
	long a;
};

#endif

int main() {
	A li[2];
	printf("%p\n", &li[0].a);
	printf("%p\n", &li[1].a);
	return 0;
}
