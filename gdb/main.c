/*************************************************************************
  > File Name: main.c
  > Author: stmatengss
  > Mail: stmatengss@163.com 
  > Created Time: 2017年02月10日 星期五 21时49分45秒
 ************************************************************************/

#include <stdio.h>

int nGlobalVar = 0;

int tempFunction(int a, int b)
{

	printf("tempFunction is called, a = %d, b = %d \n", a, b);
	return (a + b);
}

int main()
{

	int n;
	n = 1;
	n++;
	n--;

	nGlobalVar += 100;
	nGlobalVar -= 12;

	printf("n = %d, nGlobalVar = %d \n", n, nGlobalVar);

	n = tempFunction(1, 2);
	printf("n = %d", n);

	return 0;
}
