#include <stdio.h>
#include <papi.h>

int main(void) {
	long begin = PAPI_get_real_nsec();
	printf("%ld\n", begin);
	long t1 = PAPI_get_real_usec();
	printf("%ld\n", t1);
	return 0;
}
