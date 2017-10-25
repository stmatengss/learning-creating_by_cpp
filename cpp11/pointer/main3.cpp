#include <memory>
#include <iostream>

using namespace std;

int main( ) {
	uintptr_t a = uintptr_t(new char[100]); 
//	uintptr_t a = static_cast<uintptr_t>(new char[100]); 
	return 0;
}
