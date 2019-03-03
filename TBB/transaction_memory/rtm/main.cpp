#include <immintrin.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	
	auto res = _xtest();

	if (res) {
		printf("During Transaction\n");
	} else {
		printf("Not During Transaction\n");
	}

	int *g = (int *)malloc(sizeof(int));
	
	while (1) { // keep trying
		int status = _xbegin(); // set status = -1 and start transaction
		if (status == _XBEGIN_STARTED) { // status == XBEGIN_STARTED == -1
			(*g) ++; // non atomic increment of shared global variable

			res = _xtest();

#if 0
			if (res) {
				printf("During Transaction\n");
			} else {
				printf("Not During Transaction\n");
			}
#endif
			_xend(); // end transaction

			if (res) {
				printf("During Transaction\n");
			} else {
				printf("Not During Transaction\n");
			}
			break; // break on success
		} else { //
			_xabort(0xFF);	
		} //
	}
}
