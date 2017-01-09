/*************************************************************************
    > File Name: swap.c
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: 2016年12月29日 星期四 10时32分53秒
 ************************************************************************/

#include<stdio.h>

extern int buf[];

int *bufp0 = &buf[0];
int *bufp1;

void swap() {
	int temp;

	bufp1 = &buf[1];
	temp = *bufp0;
	*bufp0 = *bufp1;
	*bufp1 = temp;
}
