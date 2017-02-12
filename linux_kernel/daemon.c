/*************************************************************************
  > File Name: daemon.c
  > Author: stmatengss
  > Mail: stmatengss@163.com 
  > Created Time: Sun Jan 22 17:08:40 2017
 ************************************************************************/

#include<stdio.h>

#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <syslog.h>
#define MAXFD 64
void daemon_init(const char *pname, int facility)
{

	int i;
		pid_t pid;
	/* fork,终止父进程 */
	if (pid=fork())
		exit(0);
	/* 第一子进程 */
	setsid();
	signal(SIGHUP,SIG_IGN);
	/* fork,终止第一子进程 */
	if (pid=fork())
		exit(0);
	/* 第二子进程 */
	int daemon_proc=1;
	/* 将工作目录设定为"/" */
	chdir("/");
	/* 清除文件掩码 */
	umask(0);
	/* 关闭所有文件句柄 */
	for (i=0;i<MAXFD;i++)
	{

		close(i);
	}
	/* 打开log */
	openlog(pname,LOG_PID,facility);
}

int main() {
	daemon_init("hello", 4);
	return 0;
}
