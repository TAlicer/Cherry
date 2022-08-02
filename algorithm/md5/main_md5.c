#include "md5.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "md5-private.h"

#define READ_DATA_SIZE	1024
#define MD5_SIZE		16
#define MD5_STR_LEN		(MD5_SIZE * 2)

#if 0
// function declare
int Compute_string_md5(unsigned char *dest_str, unsigned int dest_len, char *md5_str);
int Compute_file_md5(const char *file_path, char *md5_str);
static int getPrinterSN(char* sn,int size);
#endif
static int buildPrinterUUID(char* uuid,int size);

/************** main test **************/
int main(int argc, char *argv[])
{
	int ret;
	const char *file_path = "./sn";
	char md5_str1[MD5_STR_LEN + 1];
	char md5_str2[MD5_STR_LEN + 1];
	const char *test_str = "32435/AHAFEF1VC00060";
	char uuid[46] = {0};
	
	#if 0
	// test file md5
	ret = Compute_file_md5(file_path, md5_str1);
	if (0 == ret)
	{
		printf("[file - %s] md5 value:\n", file_path);
		printf("%s\n", md5_str1);
	}
	#endif

	// test string md5 
	string_MD5((unsigned char *)test_str, (unsigned int)strlen(test_str), md5_str2);
	printf("[string - %s] md5 value:\n", test_str);
	printf("strlen(test_str) = %d\n", strlen(test_str));
	printf("%s\n", md5_str2);

	buildPrinterUUID(uuid, 46);
	
	return 0;
}

static int getPrinterSN(char* sn,int size)
{
    unsigned char data[32] = {0};
    int count = -1;

    if(sn==NULL)
    {
        return -1;
    }

    struct stat sb;
    int fd = open("./sn",O_RDONLY);
    if(fd<0)
    {
        perror("open");
        goto err;
    }
    if (fstat(fd, &sb) == -1) {
        perror("stat");
        goto err;
    }

    count = read(fd,data,sb.st_size);
    if(count<=0)
    {
        perror("read");
        goto err;
    }

    if(data[count-1]=='\n') data[count-1]='\0';

    count = snprintf(sn,size,"%s",data);

err:
    if(fd>0)
    {
        close(fd);
    }
    return count;
}


static int buildPrinterUUID(char* uuid,int size)
{
    unsigned char data[32]={0};
    size_t count = sizeof(data);
    int num=0;

    if(uuid==NULL)
    {
        return -1;
    }

    num = getPrinterSN(data,count);
    if(num<0) num=0;

    unsigned char md5sum[16];
    string_MD5(data, num, md5sum);
	printf("md5sum = %s\n", md5sum);
	
	
    char* buffer = uuid;

	snprintf(buffer, (size_t)size,
             "urn:uuid:%.8s-%.4s-%.4s-%.4s-%.12s",
             md5sum, md5sum+8, md5sum+12, md5sum+16, md5sum+20);
    printf("sn=%s uuid=%s\n",data,buffer);

    return 0;
}

#if 0
/**
 * compute the value of a string
 * @param  dest_str
 * @param  dest_len
 * @param  md5_str
 */
int Compute_string_md5(unsigned char *dest_str, unsigned int dest_len, char *md5_str)
{
	int i;
	unsigned char md5_value[MD5_SIZE];
	MD5_CTX md5;

	// init md5
	MD5Init(&md5);

	MD5Update(&md5, dest_str, dest_len);

	MD5Final(&md5, md5_value);

	// convert md5 value to md5 string
	for(i = 0; i < MD5_SIZE; i++)
	{
		snprintf(md5_str + i*2, 2+1, "%02x", md5_value[i]);
	}

	return 0;
}

/**
 * compute the value of a file
 * @param  file_path
 * @param  md5_str
 * @return 0: ok, -1: fail
 */
int Compute_file_md5(const char *file_path, char *md5_str)
{
	int i;
	int fd;
	int ret;
	unsigned char data[READ_DATA_SIZE];
	unsigned char md5_value[MD5_SIZE];
	MD5_CTX md5;

	fd = open(file_path, O_RDONLY);
	if (-1 == fd)
	{
		perror("open");
		return -1;
	}

	// init md5
	MD5Init(&md5);

	while (1)
	{
		ret = read(fd, data, READ_DATA_SIZE);
		if (-1 == ret)
		{
			perror("read");
			close(fd);
			return -1;
		}

		MD5Update(&md5, data, ret);

		if (0 == ret || ret < READ_DATA_SIZE)
		{
			break;
		}
	}

	close(fd);

	MD5Final(&md5, md5_value);

	// convert md5 value to md5 string
	for(i = 0; i < MD5_SIZE; i++)
	{
		snprintf(md5_str + i*2, 2+1, "%02x", md5_value[i]);
	}

	return 0;
}
#endif
