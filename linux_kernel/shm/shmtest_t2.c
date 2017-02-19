/*************************************************************************
  > File Name: shmtest.c
  > Author: stmatengss
  > Mail: stmatengss@163.com 
  > Created Time: Mon Feb 13 00:57:12 2017
 ************************************************************************/

#include <stdio.h> 
#include <sys/shm.h> 
#include <sys/stat.h> 
#include <unistd.h>
#include <errno.h>

int main () 
{

	int segment_id; 
	char* shared_memory; 
	struct shmid_ds shmbuffer; 
	int segment_size; 
	const int shared_segment_size = 0x6400; 

	key_t shm_key = ftok("hello.txt", 'R');

	sleep(1);
//	printf( "error: %s\n", strerror( errno ));
	segment_id = shmget (shm_key, 0, 0600); 

//	printf( "error: %s\n", strerror( errno ) );
	shared_memory = (char *) shmat(segment_id, 0, 0);
//	printf( "error: %s\n", strerror( errno ) );


	shmctl(segment_id, IPC_STAT, &shmbuffer);
//	printf( "error: %s\n", strerror( errno ) );
	segment_size = shmbuffer.shm_segsz;

	printf ("father shared memory attached at address %p\n", shared_memory); 
	printf("father segment size: %d\n", segment_size);
	printf("father memory: %s\n", shared_memory);

	shmdt(shared_memory);

	sleep(1);
	shared_memory = (char *) shmat(segment_id, 0, 0);

	printf ("father shared memory reattached at address %p\n", shared_memory); 
	sprintf(shared_memory, "Fuck U");
	shmdt(shared_memory);

	shmctl(segment_id, IPC_RMID, 0);
	return 0; 
}
