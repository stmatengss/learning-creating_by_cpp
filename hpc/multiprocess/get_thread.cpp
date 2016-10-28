#include <omp.h>
#include <iostream>
#include <cstdio>

using namespace std;

int main() {
	int nthreads, tid;
#pragma omp parallel
	//cout<<"fuck_u_man"<<endl;
	printf("Fuck, You!\n");	
	omp_set_num_threads(4);
	/* Fork a team of threads with each thread having a private tid variable */
#pragma omp parallel private(tid)
	{

		/* Obtain and print thread id */
		tid = omp_get_thread_num();
		printf("Hello World from thread = %d\n", tid);

		/* Only master thread does this */
		if (tid == 0) 
		{
			nthreads = omp_get_num_threads();
			printf("Number of threads = %d\n", nthreads);
		}

	}  
	return 0;
}
