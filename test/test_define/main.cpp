#include <stdio.h>

#define A
#define B

int main() {

#if (defined A) && (defined B)
	printf("haha\n");
#endif
	return 0;
}
