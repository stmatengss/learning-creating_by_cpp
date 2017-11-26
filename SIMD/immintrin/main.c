#include <immintrin.h>
#include <stdio.h>

int main() {
	float out[8];
	float a[8] = {0.0,1.0,2.0,3.0,4.0,-5.0,6.0,7};
	__m256 test1 =  _mm256_load_ps(&a[0]);
	float b[8] = {0.0,1.0,-2.0,-3.0,-4.0,5.0,6.0,7};
	__m256 test2 =  _mm256_load_ps(&a[0]);
	__m256 res = _mm256_add_ps(test1, test2);
	float *p = (float *)&res;
	int i;
	for (i = 0; i < 8; i ++ ) {
		printf("%lf\n", p[i]);
	}

	return 0;
}
