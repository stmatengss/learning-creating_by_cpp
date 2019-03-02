#include <immintrin.h>

int main() {
	
	int *g = (int *)malloc(sizeof(int));
	
	while (1) { // keep trying
		int status = _xbegin(); // set status = -1 and start transaction
		if (status == _XBEGIN_STARTED) { // status == XBEGIN_STARTED == -1
			(*g) ++; // non atomic increment of shared global variable
			_xend(); // end transaction
			break; // break on success
		} else { //
	
		} //
	}
}
