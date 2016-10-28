#include <cstdio>
#include <iostream>

using namespace std;

typedef unsigned char *pointer;

void show_bytes(pointer start, size_t len) {
	size_t i;
	for (i = 0; i < len; i++) {
		printf("%p\t0x%.2x\n", start + i, start[i]);
	}
	printf("\n");
}

int main() {
	int a = 15213;
	printf("int a = 15213\n");
	show_bytes((pointer) &a, sizeof(int));
	int x = -123;
	cout<<(x & (x-1))<<endl;
	cout<<(~(0u))<<endl;	
	cout<<(~(1u))<<endl;	
	cout<<(~(4u))<<endl;
	
	cout<<(~(-1))<<endl;
	
	cout<<(~(3))<<endl;
;
	return 0;
}
