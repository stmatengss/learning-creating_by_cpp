#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>

#define TEST 100000000

void test(int is_true) {
		int sum = 0;
		int i;
		for (i = 0; i < TEST; i ++ ) {
				if (__builtin_expect(i == 0, is_true)) {
						sum += i;	
				}
		}
}


void test2() {
		static int a = 1;
		int b = 1;
		fprintf(stdout, "%d\n", __builtin_constant_p(1) );
		fprintf(stdout, "%d\n", __builtin_constant_p(b) );
}

void test3() {
		void *t = __builtin_alloca(100000000);
		fprintf(stdout, "%ld\n", strlen(t));
}

void test4() {
		int a = 0;
		double b;
		fprintf(stdout, "%d\n", __builtin_types_compatible_p(typeof(a), int) );
}

void test5() {
		void *x = __builtin_assume_aligned (NULL, 32, 8);
}

void test6() {
		uint64_t p = 0x123456LL;
		fprintf(stdout, "num: %lld\n", __builtin_bswap64(p));
}

void test7() {
		int delta = 1000;
		int *a = (int *)malloc(TEST * sizeof(int) );
		int b = 0;
		int i, j;
		for (i = 0; i < delta; i ++ ) {
				for (j = i; j < TEST; j += delta ) {
						b += a[j];
						__builtin_prefetch(a[j + delta], 0, 3);
				}

		}
}

void test8() {
		printf("%f\n",  __builtin_powif(20.0, 4));
}

int main() {
		int i;
//		test2();
//		test3();
		struct timeval begin, end;		
		gettimeofday(&begin, NULL);
		test8();
		gettimeofday(&end, NULL);
		printf("likely time is : %ld\n", (end.tv_sec - begin.tv_sec) * 1000000 + end.tv_usec - begin.tv_usec);
		/*
		for (i = 0; i < 3; i ++ ) {

				struct timeval begin, end;		
				gettimeofday(&begin, NULL);
				test(0);
				gettimeofday(&end, NULL);
				printf("likely time is : %ld\n", (end.tv_sec - begin.tv_sec) * 1000000 + end.tv_usec - begin.tv_usec);

				gettimeofday(&begin, NULL);
				test(i + 1);
				gettimeofday(&end, NULL);
				printf("unlikely time is : %ld\n", (end.tv_sec - begin.tv_sec) * 1000000 + end.tv_usec - begin.tv_usec);
		}
		*/
		return 0;
}
