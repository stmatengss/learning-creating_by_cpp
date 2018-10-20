#include <memory>
#include <iostream>
#include <string>
#include <vector>

int main() {
	std::allocator<int> int_alloc;
	std::cout << int_alloc.max_size() << std::endl;
	
	int *arr = int_alloc.allocate(10);
/*	
	std::vector<int>arr_vec(arr, 10);

	for (auto num: arr_vec) {
		std::cout << num << std::endl
	}
*/
	int_alloc.construct(arr, 100);
	
	std::cout << arr << " " << arr[0] << "\n";
	
	int_alloc.deallocate(arr, 10);
	std::cout << arr << " " << arr[0] << "\n";

	return 0;
}
