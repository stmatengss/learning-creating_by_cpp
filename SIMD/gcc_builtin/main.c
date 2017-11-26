#include <stdio.h>

typedef int v4si __attribute__ ((vector_size (16)));

typedef unsigned int uint;

int main() {
	v4si a, c;
	v4si b = {3,2,1,4};
	v4si d = {3,2,5,1};
	long l;

	a = b + 1;    /* a = b + {1,1,1,1}; */
	uint *p = (uint *)&a;
	int i;
	for (i = 0; i < 4; i ++ )
		printf("%u\n", p[i]);
	a = 2 * b;    /* a = {2,2,2,2} * b; */
	for (i = 0; i < 4; i ++ )
		printf("%u\n", p[i]);
	p = (uint *)&c;
	c = a > d;
	for (i = 0; i < 4; i ++ )
		printf("%u\n", p[i]);
	c = a == d;
	for (i = 0; i < 4; i ++ )
		printf("%u\n", p[i]);
	return 0;
}
