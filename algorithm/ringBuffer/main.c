#include <stdio.h>
#include <stdlib.h>
#include "ringBuffer.h"
// 主函数
int main()
{
	char c;
	int len;
	int readLen;
	char readBuffer[BUFF_MAX_LEN];
	int i = 0;
	
	InitRingBuff();
	
	printf("Please enter a character\n");
	
	while(1)
	{
		c=getchar();
		
		switch(c)
		{
			case 'Q':
			case 'q':
				goto exit;
			break;
			
			case 'R':
			case 'r':
				readLen = ReadRingBuff(readBuffer,3);
				printf("ReadRingBufflen:%d\n",readLen);
				if(readLen > 0)
				{
					for(i = 0;i < readLen;i++)
					{
						printf("%c ",(char)readBuffer[i]);
					}
					printf("\n");
				}
			break;
			
			default :
				if(c!='\n') WriteRingBuff((char*)&c,1);
			break;
		}
	};
	
exit:
	FreeRingBuff();

    return 0;
}