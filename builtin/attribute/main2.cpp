#include <iostream>

#define DEPRECATED __attribute__((deprecated))

DEPRECATED void test () {
	// DO something
}

int main() {
	test();
	return 0;
}
