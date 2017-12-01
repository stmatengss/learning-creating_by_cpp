#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

struct test {
	char op;
	uint64_t key;
	uint64_t value;
};

test a[10];

int main() {
	printf("%d\n", offsetof(test, key));
	printf("%d\n", offsetof(test, op));
	printf("%d\n", offsetof(test, value));
	printf("%p\n", &a[0]);
	printf("%p\n", &a[1]);
	return 0;
}
