#define DECLARE_CLASS_CREATE(class_name) \
static CObject* CreateClass## class_name ();

#define IMPL_CLASS_CREATE(class_name) \
static CObject* CreateClass## class_name (){ \
	return new class_name; \
};

#include <algorithm>

using namespace std;

int main() {
	int a = 2;
	IMPL_CLASS_CREATE(a) b = 3;
	cout << b << endl;
	return 0;
}