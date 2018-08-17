#include <iostream>
#include <exception>

using namespace std;

class my_exception: public exception {
	virtual const char * what() const throw() {
		cout << "Exception" << endl;
		return "";
	}
};

int main() {
	cout << "Complex" << endl;
	// A complex one
	try {
		throw my_exception();
	} catch(exception &e) {
		e.what();
	}
	cout << "Simple" << endl;
	// A simple one
	try {
		throw;
	} catch(...) {
		cout << "Exception" << endl;
	}
}
