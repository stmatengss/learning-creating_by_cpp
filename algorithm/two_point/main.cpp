#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#if 1

void divide(vector<int> keys, vector<int> targets) {
	int i =0, j = 0;
	int pre = 0;
	bool status = false;
	for ( ; i < keys.size(); i ++ ) {
		for ( ; j < targets.size() ; j ++ ) {
			if (targets[j] > keys[i]) {
				break;
			}	
		}
		if (pre != j) printf("%d %d %d\n", pre, j, i);
		pre = j;
	}
	if (pre != targets.size()) {
		printf("%d %d %d\n", pre, static_cast<int>(targets.size()), i);
	}
	printf("\n");
}

#else

void divide(vector<int> keys, vector<int> targets) {
	int i =0, j = 0;
	int pre;
	bool status = false;
	for ( ; i < targets.size(); i ++ ) {
		while (targets[i] >= keys[j] && j < keys.size()) {
			j ++;
			status = true;
		}
		if (status) {
			status = false;
			printf("%d %d %d\n", pre, i, j - 1);
			pre = i;
		}
	}
	if (pre != targets.size()) {
		printf("%d %d %d\n", pre, static_cast<int>(targets.size()), j);
	}
	printf("\n");
}

#endif

int main() {
	divide(vector<int>{1, 5, 9}, 
		   vector<int>{0, 1, 2, 3, 4, 6, 7, 10, 11});
	divide(vector<int>{1, 3, 5, 9}, 
		   vector<int>{0, 2, 8});
	divide(vector<int>{1}, 
		   vector<int>{2, 3, 5});
	return 0;
}
