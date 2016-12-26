/*************************************************************************
  > File Name: intl.cpp
  > Author: stmatengss
  > Mail: stmatengss@163.com 
  > Created Time: 2016年12月26日 星期一 18时12分25秒
 ************************************************************************/
#ifdef RUNTIME
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
/* malloc wrapper function */
void *malloc(size_t size)
{

	void *(*mallocp)(size_t size);
	char *error;
	mallocp = dlsym(RTLD_NEXT, "malloc"); /* Get addr of libc malloc */
	if ((error = dlerror()) != NULL) {

		fputs(error, stderr);
		exit(1);
	}
	char *ptr = mallocp(size); /* Call libc malloc */
	printf("malloc(%d) = %p\n", (int)size, ptr);
	return ptr;
}
