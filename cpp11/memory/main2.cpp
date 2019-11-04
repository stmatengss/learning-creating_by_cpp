#include <memory>
#include <iostream>

int main() {
	//std::to_address(0xfff); // C++20
	int a = 1;

	std::cout << std::addressof(a) << "\n";
	std::cout << &a << "\n";
	return 0;
}
