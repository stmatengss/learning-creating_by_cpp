#include "my_random.hpp"
#include <iostream>

using namespace std;

int main() {
	
	my_random a;
	for (int i = 0; i < 10; i ++ ) {

		cout << a.get_num(50, 100) << endl;
	}
}
