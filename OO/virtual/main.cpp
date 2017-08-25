#include <iostream>

using namespace std;

class Base {
	public:
		virtual void f (float x) {
			cout << "Base:f:float=" << x << endl;
		}
		void g(float x) {
			cout << "Base:g:float=" << x << endl;
		}	
		void h(float x) {
			cout << "Base:g:float=" << x << endl;
		}	
};
class Derived: public Base {
	public:
		virtual void f (float x) {
			cout << "Derived:f:float=" << x << endl;
		}
		void g(int x) {
			cout << "Derived:g:float=" << x << endl;
		}	
		void h(float x) {
			cout << "Derived:g:float=" << x << endl;
		}	
};

int main() {

	Derived d;
	Base *pb = &d;
	Derived *pd = &d;

	pb->f(3.14f);
	pd->f(3.14f);

	pb->g(3.14f);
	pd->g(3.14f);
	
	pb->h(3.14f);
	pd->h(3.14f);

	return 0;
}
