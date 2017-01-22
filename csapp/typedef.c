/*************************************************************************
    > File Name: typedef.c
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: 2016年12月28日 星期三 20时23分37秒
 ************************************************************************/
#include <stdio.h>

#define N 2
typedef int fix_matrix[N][N];

int fix_ele(fix_matrix A, size_t i, size_t j) {
	return A[i][j];
}

int var_ele(size_t n, int A[n][n], size_t i, size_t j) {
	return A[i][j];
}

int main () {
	fix_matrix a = {
		{
			1,2
		},
		{
			3,4
		}
	};
	printf("%d", fix_ele(a, 0, 0));
	printf("%d", var_ele(N, a, 0, 0));
	return 0;
}
