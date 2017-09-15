#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#define N 50000000
//#define SIZE 4

char *a[N];

int main(int argc, char **argv) {

 	int SIZE = atoi(argv[1]);

 	for (int i = 0; i < N; i ++ ) {
	 	a[i] = (char *)malloc(SIZE);	
		a[i][SIZE - 1] = 'a';
	}
 	return 0;
}
