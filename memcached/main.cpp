/*************************************************************************
  > File Name: main.c
  > Author: stmatengss
  > Mail: stmatengss@163.com 
  > Created Time: 2017年02月17日 星期五 13时58分30秒
 ************************************************************************/

#include <cstdio>
#include <stdlib.h>    
#include <string.h>   
#include <time.h>   
#include <unistd.h>
#include <iostream>
#include <libmemcached/memcached.h>

using namespace std;

inline void CPE(int error_code) {
	if (error_code != 0) {
		cout << "error" << endl;

	}
}

const int NUM_WROKER = 4;

void run() {
	memcached_server_st *servers = NULL;
	
	memcached_st *memc = memcached_create(NULL);
	memcached_return rc;


	for (int i = 0; i < NUM_WROKER; i ++ ) {
		cout << "build " << i << " server" << endl;
		servers = memcached_server_list_append(servers, (char*)"localhost", 11211 + i, &rc);
		if (rc != MEMCACHED_SUCCESS) {
			cout << memcached_strerror(memc, rc ) << endl;
		}
	}

	rc = memcached_server_push(memc, servers);
	cout << "push server" << endl;
	if (rc != MEMCACHED_SUCCESS) {
		cout << memcached_strerror(memc, rc) << endl;
		CPE(1);
	}
	memcached_server_free(servers);

	memcached_behavior_set(memc,MEMCACHED_BEHAVIOR_DISTRIBUTION,MEMCACHED_DISTRIBUTION_CONSISTENT);  
	memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_RETRY_TIMEOUT, 20) ;  
	//  memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_REMOVE_FAILED_SERVERS, 1) ;  // 同时设置MEMCACHED_BEHAVIOR_SERVER_FAILURE_LIMIT 和 MEMCACHED_BEHAVIOR_AUTO_EJECT_HOSTS   
	memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_SERVER_FAILURE_LIMIT, 5) ;  
	memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_AUTO_EJECT_HOSTS, 1) ;  

	const char* key = (char*)"1234";
	const char* value = (char*)"bar";

	if (memc == NULL) {
		CPE(1);
	}

	cout << "set:" << strlen(key) << strlen(value) << endl;
	rc = memcached_set(memc, key, strlen(key), 
			value, strlen(value), (time_t)0, (uint32_t)0);

	if (rc != MEMCACHED_SUCCESS) {
		cout << memcached_strerror(memc, rc) << endl;
		CPE(1);
	}
	cout << "get_success" << endl;

	size_t* v_len;
	uint32_t* flags;
	int key_len = strlen(key);
	memcached_return_t* error;
	char* res = memcached_get(memc, key, key_len, v_len, flags, error);

	if (rc != MEMCACHED_SUCCESS) {
		cout << memcached_strerror(memc, rc) << endl;
		CPE(1);
	}

	cout << string(res) << endl;
}

int main() {
	run();
}
