#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_
typedef unsigned char u8;
typedef unsigned int u32;
#define BUFF_MAX_LEN  5   //缓冲区的长度,可以修改

void InitRingBuff(void);
void FreeRingBuff(void);
int WriteRingBuff(char *pBuff, int AddLen);
int ReadRingBuff(char *pBuff, int len);

#endif /* RINGBUFFER_H_ */
