#include <stdio.h>

#if 0 
int test(int a, int b) {
	return a;
}
#else
int test(int a, int b __attribute__((unused))) {
	return a;
}
#endif

int main() {
	return 0;
}
