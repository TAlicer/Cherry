/*****************************************************************************
function:system V ��Ϣ����ʾ��
command: ��Ҫִ�е�����
reply:�����Ҫ����ֵ������char * ָ�룬������NULL
command_type: 
HT_SHELL_POENP  :  ִ��popen���� (�������ȴ�����
HT_SHELL_SYSTEM :  ִ��system��������������������أ�   
HT_SHELL_SETENV :   ִ��setenv ��http_cookie �ȣ���Ҫ�Լ���ӣ�����
����ֵ��0��ʾִ�гɹ�������ִ��ʧ��
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include <errno.h>
enum
{
	SHELL_POENP,		//������Ҫ��ȡ������Ϣ�����
	SHELL_SYSTEM,		//���ڲ���Ҫ��ȡ������Ϣ�����
	SHELL_SETENV		//�������û�������
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
	
	// ������Ϣ����
	msgid = msgget((key_t)5678, 0666 | IPC_CREAT);
	if (msgid == -1)
	{
		printf("msgget failed error: %s\n", strerror(errno));
		return -1;
	}
 
	// ����Ϣ������д��Ϣ
	msgrcv(msgid, (void *)&recv, 4096, msgtype, IPC_NOWAIT) ;

	data.msg_type = 1; 
	data.command_type=command_type;
	strcpy(data.text, command);

	// ������﷢������
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