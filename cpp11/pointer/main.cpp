#include <memory>
#include <iostream>

using namespace std;

int main() {
	shared_ptr<int> p0(new int(5));
	shared_ptr<int> p1(new int[5]);
	shared_ptr<int> p2 = p1;
	
	cout << (typeid( p1.get()).name() ) << endl;
	p1.get()[2] = 10;
	cout << p2.get()[2] << endl;
	p2.get()[3] = -5;
	cout << p1.get()[3] << endl;

	p1.reset();
	p2.reset();
	return 0;
}
