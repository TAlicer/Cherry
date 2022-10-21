#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include <errno.h>
#define MSG_SIZE 4096
struct msg_st
{
    long int msg_type;
    int command_type;
    char text[MSG_SIZE];
};
   
int main(int argc, char *argv[])
{
    fprintf(stdout,"Start hannto shell exec process \n");
   
    int msgid = -1;
    struct msg_st data;
    struct msg_st reply;
    long int msgtype = 1;   
    reply.msg_type = 2;
    char buf[MSG_SIZE]= {0};

    // 建立消息队列
    msgid = msgget((key_t)5678, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        fprintf(stderr, "msgget failed width error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
 
    // 从队列中获取消息
    while (1)
    {
        printf("shell wait for msg\n");
        if (msgrcv(msgid, (void *)&data, MSG_SIZE, msgtype, 0) == -1)
        {
            fprintf(stderr, "msgrcv failed width erro: %d\n", errno);
        }
 
        printf("recv message: %s   command_type=%d\n",data.text,data.command_type);

        if(data.command_type==0)//执行popen函数
        {
                printf("execute popen command \n");
                setenv("LUA_PATH", "/www/?.lua", 0);
                size_t read=0;
                FILE *f = popen(data.text, "r");
                if (!f)
                {
                    
                    printf("popen failed ,error=%s\n",strerror(errno));
                   continue;
                }
                memset(buf,0,MSG_SIZE);
                memset(reply.text,0,MSG_SIZE);
                read=fread(buf,1,MSG_SIZE,f);
                if (read<=0)
                {
                    //pclose(f);
                    printf("lua concext is null\n");
                    //continue;
                }
                
                pclose(f);
                int ret=0;
               
                strncpy(reply.text, buf,strlen(buf));
               // printf("-----------------------------------------------------lua reply =%s\n",reply.text);
                ret=msgsnd(msgid, (void *)&reply,strlen(reply.text)+sizeof(int), 0);
                if ( ret== -1)
                {
                    fprintf(stderr, "msgsnd failed\n");
                    exit(EXIT_FAILURE);
                }
                fprintf(stdout, "shell process reply successful\n\n");
                continue;
        }
        else if(data.command_type==1)//执行system函数
        {
            
            if(system(data.text))
            {
                printf("%s system failed ,error=%s\n",data.text,strerror(errno));
            }
            continue;
            
        }
        else if(data.command_type==2)//执行setenv函数，设置http_cookie 环境变量
        {
			setenv("HTTP_COOKIE", data.text, 1);
			printf("HTTP_COOKIE=%s\n",getenv("HTTP_COOKIE"));
			printf("set http cookie succesfuly\n\n");
            continue;
        } 
    }

 #if 0
    // 删除消息队列
    if (msgctl(msgid, IPC_RMID, 0) == -1)
    {
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
    }
#endif
    
    return 0;
}