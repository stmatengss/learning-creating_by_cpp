/*************************************************************************
    > File Name: mymalloc.c
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: 2016年12月26日 星期一 18时28分05秒
 ************************************************************************/
#ifdef COMPILETIME
#include <stdio.h>
#include <malloc.h>
/* malloc wrapper function */
void *mymalloc(size_t size)
{

	void *ptr = malloc(size);
	printf("malloc(%d)=%p\n",
			(int)size, ptr);
	return ptr;
}
/* free wrapper function */
void myfree(void *ptr)
{

	free(ptr);
	printf("free(%p)\n", ptr);
}
#endif
