/*************************************************************************
  > File Name: reader.c
  > Author: stmatengss
  > Mail: stmatengss@163.com 
  > Created Time: Mon Feb 13 13:57:28 2017
 ************************************************************************/

#include<stdio.h>
//reader.c  
#include <stdio.h>  
#include <string.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <errno.h>  
#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/sem.h>  
#include <sys/shm.h>  

#define R 0  
#define W 1  
#define N 1024  

//union semun {
//
//	int              val;    /* Value for SETVAL */  
//	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */  
//	unsigned short  *array;  /* Array for GETALL, SETALL */  
//	struct seminfo  *__buf;  
//};  

void pv(int semid, int op, int num)  
{

	struct sembuf buf;  
	buf.sem_num = num;  
	buf.sem_op = op;  
	buf.sem_flg = 0;  

	if (semop(semid, &buf, 1) == -1)  
	{

		perror("semop");  
		exit(-1);  
	}      
}  

int main()  
{

	int semid, shmid;  
	key_t key;  
	char *shmaddr;  

	if ((key = ftok(".", 'a')) == -1)  
	{

		perror("ftok");  
		exit(-1);  
	}  

	if ((semid = semget(key, 2, 0666 | IPC_CREAT | IPC_EXCL)) == -1)  
	{

		if (errno == EEXIST)  
		{

			semid = semget(key, 2, 0666);  
		}  
	}  
	else    //first  
	{

		union semun un;  

		un.val = 0;  
		if (semctl(semid, R, SETVAL, un) == -1)  
		{

			perror("init R");  
			exit(-1);  
		}  

		un.val = 1;  
		if (semctl(semid, W, SETVAL, un) == -1)  
		{

			perror("init R");  
			exit(-1);  
		}  
	}  

	if ((shmid = shmget(key, N, 0666 | IPC_CREAT)) == -1)  
	{

		perror("shmget");  
		exit(-1);  
	}  

	if ((shmaddr = (char *)shmat(shmid, NULL, 0)) == (char *)-1)  
	{

		perror("shmaddr");  
		exit(-1);  
	}  

	srandom(getpid());  
	while (1)  
	{

		//p(r) printf v(w)  
		pv(semid, -1, R);  
		printf("%s", shmaddr);  
		if (strncmp(shmaddr, "quit", 4) == 0)  
		{

			//v(r)  
			pv(semid, 1, R);  
			break;  
		}  
		pv(semid, 1, W);  
		sleep(random()%5+1);  
	}  

	if (shmdt(shmaddr) == -1)  
	{

		perror("shmdt");  
		exit(-1);  
	}  

	exit(0);  
}
