/*************************************************************************
  > File Name: shm.c
  > Author: stmatengss
  > Mail: stmatengss@163.com 
  > Created Time: 2017年01月06日 星期五 12时02分06秒
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <error.h>
#define SIZE 1024

int main()
{
	int shmid ;
	char *shmaddr ;
	struct shmid_ds buf ;
	int flag = 0 ;
	int pid ;
	shmid = shmget(IPC_PRIVATE, SIZE, IPC_CREAT|0600 ) ;
	if ( shmid < 0 )
	{
		perror("get shm  ipc_id error") ;
		return -1 ;
	}
	pid = fork() ;
	if ( pid == 0 )
	{
		shmaddr = (char *)shmat( shmid, NULL, 0 ) ;
		if ( (int)shmaddr == -1 )
		{
			perror("shmat addr error") ;
			return -1 ;
		}
		strcpy( shmaddr, "Hi, I am child process!\n") ;
		shmdt( shmaddr ) ;
		return  0;

	} else if ( pid > 0) {
		sleep(3 ) ;
		flag = shmctl( shmid, IPC_STAT, &buf) ;
		if ( flag == -1 )
		{
			perror("shmctl shm error") ;
			return -1 ;
		}
		printf("shm_segsz =%d bytes\n", buf.shm_segsz ) ;
		printf("parent pid=%d, shm_cpid = %d \n", getpid(), buf.shm_cpid ) ;
		printf("chlid pid=%d, shm_lpid = %d \n",pid , buf.shm_lpid ) ;
		shmaddr = (char *) shmat(shmid, NULL, 0 ) ;
		if ( (int)shmaddr == -1 )
		{
			perror("shmat addr error") ;
			return -1 ;
		}
		printf("%s", shmaddr) ;
		shmdt( shmaddr ) ;
		shmctl(shmid, IPC_RMID, NULL) ;
	}else{
		perror("fork error") ;
		shmctl(shmid, IPC_RMID, NULL) ;
	}
	return 0 ;
}
