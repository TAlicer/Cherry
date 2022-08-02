#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

static void get_server_ip(int sock)
{
	struct sockaddr_in addrMy;
 	memset(&addrMy,0,sizeof(addrMy));
 	int len = sizeof(addrMy);

 	getsockname(sock,(struct sockaddr*)&addrMy,(socklen_t *)&len);
 	printf("ip = %s", inet_ntoa(addrMy.sin_addr));

 	return;
}


int main(int argc, char*argv[])  
{     
	int sockfd; // 套接字文件描述符  
	struct sockaddr_in local_addr; // 本地地址 
	int err = -1; 
	char group[16] = "239.255.255.250"; // 多播组 IP
	int iparm = 1;
	int ttl = 10;
	  
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);  //建立套接字
	if (sockfd == -1)  
	{  
		perror("socket()");  
		return -1;  
	}    
	
	if(2 != argc)    
    {    
		printf("Please enter port!\n");
        printf("Usage: %s 37020\n",argv[0]);
    
        return -1;    
    }
	
	// 初始化地址 
	memset(&local_addr, 0, sizeof(local_addr));  
	local_addr.sin_family = AF_INET;  
	local_addr.sin_addr.s_addr = htonl(INADDR_ANY);  
	local_addr.sin_port = htons(atoi(argv[1]));
	  
	// 绑定socket  
	err = bind(sockfd,(struct sockaddr*)&local_addr, sizeof(local_addr));  
	if(err < 0)  
	{  
		perror("bind()");  
		return -2;  
	}    
 
	printf ("Bind local port[%s]\n", argv[1]);
	
	struct ip_mreq mreq; // 多播地址结构体                                 
 
	// 加入多播组，相当于创建一个QQ群，某人加入此群
	mreq.imr_multiaddr.s_addr = inet_addr(group); // 多播地址，类似于 QQ 群号 
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);// 将本机加入多播组，类似于某人加入此群
	
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&iparm, sizeof(iparm));
	setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&ttl, sizeof(int));
	
	// 加入多播组
	err = setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));  
	if (err < 0)  
	{  
		perror("[50]setsockopt():IP_ADD_MEMBERSHIP");  
		return -4;  
	} 
 
	int times = 0;  
	int addr_len = 0;  
	char buff[2048] = {0};  
	int n = 0; 
	
	printf("加入多播组成功，准备接收数据\n");
 
	//接收数据
	while(1) 
	{  
		addr_len = sizeof(local_addr);  
		memset(buff, 0, sizeof(buff));     
		
		// 接收数据 
		n = recvfrom(sockfd, buff, sizeof(buff), 0,(struct sockaddr*)&local_addr, &addr_len);  
		if( n == -1)   
		{  
			perror("recvfrom()"); 
			close(sockfd); 
			return -1;
		}  
 
		printf("Received packet from %s:%d\n", inet_ntoa(local_addr.sin_addr), ntohs(local_addr.sin_port));
		//printf("Recv message from server: %s\n\n", buff);  
		get_server_ip(sockfd);
	}
	
	// 退出广播组 
	err = setsockopt(sockfd, IPPROTO_IP, IP_DROP_MEMBERSHIP,&mreq, sizeof(mreq)); 
	if (err < 0)  
	{  
		perror("[79]setsockopt():IP_DROP_MEMBERSHIP");  
		return -4;  
	}  
 
		  
	close(sockfd); 
 
	return 0;  
}