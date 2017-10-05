#include <memory>
#include <iostream>

using namespace std;

int main() {
	shared_ptr<int> a(new int(10));
	shared_ptr<int> b = a;
	shared_ptr<int> c = a;
	cout << a.use_count() << endl;
	cout << *a.get() << endl;
	*b.get() = 20;
	cout << *a.get() << endl;
	b.reset();
	cout << a.use_count() << endl;
	
	return 0;
}
