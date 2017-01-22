/*************************************************************************
    > File Name: pipe.c
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: Sun Jan 22 18:02:08 2017
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(void)
{

	int fd[2], nbytes;
	pid_t childpid;
	char string[] = "Hello, world!\n";
	char readbuffer[80];
	pipe(fd);
	if((childpid = fork()) == -1)
	{

		perror("fork");
		exit(1);
	}
	if(childpid == 0)
	{

		/* 子进程关闭管道的读句柄 */
		close(fd[0]);
		/* 通过写句柄向管道写入信息 */
		write(fd[1], string, strlen(string));
		_exit(0);
	}
	else
	{

		/* 父进程关闭管道的写句柄 */
		close(fd[1]);
		/* 通过读句柄从管道读出信息 */
		nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
		printf("Received string: %s", readbuffer);
	}
	return(0);
}
