#include <numaif.h>
#include <string.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>

int main() {
	int id = shmget(123, 10, IPC_CREAT | IPC_EXCL | 0666 );
   	char *buffer = shmat(id, NULL, 0);

	unsigned long nodemask = (1<<0); // init core id
	int ret = mbind(buffer, 10, MPOL_BIND, &nodemask, 32, 0);	
}
