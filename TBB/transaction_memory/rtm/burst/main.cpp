#include <immintrin.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <thread>

using namespace std;

int counter = 0;
const int iter_num = 100000000;
const int th_num = 4;

void test() {

	int *g = &counter; 
	int abort_counter = 0;

	for(int i = 0; i < iter_num; i ++ ) { // keep trying
		int status = _xbegin(); // set status = -1 and start transaction
		if (status == _XBEGIN_STARTED) { // status == XBEGIN_STARTED == -1
			(*g) ++; // non atomic increment of shared global variable
			_xend(); // end transaction
		} else { //
			abort_counter ++;
		} //
	}
	printf("%d\n", abort_counter);
}


int main() {
	
	thread th[th_num];

	for (int i = 0; i < th_num; i ++ ) {
		th[i] = thread(test);
	}


	for (int i = 0; i < th_num; i ++ ) {
		th[i].join();
	}

	printf("[counter]%d\n", counter);
}
