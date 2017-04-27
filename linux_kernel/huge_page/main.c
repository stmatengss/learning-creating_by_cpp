#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

#define MB_1 (1024*1024)
#define MB_8 (8*MB_1)

char  *a;
int shmid1;

void init_hugetlb_seg()
{

		shmid1 = shmget(2, MB_8, SHM_HUGETLB
						| IPC_CREAT | SHM_R
						| SHM_W);
		if ( shmid1 < 0 ) {

				perror("shmget");
				exit(1);
		}
		printf("HugeTLB shmid: 0x%x\n", shmid1);
		a = shmat(shmid1, 0, 0);
		if (a == (char *)-1) {

				perror("Shared memory attach failure");
				shmctl(shmid1, IPC_RMID, NULL);
				exit(2);
		}
}

void wr_to_array()
{

		int i;
		for( i=0 ; i<MB_8 ; i++) {

				a[i] = 'A';
		}
}

void rd_from_array()
{

		int i, count = 0;
		for( i=0 ; i<MB_8 ; i++)
				if (a[i] == 'A') count++;
		if (count==i)
				printf("HugeTLB read success :-)\n");
		else
				printf("HugeTLB read failed :-(\n");
}

int main(int argc, char *argv[])
{

		init_hugetlb_seg();
		printf("HugeTLB memory segment initialized !\n");
		printf("Press any key to write to memory area\n");
		getchar();
		wr_to_array();
		printf("Press any key to rd from memory area\n");
		getchar();
		rd_from_array();
		shmctl(shmid1, IPC_RMID, NULL);
		return 0;
}
