#include <aio.h>
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

#define BUFSIZE 1024

int main() {
	int fd, ret;
	struct aiocb my_aiocb;

	fd = open( "file.txt", O_RDONLY );
	if (fd < 0) perror("open");

	/* Zero out the aiocb structure (recommended) */
	bzero( (char *)&my_aiocb, sizeof(struct aiocb) );

	/* Allocate a data buffer for the aiocb request */
	char *read_res = (char *)malloc(BUFSIZE + 1);
	my_aiocb.aio_buf = read_res; 
	if (!my_aiocb.aio_buf) perror("malloc");

	/* Initialize the necessary fields in the aiocb */
	my_aiocb.aio_fildes = fd;
	my_aiocb.aio_nbytes = BUFSIZE;
	my_aiocb.aio_offset = 0;

	ret = aio_read( &my_aiocb );
	if (ret < 0) perror("aio_read");

	while ( aio_error( &my_aiocb ) == EINPROGRESS ) ;

	if ((ret = aio_return( &my_aiocb )) > 0) {
		printf("%s\n", read_res);	
		/* got ret bytes on the read */
	} else {

		/* read failed, consult errno */
	}
	return 0;
}
