/*************************************************************************
    > File Name: getopt.c
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: Mon Jan  9 10:43:06 2017
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>

int main(int argc, char **argv) {
	int result;
	char option;
	while ((result = getopt(argc, argv, "ab:c::")) != -1) {
		switch(result) {
			case 'a':
				option = 'a';
				break;
			case 'b':
				option = 'b';
				break;
			case 'c':
				option = 'c';
				break;
			default:
				printf("error");
		}
		printf("%c %c %s\n", option, optopt, optarg);
	}
	return 0;
}
