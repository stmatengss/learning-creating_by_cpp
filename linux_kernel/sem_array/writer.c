/*************************************************************************
  > File Name: write.c
  > Author: stmatengss
  > Mail: stmatengss@163.com 
  > Created Time: Mon Feb 13 13:56:18 2017
 ************************************************************************/

#include<stdio.h>
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
	buf.sem_num = num;//信号灯编号  
	buf.sem_op = op;  //p操作或者v操作  
	buf.sem_flg = 0;  
	/*semid为信号灯集id， buf为struct sembuf结构体指针， 1表示操作信号灯的个数为1，如果大于一，表示操纵多个（则buf为struct sembuf结构体的数组指针）*/  
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
	//先启动的进程负责进行初始化，信号灯集中由两个信号灯，一个为读，一个为写  
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
		//读的信号灯值为0  
		if (semctl(semid, R, SETVAL, un) == -1)  
		{

			perror("init R");  
			exit(-1);  
		}  
		//写的信号灯值为1  
		un.val = 1;  
		if (semctl(semid, W, SETVAL, un) == -1)  
		{

			perror("init R");  
			exit(-1);  
		}  
	}  
	//创建共享内存  
	if ((shmid = shmget(key, N, 0666 | IPC_CREAT)) == -1)  
	{

		perror("shmget");  
		exit(-1);  
	}  
	//映射共享内存  
	if ((shmaddr = (char *)shmat(shmid, NULL, 0)) == (char *)-1)  
	{

		perror("shmaddr");  
		exit(-1);  
	}  

	while (1)  
	{

		//p(w) fgets v(r)  

		pv(semid, -1, W);  
		fgets(shmaddr, N, stdin);  
		pv(semid, 1, R);  
		if (strncmp(shmaddr, "quit", 4) == 0)  
			break;  
	}  

	usleep(100000);  

	if(semctl(semid, 0, IPC_RMID) == -1)  
	{

		perror("rm sem");  
		exit(-1);  
	}  

	if (shmdt(shmaddr) == -1)  
	{

		perror("shmdt");  
		exit(-1);  
	}  

	if (shmctl(shmid, IPC_RMID, NULL) == -1)  
	{

		perror("shmctl");  
		exit(-1);  
	}  

	exit(0);  
} 
