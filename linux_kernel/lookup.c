/*************************************************************************
    > File Name: lookup.c
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: Sat Jan 21 23:21:56 2017
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

extern char** environ;

int main () {

	char **env = environ;
	while(*env) {
		printf("%s\n", *env++);
	}
	return 0;
}
