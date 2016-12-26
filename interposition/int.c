/*************************************************************************
    > File Name: int.c
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: 2016年12月26日 星期一 18时25分55秒
 ************************************************************************/
#include <stdio.h>
#include <malloc.h>
int main(int argc, char** argv)
{

	int *p = malloc(32);
	free(p);
	return(0);
}
