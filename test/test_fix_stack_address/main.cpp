#include <cstdio>

//int a __attribute__((at(0x40001000))) = 1;
//int a __attribute__((address(0x11111111))) = 1;
int a __attribute__((section("fuck"))) = 1;
char d[100];
long long f __attribute__((section("shit"))) = 1LL;
int c = 1;
int b __attribute__((section("fuck"))) = 1;
char e[100] __attribute__((section("shit")));

int main() {

	printf("%p %p %p %p %p %p\n", &a, &b, &c, d, e, &f);
	return 0;
}
