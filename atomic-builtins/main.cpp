/*************************************************************************
  > File Name: main.cpp
  > Author: stmatengss
  > Mail: stmatengss@163.com 
  > Created Time: Tue Jan  3 23:47:36 2017
 ************************************************************************/

#include<iostream>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
using namespace std;


static int counter = 0;


void *test_func(void *arg)
{

	int i=0;
	for(i=0;i<20000;++i){

		__sync_fetch_and_add(&counter,1);
	}
	return NULL;
}

int main(int argc, const char *argv[])
{

	pthread_t id[20];
	int i = 0;

	for(i=0;i<20;++i){

		pthread_create(&id[i],NULL,test_func,NULL);
	}

	for(i=0;i<20;++i){

		pthread_join(id[i],NULL);
	}

	printf("%d\n",counter);
	return 0;
}
