#include <iostream>

class A {
	public:
	A() {

	}
	int a;
	int incr_a() const {
		return a + 1;
	}
};

class B: public A {
	public:
	B() {

	}
};

class C: public A {
	public:
	C() {

	}
};

int main() {
	B *b = new B();
	C *c = new C();
	b->incr_a();
	c->incr_a();
	return 0;
}
