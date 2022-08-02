#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> //close()
#include <string.h> //strcmp()���ַ�����������
#include <stdlib.h> //atoi() �ַ���תint
#include <iostream>
#include <fstream>
#include <sstream>
 
int main(int argc, char *argv[])
{
	int port = 12345;
	if( port<1025 || port>65535 )//0~1024һ���ϵͳʹ�ã�һ�����Է��䵽65535
	{
		printf("�˿ںŷ�ΧӦΪ1025~65535");
		return -1;
	}
	
	//1 ����tcpͨ��socket
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1)
	{
		perror("socket failed!\n");
	}
 
	//2 ���ӷ�����
	struct sockaddr_in server_addr = {0};//�������ĵ�ַ��Ϣ
	server_addr.sin_family = AF_INET;//IPv4Э��
	server_addr.sin_port = htons(port);//�������˿ں�
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//���÷�����IP
	int ret = connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if(ret == -1)
	{
		perror("connect failed!\n");
	}
	else
	{
		printf("connect server successful!\n");
	}
 
#if 0
	//3 ѭ��������Ϣ
	while(1)
	{
		char buf[1024] = {0};
		printf("Please enter msg:");
		scanf("%s",buf);
		write(socket_fd,buf,strlen(buf));//������Ϣ
		if(strcmp(buf, "exit") == 0)
		{
			break;//�˳�ѭ��
		}
	}
#endif
	
	std::string strValue;
	std::ifstream ifs("demo.txt");
    std::string strOut((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>(0));

	while(1)
	{
	write(socket_fd, strOut.c_str(), strOut.size());//������Ϣ
	sleep(1);
	}
 
	//4 �ر�������socket
	close(socket_fd);
 
	return 0;
}