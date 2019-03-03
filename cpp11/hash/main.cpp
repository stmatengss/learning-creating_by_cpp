#include <iostream>
#include <iomanip>
#include <functional>
#include <string>
#include <unordered_set>

int main(int argc, char **argv) {
    std::string str(argv[1]);
    std::size_t str_hash = std::hash<std::string>{}(str);
//    std::cout << "hash(" << std::quoted(str) << ") = " << str_hash << '\n';
    std::cout << str_hash << '\n';
	return 0;
}
