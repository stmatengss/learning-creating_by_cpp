#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <unordered_map>
#include <chrono>
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
typedef hash_map<uint64_t, int> h_map;

void test_hash_map() {
	h_map test;
	auto start = std::chrono::system_clock::now();
	for (int i = 0; i < iter_num; i ++ ) {
		test[i] = 0;
	}
	printf("/--Insert\n");
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end-start;
	printf("[TIME]%lf [Tput]%lf\n", diff.count(), (double)iter_num / 1000000 / diff.count());
	printf("/--Find\n");

	start = std::chrono::system_clock::now();
	for (int i = 0; i < iter_num; i ++ ) {
		test.find(i);
	}
	end = std::chrono::system_clock::now();
	diff = end-start;
	printf("[TIME]%lf [Tput]%lf\n", diff.count(), (double)iter_num / 1000000 / diff.count());

	auto it = test.find(1000000ULL);
	if (it == test.end()) {
		printf("Can not find key\n");
	}
	it = test.find(1ULL);
	cout << it->first << " " << it->second << endl;
}

void test_unorder_map() {
	u_map test;
	auto start = std::chrono::system_clock::now();
	for (int i = 0; i < iter_num; i ++ ) {
		test[i] = 0;
	}
	printf("/--Insert\n");
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> diff = end-start;
	printf("[TIME]%lf [Tput]%lf\n", diff.count(), (double)iter_num / 1000000 / diff.count());
	printf("/--Find\n");

	start = std::chrono::system_clock::now();
	for (int i = 0; i < iter_num; i ++ ) {
		test.find(i);
	}
	end = std::chrono::system_clock::now();
	diff = end-start;
	printf("[TIME]%lf [Tput]%lf\n", diff.count(), (double)iter_num / 1000000 / diff.count());

	auto it = test.find(1000000ULL);
	if (it == test.end()) {
		printf("Can not find key\n");
	}
	it = test.find(1ULL);
	cout << it->first << " " << it->second << endl;
}

const static int del_iter = 1000000;
const static int push_number = 100;

void test_clear() {
	h_map test[del_iter];
	for (int i = 0; i < del_iter; i ++ ) {
		for (int j = 0; j < push_number; j ++ ) {
			test[i][push_number] = j;
		}
	}
	auto start = std::chrono::system_clock::now();
	for (int i = 0; i < del_iter; i ++ ) {
		test[i].clear();
	}
	auto end = std::chrono::system_clock::now();
	auto diff = end-start;
	printf("[TIME]%lf [Tput]%lf\n", diff.count(), (double)del_iter / 1000000 / diff.count());
}

int main(int argc, char **argv) {
	if (argv[1][0] == '1') {
		test_unorder_map();
	} else if (argv[1][0] == '2') {
		test_hash_map();
	} else if (argv[1][0] == '3') {
		test_clear();
	} else {
		h_map test;
		test[100ULL] = 100;
		printf("%d\n", test[0ULL]);
		printf("%d\n", test[100ULL]);
	}
	return 0;
}
