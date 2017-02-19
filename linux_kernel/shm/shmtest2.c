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

	pid_t pid_id = fork();

	if (pid_id == 0) {
		/* Allocate a shared memory segment.  */ 
		//segment_id = shmget (IPC_PRIVATE, shared_segment_size, 
		//		IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR); 

		segment_id = shmget (shm_key, shared_segment_size, 
				IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR); 
		/* Attach the shared memory segment.  */ 
		shared_memory = (char*) shmat (segment_id, 0, 0); 
		printf ("son shared memory attached at address %p\n", shared_memory); 
		/* Determine the segment's size. */ 
		shmctl (segment_id, IPC_STAT, &shmbuffer); 
		segment_size  = shmbuffer.shm_segsz; 
		printf("lpid: %d, cpid: %d\n", shmbuffer.shm_lpid, shmbuffer.shm_cpid);
		printf ("son segment size: %d\n", segment_size); 
		/* Write a string to the shared memory segment.  */ 
		sprintf (shared_memory, "Hello, world."); 
		/* Detach the shared memory segment.  */ 
		shmdt (shared_memory); 

	 	sleep(3);	
		/* Reattach the shared memory segment, at a different address.  */ 
		shared_memory = (char*) shmat (segment_id, 0, 0); 
		printf ("son shared memory reattached at address %p\n", shared_memory); 
		/* Print out the string from shared memory.  */ 
		printf ("son memory: %s\n", shared_memory); 
		/* Detach the shared memory segment.  */ 
		shmdt (shared_memory); 

		/* Deallocate the shared memory segment.  */ 
		shmctl (segment_id, IPC_RMID, 0); 
	} else {
		sleep(1);
		printf( "error: %s\n", strerror( errno ));
		segment_id = shmget (shm_key, shared_segment_size, 
				IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	
		printf( "error: %s\n", strerror( errno ) );
		shared_memory = (char *) shmat(segment_id, 0, 0);
		printf( "error: %s\n", strerror( errno ) );
	

		shmctl(segment_id, IPC_STAT, &shmbuffer);
		printf( "error: %s\n", strerror( errno ) );
		segment_size = shmbuffer.shm_segsz;

		printf ("father shared memory attached at address %p\n", shared_memory); 
		printf("father segment size: %d\n", segment_size);
		
		shmdt(shared_memory);

		sleep(1);
		shared_memory = shmat(segment_id, 0, 0);
			
		printf ("father shared memory attached at address %p\n", shared_memory); 
		fprintf(shared_memory, "Fuck U");
		shmdt(shared_memory);

		shmctl(segment_id, IPC_RMID, 0);
	}
	return 0; 
}
