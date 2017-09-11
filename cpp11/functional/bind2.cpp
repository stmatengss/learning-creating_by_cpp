#include <iostream>
#include <future>

using namespace std;

int g(int x) {
 	cout << x << endl;
	return x;
}

int main() {
 	auto f = [](int x) -> int {
		cout << x << endl;
	 	return x;
	};
	f(2);
	auto ff = bind(f, 5);
	cout << ff() << endl;
}
