#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *ppp1 = "hello world";
char ppp0[] = "hello world";
extern void *_end; /* any type would do, only its address is important */

int main()
{

	void *p = calloc(10000,1);
	printf( "end:%p heap:%p rodata:%p data:%p\n", &_end, p, ppp1, ppp0 );
	sleep(10000); /* sleep to give chance to look at the process memory map */
	return 0;
}
