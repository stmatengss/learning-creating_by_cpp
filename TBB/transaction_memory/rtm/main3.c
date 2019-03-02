#include <immintrin.h>
#include <stdlib.h>

#define _xbegin() {\
        __asm__ __volatile__ (".byte 0xc7, 0xf8, 0xfa, 0xff, 0xff, 0xff":::"eax") ;\
        }

#define _xend() {\
        __asm__ __volatile__ (".byte 0x0f, 0x01, 0xd5") ;\
        }

#define _xabort(byte) {\
        __asm__ __volatile__ (".byte 0xc6, 0xf8, " #byte :::"eax") ;\
        }

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
