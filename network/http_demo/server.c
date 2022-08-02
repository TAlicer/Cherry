#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> //close()
#include <string.h> //strcmp()等字符串操作函数
#include <stdlib.h> //atoi() 字符串转int

int getHttpHead(int fd, char *buf, int bufLen)
{
	char tmp[1] = {0};
	int i = 0;
	int offset = 0;
	int nbytes = 0;

	while((nbytes=recv(fd,tmp,1, 0))==1)
	{
		if(offset > bufLen-1)
		{
			return bufLen;
		}
		
		if(i < 4)
		{
			if(tmp[0] == '\r' || tmp[0] == '\n') i++;
			else i = 0;
			
			strncpy(buf+offset, tmp, 1);
			offset++;
		}
		
		if(4 == i)
		{
			return offset;
		}
	}
	
	return -1;
}

int getPrintDocInfo(int fd, char *buf, int bufLen)
{
	int ret = 0;
	int offset = 0;
	int i = 0;
		
	for(i=0; i<3; i++)
	{
		ret = getHttpHead(fd, buf+offset, bufLen-offset);
		offset += ret;
	}
	
	read(fd, buf+offset, 2);
	return offset+2;
}


int main(int argc, char *argv[])
{
	int port = 12345;
	if( port<1025 || port>65535 )//0~1024一般给系统使用，一共可以分配到65535
	{
		printf("端口号范围应为1025~65535");
		return -1;
	}
 
	//1 创建tcp通信socket
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1)
	{
		perror("创建tcp通信socket失败!\n");
		return -1;
	}
 
	//2 绑定socket地址
	struct sockaddr_in server_addr = {0};//存放地址信息
	server_addr.sin_family = AF_INET;//AF_INET->IPv4  
	server_addr.sin_port = htons(port);//端口号
	server_addr.sin_addr.s_addr = INADDR_ANY;//让系统检测本地网卡，自动绑定本地IP
	int ret = bind(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr) );
	if(ret == -1)
	{
		perror("bind failed!\n");
		return -1;
	}
 
	//3 设置监听队列，设置为可以接受5个客户端连接
	ret = listen(socket_fd, 5);
	if(ret == -1)
	{
		perror("listen falied!\n");
	}
 
 
	printf("server is running!\n");
 
	struct sockaddr_in client_addr = {0};//用来存放客户端的地址信息
	int len = sizeof(client_addr);
	int new_socket_fd = -1;//存放与客户端的通信socket
	
	//4 等待客户端连接
	new_socket_fd = accept( socket_fd, (struct sockaddr *)&client_addr, &len);
	if(new_socket_fd == -1)
	{
		perror("accpet error!\n");
	}
	else
	{
		//printf("IP:%s, PORT:%d [connected]\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
	}

	char buf[1024*10] = {0};
	char body[1024*10] = {0};
	char pic[1024] = {0};
	int headLen = 0;
	
	headLen = getHttpHead(new_socket_fd, buf, sizeof(buf));
	printf("buf = :\n%s\n", buf);
	
	printf("------------------------------------\n");

	getPrintDocInfo(new_socket_fd, body, sizeof(body));
	printf("body = :\n%s\n", body);
	
	printf("------------------------------------\n");
	
	read(new_socket_fd, pic, sizeof(pic));
	printf("pic = :\n%s\n", pic);

	
	
	//5 关闭socket
	close(new_socket_fd);
	close(socket_fd);
 
	return 0;
}