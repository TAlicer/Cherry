/*****************************************************************************
function:system V 消息队列示例
command: 需要执行的命令
reply:如果需要返回值，则传入char * 指针，否则填NULL
command_type: 
HT_SHELL_POENP  :  执行popen命令 (会阻塞等待返回
HT_SHELL_SYSTEM :  执行system命令（不会阻塞，立即返回）   
HT_SHELL_SETENV :   执行setenv （http_cookie 等，需要自己添加）命令
返回值：0表示执行成功，否则执行失败
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include <errno.h>
enum
{
	SHELL_POENP,		//用于需要获取返回信息的情况
	SHELL_SYSTEM,		//用于不需要获取返回信息的情况
	SHELL_SETENV		//用于设置环境变量
};

struct msg_data
{
    long int msg_type;
    int command_type;
    char text[4096];
};

int  shell_command(char* command,char * msg_reply,int command_type)
{
	struct msg_data data;
	struct msg_data recv;
	int msgid = -1;
	int ret =0;
	long int msgtype = 2;
	
	printf("command=%s  command_type=%d \n",command,command_type);
	
	// 建立消息队列
	msgid = msgget((key_t)5678, 0666 | IPC_CREAT);
	if (msgid == -1)
	{
		printf("msgget failed error: %s\n", strerror(errno));
		return -1;
	}
 
	// 向消息队里中写消息
	msgrcv(msgid, (void *)&recv, 4096, msgtype, IPC_NOWAIT) ;

	data.msg_type = 1; 
	data.command_type=command_type;
	strcpy(data.text, command);

	// 向队列里发送数据
	if (msgsnd(msgid, (void *)&data, 12+strlen(command), 0) == -1)
	{
		printf("msgsnd failed\n");
		return -1;
	}

	if(command_type==0)
	{
		
		 memset(recv.text,0,4096);
		 ret =msgrcv(msgid, (void *)&recv, 4096, msgtype, 0) ;
		
		 if (ret== -1)
		{
			printf("msgrcv failed with erro: %d\n", errno);
			return -1;
		}
 
		if(msg_reply)
		{
			strncpy(msg_reply,recv.text,strlen(recv.text)+2);
		}
	}

	return 0;
}


int main(int argc, char *argv[])
{
	char buf[128] = {0};
	
	shell_command("echo \"hello world\" > test.txt", NULL, SHELL_SYSTEM);
	shell_command("theme=light", NULL, SHELL_SETENV);
	
	shell_command("env | grep HTTP_COOKIE", buf, SHELL_POENP);
	printf("buf = %s\n", buf);
	
	return 0;
}