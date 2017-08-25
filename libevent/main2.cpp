#include <stdio.h>  
#include <string.h>  
#include <iostream>  
#include <sys/socket.h>      
#include <netinet/in.h>      
#include <arpa/inet.h>      
#include <netdb.h>  

#include <event.h>  
using namespace std;  

// 事件base  
struct event_base* base;  

// 读事件回调函数  
void onRead(int iCliFd, short iEvent, void *arg)  
{  
		int iLen;  
		char buf[1500];  

		iLen = recv(iCliFd, buf, 1500, 0);  

		if (iLen <= 0) {  
				cout << "Client Close" << endl;  

				// 连接结束(=0)或连接错误(<0)，将事件删除并释放内存空间  
				struct event *pEvRead = (struct event*)arg;  
				event_del(pEvRead);  
				delete pEvRead;  

				close(iCliFd);  
				return;  
		}  

		buf[iLen] = 0;  
		cout << "Client Info:" << buf << endl;  
}  

// 连接请求事件回调函数  
void onAccept(int iSvrFd, short iEvent, void *arg)  
{  
		int iCliFd;  
		struct sockaddr_in sCliAddr;  

		socklen_t iSinSize = sizeof(sCliAddr);  
		iCliFd = accept(iSvrFd, (struct sockaddr*)&sCliAddr, &iSinSize);  

		// 连接注册为新事件 (EV_PERSIST为事件触发后不默认删除)  
		struct event *pEvRead = new event;  
		event_set(pEvRead, iCliFd, EV_READ|EV_PERSIST, onRead, pEvRead);  
		event_base_set(base, pEvRead);  
		event_add(pEvRead, NULL);  
}  

int main()  
{  

		int iSvrFd;    
		struct sockaddr_in sSvrAddr;  

		memset(&sSvrAddr, 0, sizeof(sSvrAddr));    
		sSvrAddr.sin_family = AF_INET;    
		sSvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");      
		sSvrAddr.sin_port = htons(8888);     

		// 创建tcpSocket（iSvrFd），监听本机8888端口    
		iSvrFd = socket(AF_INET, SOCK_STREAM, 0);    
		bind(iSvrFd, (struct sockaddr*)&sSvrAddr, sizeof(sSvrAddr));    
		listen(iSvrFd, 10);  

		// 初始化base  
		base = event_base_new();  

		struct event evListen;  
		// 设置事件  
		event_set(&evListen, iSvrFd, EV_READ|EV_PERSIST, onAccept, NULL);  
		// 设置为base事件  
		event_base_set(base, &evListen);  
		// 添加事件  
		event_add(&evListen, NULL);  

		// 事件循环  
		event_base_dispatch(base);  

		return 0;  
}  
