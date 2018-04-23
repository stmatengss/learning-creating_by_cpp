#include <ciso646>
#include <cstdio>

int main() {
	printf("%d\n", 1 and 1);
	printf("%d\n", 0 and 1);
	printf("%d\n", 0 not_eq 1);
	printf("%d\n", 3 xor 1);
	return 0;
}
