#define _GNU_SOURCE                                   
#include <unistd.h>                                   
#include <sys/syscall.h>                              
#include <sys/types.h>                                
#include <signal.h>                                   
#include <stdio.h>
                                                      
int                                                   
main(int argc, char *argv[])                          
{                                                     
    pid_t tid;                                        
                                                      
    tid = syscall(SYS_gettid);                        
	printf("%d\n", tid);
    tid = syscall(SYS_sysinfo);                        
	printf("%d\n", tid);
    tid = syscall(SYS_semget);                        
	printf("%d\n", tid);
    tid = syscall(SYS_pause);                        
    tid = syscall(SYS_tgkill, getpid(), tid, SIGHUP); 
}                                                     

