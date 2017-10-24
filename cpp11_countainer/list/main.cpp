#include <list>
#include <iostream>

using namespace std;

list<int> l = {
	1, 2, 3
};

int main() {
	for (auto ll = l.begin(); ll != l.end(); ll ++) {
		if (*ll == 1) {

			l.erase(ll);
			break;
		}
	}
	for (auto &ll: l) {
		cout << ll << endl;
	}
	return 0;
}
