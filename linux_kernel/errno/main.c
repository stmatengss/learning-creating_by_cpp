/*************************************************************************
  > File Name: errno/main.c
  > Author: stmatengss
  > Mail: stmatengss@163.com 
  > Created Time: 2017年02月11日 星期六 13时19分04秒
 ************************************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

const char *FILE_NAME = "/tmp/this_file_does_not_exist.yarly";

int main( int argc, char **argv )
{

	int fd = 0;

	printf( "Opening %s...\n", FILE_NAME );	
	fd = open( FILE_NAME, O_RDONLY, 0644 );
	if( fd < 0 ) {

		// Error, as expected.
		perror( "Error opening file" );
		printf( "Error opening file: %s\n", strerror( errno ) );
	}

	return EXIT_SUCCESS;
}
