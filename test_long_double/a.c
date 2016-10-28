#include <stdio.h>
#include <limits.h>
int main() 
{
	long double a = 1.0;
	long long i = 1;
	for (i = 1; i < 100 ;i++) 
	{
	
		printf("%d=%llf\n", i, a);
		long double tmp = a * 2.0;
		if (tmp < a) break;
		a = tmp;
	}
	printf("%d" ,sizeof(long double));
	return 0;
}
