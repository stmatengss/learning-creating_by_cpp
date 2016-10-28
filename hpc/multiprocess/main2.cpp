#include <c++/4.8.4/iostream>
#include <c++/4.8.4/ctime>
#include "main.h"
#include <omp.h>

using namespace std;

int main() {
	clock_t t1 = clock();
	#pragma omp parallel for
	for (int i = 0; i < 8; i++) {
		test();
	}
	std::cout<<"threads: "<<omp_get_num_threads()<<std::endl;
	clock_t t2 = clock();
	std::cout<<"time: "<<(t2 - t1)<<std::endl;
	return 0;
}
