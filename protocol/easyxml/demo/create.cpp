#include <string.h>
#include <stdlib.h>

#include "easyxml.hpp"
using namespace tinyxml2;
using namespace easyxml;

/** @fn
* @brief 复制字符串到新分配的内存中。
* @param pSrc   指向需要复制的字符串。
* @return 新分配的内存地址   成功。
   NULL    失败。
*/
char *strDup(const char *pSrc)
{
	int len = 0;
	char *pDst = NULL;

	if (NULL == pSrc)
	{
		return NULL;
	}

	len = strlen(pSrc);
	pDst = (char *)malloc(len + 1);
	if (NULL == pDst)
	{
	printf("malloc() failure !");
	return NULL;
	}

	memcpy(pDst, pSrc, len);
	pDst[len] = '\0';

	return pDst;
}


int main(int argc, char ** argv)
{
	XMLDocument xmlDoc;
	XMLNode* parent = NULL;
	XMLElement *currentNode = NULL;
	XMLElement *child[16] = { NULL };
	XMLElement *node = NULL;
	XMLPrinter printer;
	char *xmlBuf = NULL;
	int len = 0;
	
	parent = &xmlDoc;
	
	parent->InsertEndChild( xmlDoc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\""));

	child[1] = xmlAddNode(xmlDoc, parent, "env:Envelope");
	child[2] = xmlAddNode(xmlDoc, child[1], "Header");
	xmlAddNode(xmlDoc, child[2], "MessageID", "87adc205-1dd2");
	xmlAddNode(xmlDoc, child[2], "To", "schemas-xmlsoap-org");
	xmlAddNode(xmlDoc, child[2], "Action", "http://schemas");

	currentNode = xmlAddNode(xmlDoc, child[2], "AppSequence");
	xmlSetNodeAttr(currentNode, "InstanceId", "1599575162");
	xmlSetNodeAttr(currentNode, "MessageNumber", "0");

	child[2] = xmlAddNode(xmlDoc, child[1], "Body");
	child[3] = xmlAddNode(xmlDoc, child[2], "Hello");
	child[4] = xmlAddNode(xmlDoc, child[3], "EndpointReference");
	xmlAddNode(xmlDoc, child[4], "Address", "uuid:87adc205-1dd2-11b2-8459-98df82014343");
	xmlAddNode(xmlDoc, child[3], "Types", "Device");
	xmlAddNode(xmlDoc, child[3], "MetadataVersion", 1.5556f);

	xmlDoc.Print(&printer);
	xmlBuf = strDup(printer.CStr());	//将组装的xml报文保存到xmlBuf里
	if (NULL == xmlBuf)
	{
		return -1;
	}

	len = printer.CStrSize();			//该长度包含终止符null，即len = xml报文实际长度+1
	printf("xmlBuf size:\n%d\n", len);
	printf("xmlBuf:\n%s\n", xmlBuf);

	xmlDoc.SaveFile("test.xml");		//将组装的xml报文保存到本地test.xml文件

	free(xmlBuf);
	xmlBuf = NULL;
	return 0;
}


/*---------------组装好的报文---------------*/
/*
<?xml version="1.0" encoding="UTF-8"?>
<env:Envelope>
    <Header>
        <MessageID>87adc205-1dd2</MessageID>
        <To>schemas-xmlsoap-org</To>
        <Action>http://schemas</Action>
        <AppSequence InstanceId="1599575162" MessageNumber="0"/>
    </Header>
    <Body>
        <Hello>
            <EndpointReference>
                <Address>uuid:87adc205-1dd2-11b2-8459-98df82014343</Address>
            </EndpointReference>
            <Types>Device</Types>
            <MetadataVersion>1.5556</MetadataVersion>
        </Hello>
    </Body>
</env:Envelope>
*/
