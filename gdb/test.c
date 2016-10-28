#include<stdio.h>

int nGlobalVar = 0;

int add(int a, int b) 
{
	printf("added is called, a=%d, b=%d\n", a, b);
	return a+b;
}

int main()
{
	int n;
	n = 1;
	n++;
	n--;

	nGlobalVar += 100;
	nGlobalVar -= 12;
	
	printf("n=%d, nGlobalVar=%d\n", n, nGlobalVar);

	n = add(1, 2);

	printf("n=%d\n", n);

	return 0;
}
