#include <stdio.h>
#include <iostream>
#include <stdlib.h>

struct test {
	int a;
	long b;
	char c;
};

int main() {
	test *a = (test *)0x000000ff;
	printf("%p\n", &(a->a));
	printf("%p\n", &(a->b));
	return 0;
}
