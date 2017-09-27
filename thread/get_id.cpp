#include <thread>
#include <iostream>

int main() {
	std::cout << std::this_thread::get_id() << std::endl;
	return 0;
}
