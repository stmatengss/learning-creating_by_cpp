/*************************************************************************
    > File Name: signal1.c
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: Sun Jan 22 16:31:13 2017
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<signal.h>

int inter() {
	printf("Int Begin\n");
	sleep(4);
	printf("Int End\n");
}

int main() {
	signal(SIGINT, inter);
	printf("Begin\n");
	sleep(8);
	printf("End\n");
	return 0;
}
