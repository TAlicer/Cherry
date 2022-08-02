#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ringBuffer.h"

#define VOS_OK 0
#define VOS_ERR -1

char *pHead = NULL;			//环形缓冲区首地址
char *pValidRead = NULL;	//已使用环形缓冲区首地址
char *pValidWrite = NULL;	//已使用环形缓冲区尾地址
char *pTail = NULL;			//环形缓冲区尾地址

//环形缓冲区初始化
void InitRingBuff()
{
	if(NULL == pHead)
	{
		pHead = (char *)malloc(BUFF_MAX_LEN * sizeof(char));
	}
	
	memset(pHead, 0 , sizeof(BUFF_MAX_LEN));
	
	pValidRead = pHead;
	pValidWrite = pHead;
	pTail = pHead + BUFF_MAX_LEN;  
}

//环形缓冲区释放
void FreeRingBuff()
{
	if(NULL != pHead)
	{
		free(pHead);
	}
}

//向缓冲区写数据
int WriteRingBuff(char *pBuff, int AddLen)
{
	if(NULL == pHead)
	{
		printf("WriteRingBuff:RingBuff is not Init!\n");
		return VOS_ERR;
	}

	if(AddLen > pTail - pHead)
	{
		printf("WriteRingBuff:New add buff is too long\n");	
		return VOS_ERR;
	}
	
	//若新增的数据长度大于写指针和尾指针之间的长度
	if(pValidWrite + AddLen > pTail)
	{
		int PreLen = pTail - pValidWrite;
		int LastLen = AddLen - PreLen;
		memcpy(pValidWrite, pBuff, PreLen);	
		memcpy(pHead, pBuff + PreLen, LastLen);
		
		pValidWrite = pHead + LastLen;	//新环形缓冲区尾地址
	}
	else
	{
		memcpy(pValidWrite, pBuff, AddLen);	//将新数据内容添加到缓冲区
		pValidWrite += AddLen;	//新的有效数据尾地址
	}
	return VOS_OK;
}

//从缓冲区读数据
int ReadRingBuff(char *pBuff, int len)
{
	if(NULL == pHead)
	{
		printf("ReadRingBuff:RingBuff is not Init!\n");
		return VOS_ERR;
	}
	if(len > pTail - pHead)
	{
		printf("ReadRingBuff:Read buff size is too long\n");	
		return VOS_ERR;
	}
	if(0 == len)
	{
		return VOS_OK;
	}
	if(pValidRead + len > pTail)
	{
		int PreLen = pTail - pValidRead;
		int LastLen = len - PreLen;
		memcpy(pBuff, pValidRead, PreLen);
		memcpy(pBuff + PreLen, pHead, LastLen);
		
		pValidRead = pHead + LastLen;
	}
	else
	{
		memcpy(pBuff, pValidRead, len);
		pValidRead += len;
	}
	
	return len;
}