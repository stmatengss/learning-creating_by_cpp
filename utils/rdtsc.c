#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>

static uint64_t rdtsc() {
		uint32_t lo, hi;
		__asm__ __volatile__ ("rdtsc": "=a" (lo), "=d" (hi));
		return (((uint64_t)hi << 32)| lo);
}

void test() {
		for (int i = 0; i < 10; i ++ ) {
				uint64_t begin = rdtsc();
				printf("counter: %d\n", i);
				printf("took %lu cycles\n", rdtsc() - begin);
		}
}

int main () {
		test();
		return 0;	
}
