#include <stdio.h>    
#include <stdlib.h>    
#include <string.h>   
#include <time.h>   
#include <unistd.h>   
#include <libmemcached/memcached.h>    

int main(int argc, char *argv[])   
{

	memcached_st *memc;   
	memcached_return rc;   
	memcached_server_st *servers;   

	//onnect multi server    
	memc = memcached_create(NULL);   

	servers = memcached_server_list_append(NULL, (char*)"localhost", 11211, &rc);   
//	servers = memcached_server_list_append(servers, (char*)"localhost", 30000, &rc);   

	rc = memcached_server_push(memc, servers);  
	memcached_server_free(servers);    

//	memcached_behavior_set(memc,MEMCACHED_BEHAVIOR_DISTRIBUTION,MEMCACHED_DISTRIBUTION_CONSISTENT);  
//	memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_RETRY_TIMEOUT, 20) ;  
//	memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_REMOVE_FAILED_SERVERS, 1) ;  // 同时设置MEMCACHED_BEHAVIOR_SERVER_FAILURE_LIMIT 和 MEMCACHED_BEHAVIOR_AUTO_EJECT_HOSTS   
//	memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_SERVER_FAILURE_LIMIT, 5) ;  
//	memcached_behavior_set(memc, MEMCACHED_BEHAVIOR_AUTO_EJECT_HOSTS, 1) ;  

	int time_sl = 0 ;    
	int times = 0 ;  
	while(times++<100000)  
	{

		//save data    
		const char  *keys[]= {
			"key1", "key2", "key3","8995"};   
		const  size_t key_length[]= {
			4, 4, 4, 4};   
		char *values[] = {
			"This is 1 first value", "This is 2 second value", "This is 3 third value"," this is 4 forth value"};   
		size_t val_length[]= {
			21, 22, 21, 22};  
		int i = 0;  
		for (; i < 4; i++)        
		{

			rc = memcached_set(memc, keys[i], key_length[i], values[i], val_length[i], (time_t)180,(uint32_t)0);     printf("key: %s  rc:%s\n", keys[i], memcached_strerror(memc, rc));   // 输出状态         
		}   
		i = 0;
		size_t* value_size;
		uint32_t* flag;
		memcached_return_t* error;
		for (; i < 4; i++)
		{
			char* res = memcached_get(memc, keys[i], key_length[i], value_size, flag, error);
			printf("get:%s\n", res);
		}
		printf("time: %d\n", time_sl++) ;  
		sleep(1) ;  

	}   
	//free    
	memcached_free(memc);   
	return 0;   
}
