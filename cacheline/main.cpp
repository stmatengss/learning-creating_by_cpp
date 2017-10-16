#include <cstdio>
#include <stdint.h>

#define L1_CACHE_LINE 64
#define FULL 0xffffffff

struct A
{
	uint32_t a __attribute__ ( (aligned(L1_CACHE_LINE)) );
	uint32_t b __attribute__ ( (aligned(L1_CACHE_LINE)) );
	uint32_t c __attribute__ ( (aligned(L1_CACHE_LINE)) );
	uint32_t d __attribute__ ( (aligned(L1_CACHE_LINE)) );
};

struct B
{
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
};

inline void PRINT_BINARY_CHAR(char num) {

	for (int i = 0; i < 8; i ++ ) {

		if(num & (1<<(7-i)))
			printf("1");
		else 
			printf("0");
	}
	printf("\n");
}

inline void print_all(char *p) {
	for (int i = 0; i < L1_CACHE_LINE; i ++ ) {
		PRINT_BINARY_CHAR(*(p + i));
	}
	
}

void test1() {

	A *a = new A;
	B *b = new B;

	a->a = FULL;
	a->b = FULL;	
	a->c = FULL;	
	a->d = FULL;	

	b->a = FULL;
   	b->b = FULL;	
   	b->c = FULL;	
   	b->d = FULL;	

	print_all((char *)a);
	printf("\n");
	printf("\n");

	print_all((char *)b);
}

const int iter_num = 1<<30;
typedef A* AA;
typedef B* BB;

void test2() {
	AA *a = new AA[iter_num];
	BB *b = new BB[iter_num];

	for (int i = 0; i < iter_num; i ++) {
		a[i]->a = FULL;
		a[i]->b = FULL;
		a[i]->c = FULL;
		a[i]->d = FULL;
	}
	printf("fuck\n");

	for (int i = 0; i < iter_num; i ++) {
		b[i]->a = FULL;
		b[i]->b = FULL;
		b[i]->c = FULL;
		b[i]->d = FULL;
	}
}
	
void test3() {
	AA a = new A;
	BB b = new B;
#if 1 
	for (int i = 0; i < iter_num; i ++) {
		a->a = i;
		a->b = i;
		a->c = i;
		a->d = i;
	}

#else

	for (int i = 0; i < iter_num; i ++) {
		b->a = FULL;
		b->b = FULL;
		b->c = FULL;
		b->d = FULL;
	}
#endif
}
int main() {
	test3();
	return 0;
}
