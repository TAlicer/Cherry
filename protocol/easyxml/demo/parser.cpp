#include <iostream> 
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "easyxml.hpp"
using namespace easyxml;
using namespace tinyxml2;


#define XML_FILE "test.xml"

//获取文件大小
int file_size(const char* filename)
{
	struct stat statbuf;
	int size = 0;
	
	stat(filename,&statbuf);
	size=statbuf.st_size;
	
	return size;
}

//获取文件内容
char *getTestXml()
{
	char *xmlBuf = NULL;
	int fd = -1;
	int fileSize = 0;

	fileSize = file_size(XML_FILE);

	xmlBuf = (char *)malloc(fileSize + 1);
	if (NULL == xmlBuf)
	{
		printf("malloc() failure !");
		return NULL;
	}

	fd = open(XML_FILE,O_RDONLY);
	if(fd <= 0)
	{
		perror("open fail!\n");
		close(fd);
		return NULL;
 	}

	 read(fd, xmlBuf, fileSize);
	 xmlBuf[fileSize] = '\0';

	 close(fd);
	 return xmlBuf;
}

int main(void /* int argc, char ** argv */ )
{
	XMLDocument xmlDoc;
	XMLElement *pXmlRoot = NULL;
	XMLElement *pXmlTra = NULL;
	char *xmlBuf = NULL;
	char messageID[32] = {0};
	int messageNumber = -1;

//从文件中获取xml内容并解析
#if 0
	if(0 == xmlDoc.LoadFile(XML_FILE))
	{
		pXmlRoot = xmlDoc.FirstChildElement("PPVSPMessage");
		if (pXmlRoot != NULL)
		{
			pXmlTra = pXmlRoot->FirstChildElement("Header");
			if (pXmlTra != NULL)
			{
				xmlGetChildNode(pXmlTra, "MessageID", messageID, sizeof(messageID));
				xmlGetNodeAttr(pXmlTra, "AppSequence", "MessageNumber", &messageNumber);
			}
			std::cout<<messageID<<std::endl;
			std::cout<<messageNumber<<std::endl;
		}  
	}
	else
	{
		free(xmlBuf);
		xmlBuf = NULL;
		return -1;
	}
#else
	//从buf中获取xml内容并解析
	xmlBuf = getTestXml();

 	//对于Parse函数，您可以选择传入“ len”，即要解析的字节数。如果未指定，TinyXML-2将假定'xml'指向以NULL终止的字符串
	if(0 == xmlDoc.Parse((const char *)xmlBuf, file_size(XML_FILE)))
	{
		pXmlRoot = xmlDoc.RootElement();
		if (pXmlRoot != NULL)
		{
			pXmlTra = pXmlRoot->FirstChildElement("Header");
			if (pXmlTra != NULL)
			{
				xmlGetChildNode(pXmlTra, "MessageID", messageID, sizeof(messageID));
				xmlGetNodeAttr(pXmlTra, "AppSequence", "MessageNumber", &messageNumber);
			}
			std::cout<<messageID<<std::endl;
			std::cout<<messageNumber<<std::endl;
		}  
	}
	else
	{
		free(xmlBuf);
		xmlBuf = NULL;
		return -1;
	}
#endif

	free(xmlBuf);
	xmlBuf = NULL;

	return 0;
}

