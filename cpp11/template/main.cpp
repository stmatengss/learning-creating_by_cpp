#include <iostream>

template<typename... Ts>
void magic(Ts... args) {
	std::cout << sizeof...(args) << std::endl;
}

int main() {
	magic(); // 输出0
	magic(1); // 输出1
	magic(1, ""); // 输出2
	return 0;
}
