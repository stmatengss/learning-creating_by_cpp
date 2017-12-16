#include <stdio.h>
#include <stdint.h>

int main() {

	char *a = (char *)malloc(4);
	printf("%p\n", a);
	printf("%p\n", (char *)(((uint64_t)a) / 64 * 64) );
}
