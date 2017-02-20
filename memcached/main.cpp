/*************************************************************************
    > File Name: main.c
    > Author: stmatengss
    > Mail: stmatengss@163.com 
    > Created Time: 2017年02月17日 星期五 13时58分30秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <libmemcached/memcached.h>

using namespace std;

inline void CPE(int error_code) {
	if (error_code != 0) {
		cout << "error" << endl;

	}
}

void run() {
	memcached_server_st *servers = NULL;
	memcached_st *memc = memcached_create(NULL);

	char *key = "foo";
	char *value = "bar";

	if (memc == NULL) {
		CPE(1);
	}

	cout << "get" << endl;
	memcached_return_t rc = memcached_set(memc, key, strlen(key), 
			value, strlen(value), (time_t)0, (uint32_t)0);

	if (rc != MEMCACHED_SUCCESS) {
		cout << memcached_strerror(memc, rc) << endl;
		CPE(1);
	}

	size_t* v_len;
	char* res = memcached_get(memc, key, strlen(key), v_len, NULL, NULL);

	cout << res << endl;
}

int main() {
	run();
}
