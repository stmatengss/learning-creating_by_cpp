#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <unordered_map>
#include <ext/hash_map>

using namespace std;
using namespace __gnu_cxx;

const static int iter_num = 1 << 26;

/*
void test_hash_map {

	hash_map<uint64_t, int> hm;
	for (int i = 0; i < iter_num; i ++ ) {
		hm[static_cast<uint64_t>(i)] = 1;		
	}
}
*/
typedef unordered_map<uint64_t, int> u_map;
//typedef hash_map<uint64_t, int> u_map;

void test_unorder_map() {
	u_map test;
	for (int i = 0; i < (1 << 10); i ++ ) {
//		test.insert(u_map::value_type(static_cast<uint64_t>(i), 0));
//		test.insert(u_map::value_type(i, 0));
		test[i] = 0;
	}
	printf("Insert\n");
	for (int i = 0; i < iter_num; i ++ ) {
		test.find(i % (1 << 11));
	}
	auto it = test.find(1000000ULL);
	if (it == test.end()) {
		printf("Can not find key\n");
	}
}

int main(int argc, char **argv) {
	if (argv[1][0] == '1') {
		test_unorder_map();
	} else if (argv[1][0] == '2') {

	} else if (argv[1][0] == '3') {

	} else {

	}
	return 0;
}
