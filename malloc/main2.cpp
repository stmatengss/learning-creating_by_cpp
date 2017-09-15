#include <iostream>
#include <jemalloc/jemalloc.h>

using namespace std;

#define N 50000000
#define SIZE 4

char *a[N];

int main() {
 	for (int i = 0; i < N; i ++ ) {
	 	a[i] = (char *)malloc(SIZE);	
		a[i][SIZE - 1] = 'a';
	}
 	return 0;
}
