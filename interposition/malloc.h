/*************************************************************************
    > File Name: malloc.h
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: 2016年12月26日 星期一 18时28分29秒
 ************************************************************************/
#define malloc(size) mymalloc(size)
#define free(ptr) myfree(ptr)
void *mymalloc(size_t size);
void myfree(void *ptr);
