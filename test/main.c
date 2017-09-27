#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

int main() {

	char *a = (char *)(intptr_t)sbrk(0);

	sbrk(16);

	memset(a, '+', 16);

	printf("%p\n", a);

	char *b = (char *)malloc(16);

	char *c = (char *)malloc(16);

	memset(b, '-', 16);
	
	memset(c, '*', 16);

	printf("%p\n", b);
	printf("%p\n", c);

	int offset = c - a;

	printf("%s\n", a);
	printf("%s\n", b);
	printf("%s\n", a + (c - a));
}
