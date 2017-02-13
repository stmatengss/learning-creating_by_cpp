/*************************************************************************
    > File Name: main.c
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: Mon Feb 13 14:38:30 2017
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>

void test() {
	char buffer[10];
	int fd = open("test", O_RDWR | O_CREAT, 0777);
	printf("fd:%d\n", fd);
	lseek(fd, 0, SEEK_SET);
	read(fd, buffer, 10);
	//write(fd, "fuck u man\n", 10);
	int i;
	for(i = 0; i < 10; i ++ )printf("buffer:%c\n", buffer[i]);
	printf("\n");
}

int main() {
	test();
	return 0;
}
