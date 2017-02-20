/*************************************************************************
  > File Name: pthread_arg.c
  > Author: stmatengss
  > Mail: stmatengss@163.com 
  > Created Time: 2017年02月16日 星期四 11时13分40秒
 ************************************************************************/

#include<stdio.h>
#include <pthread.h>
#include <string.h>

struct thread_data{

	int  thread_id;
	int  sum;
	char *message;
};

#define NUM_THREADS 10

struct thread_data thread_data_array[NUM_THREADS];

void *PrintHello(void *threadarg)
{

	struct thread_data *my_data;
	my_data = (struct thread_data *) threadarg;
	int taskid = my_data->thread_id;
	int sum = my_data->sum;
	char *hello_msg = my_data->message;
	printf("taskid:%d, sum:%d, message:%s\n", taskid, sum, hello_msg);
}

int main (int argc, char *argv[])
{

	pthread_t threads[NUM_THREADS];
	int t;
	int sum = 0;
	char* msg = "helloworlda";
	for (t = 0; t < NUM_THREADS; t ++ ) {
		thread_data_array[t].thread_id = t;
		sum += t;
		thread_data_array[t].sum = sum;
		thread_data_array[t].message = (char *) malloc(sizeof(char) * 12);
//		thread_data_array[t].message = msg;
		memcpy(thread_data_array[t].message, msg, 10);
		thread_data_array[t].message[10] += t;
		int rc = pthread_create(&threads[t], NULL, PrintHello, 
				(void *) &thread_data_array[t]);
		if (rc){

			printf("ERROR; return code from pthread_create() is %d\n", rc);
			return 1;
		}
	}
	return 0;
}
