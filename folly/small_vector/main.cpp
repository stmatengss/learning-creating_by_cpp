#include <folly/small_vector.h>

using namespace folly;

int main() {
	small_vector<int,2> vec;
	vec.push_back(0); // Stored in-place on stack
	vec.push_back(1); // Still on the stack
	vec.push_back(2); // Switches to heap buffer.
	return 0;
}
