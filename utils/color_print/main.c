#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */

void red_printf(const char *format, ...)
{	
	va_list args;

	char buf1[1000], buf2[1000];
	memset(buf1, 0, 1000);
	memset(buf2, 0, 1000);

    va_start(args, format);
	vsnprintf(buf1, 1000, format, args);

	snprintf(buf2, 1000, "\033[31m%s\033[0m", buf1);
	printf("%s", buf2);
	//write(2, buf2, 1000);
    va_end( args );
}

#define ITERS (1024 * 1024 * 1024)
int main()
{
	int i, sum = 23;
	for(i = 0; i < ITERS; i++) {
		sum *= i;
	}
	red_printf("sum %d %d %d\n", 1, 2, 3, 4);
}

