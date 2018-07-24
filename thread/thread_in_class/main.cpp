#include <iostream>
#include <thread>

using namespace std;

class Test{
	public:
	Test(){

	}
	~Test(){

	}
	void test(int begin) {
		for (int i = begin; i < begin + 10; i ++ ) {
			cout << i << endl;
		}
	}
	void run_thread() {
		thread th(&Test::test, this, 10);
		th.join();
	}
};

int main() {
	Test *t = new Test();
	t->run_thread();
	return 0;
}
