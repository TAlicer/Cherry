/*******************************************************************************
 * Project:  easyxml
 * @file     easyxml.cpp
 * @brief 
 * @author   south-bear2
 * @date:    2020-11-09
 * @note
 * Modify history:
 ******************************************************************************/
	
#include <string>
#include "tinyxml2.h" 
#include "easyxml.hpp"
using namespace tinyxml2;


#ifdef _WIN32
#define snprintf _snprintf_s
#endif
 
namespace easyxml
{

///< 添加空节点元素
XMLElement *xmlAddNode(XMLDocument& doc, XMLElement *fatherNode, const char *nodeName)
{ 
    XMLElement *node = doc.NewElement(nodeName);
    fatherNode->InsertEndChild(node);
	
    return node;
}

XMLElement *xmlAddNode(XMLDocument& doc, XMLNode *fatherNode, const char *nodeName)
{ 
    XMLElement *node = doc.NewElement(nodeName);
    fatherNode->InsertEndChild(node);
	
    return node;
}

///< 添加节点元素,带实体
XMLElement *xmlAddNode(XMLDocument& doc, XMLElement *fatherNode, const char *nodeName, const char *value)
{ 
    XMLElement *node = doc.NewElement(nodeName);
	node->SetText(value); 
    fatherNode->InsertEndChild(node);
 
    return node;
}

XMLElement *xmlAddNode(XMLDocument& doc, XMLElement *fatherNode, const char *nodeName, int value)
{ 
    XMLElement *node = doc.NewElement(nodeName);
	node->SetText(value); 
    fatherNode->InsertEndChild(node);
 
    return node;
}

XMLElement *xmlAddNode(XMLDocument& doc, XMLElement *fatherNode, const char *nodeName, double value)
{ 
    XMLElement *node = doc.NewElement(nodeName);
	node->SetText(value); 
    fatherNode->InsertEndChild(node);
 
    return node;
}

XMLElement *xmlAddNode(XMLDocument& doc, XMLElement *fatherNode, const char *nodeName, float value)
{ 
    XMLElement *node = doc.NewElement(nodeName);
	node->SetText(value); 
    fatherNode->InsertEndChild(node);
 
    return node;
}

XMLElement *xmlAddNode(XMLDocument& doc, XMLNode *fatherNode, const char *nodeName, const char *value)
{ 
    XMLElement *node = doc.NewElement(nodeName);
	node->SetText(value); 
    fatherNode->InsertEndChild(node);
 
    return node;
}

XMLElement *xmlAddNode(XMLDocument& doc, XMLNode *fatherNode, const char *nodeName, int value)
{ 
    XMLElement *node = doc.NewElement(nodeName);
	node->SetText(value); 
    fatherNode->InsertEndChild(node);
 
    return node;
}

XMLElement *xmlAddNode(XMLDocument& doc, XMLNode *fatherNode, const char *nodeName, double value)
{ 
    XMLElement *node = doc.NewElement(nodeName);
	node->SetText(value); 
    fatherNode->InsertEndChild(node);
 
    return node;
}

XMLElement *xmlAddNode(XMLDocument& doc, XMLNode *fatherNode, const char *nodeName, float value)
{ 
    XMLElement *node = doc.NewElement(nodeName);
	node->SetText(value); 
    fatherNode->InsertEndChild(node);
 
    return node;
}

///< 设置节点属性
void xmlSetNodeAttr(XMLElement *nodeName, const char *attrName, const char *value)
{ 
	nodeName->SetAttribute(attrName, value);
    return;
}

///< xml获取节点属性
void xmlGetNodeAttr(XMLElement *nodeName, const char *attrName, char *buf, int bufLen)
{ 
	if (nodeName && nodeName->Attribute(attrName))
	{
		snprintf(buf, std::min(bufLen - 1, (int)strlen(nodeName->Attribute(attrName)))+1,
						"%s", nodeName->Attribute(attrName));
	}
	else
	{
		printf("node or node name is null.\n");
	}
    return;
}

void xmlGetNodeAttr(XMLElement *nodeName, const char *attrName, int *value)
{ 
	if (nodeName && nodeName->Attribute(attrName))
	{
		sscanf(nodeName->Attribute(attrName), "%d", value);
	}
	else
	{
		printf("node or node name is null.\n");
	}
    return;
}

void xmlGetNodeAttr(XMLElement *nodeName, const char *attrName, double *value)
{ 
	if (nodeName && nodeName->Attribute(attrName))
	{
		sscanf(nodeName->Attribute(attrName), "%lf", value);
	}
	else
	{
		printf("node or node name is null.\n");
	}
    return;
}

void xmlGetNodeAttr(XMLElement *nodeName, const char *attrName, float *value)
{ 
	if (nodeName && nodeName->Attribute(attrName))
	{
		sscanf(nodeName->Attribute(attrName), "%f", value);
	}
	else
	{
		printf("node or node name is null.\n");
	}
    return;
}

void xmlGetNodeAttr(XMLElement *fatherNode, const char *nodeName, const char *attrName, char *buf, int bufLen)
{ 
	XMLElement *pXmlTra = NULL;

	pXmlTra = fatherNode->FirstChildElement(nodeName);
	
	if (pXmlTra && pXmlTra->Attribute(attrName))
	{
		snprintf(buf, std::min(bufLen - 1, (int)strlen(pXmlTra->Attribute(attrName)))+1,
						"%s", pXmlTra->Attribute(attrName));
	}
	else
	{
		printf("node [%s] null.\n", nodeName);
	}
    return;
}

void xmlGetNodeAttr(XMLElement *fatherNode, const char *nodeName, const char *attrName, int *value)
{ 
	XMLElement *pXmlTra = NULL;

	pXmlTra = fatherNode->FirstChildElement(nodeName);
	
	if (pXmlTra && pXmlTra->Attribute(attrName))
	{
		sscanf(pXmlTra->Attribute(attrName), "%d", value);
	}
	else
	{
		printf("node [%s] null.\n", nodeName);
	}
    return;
}

void xmlGetNodeAttr(XMLElement *fatherNode, const char *nodeName, const char *attrName, double *value)
{ 
	XMLElement *pXmlTra = NULL;

	pXmlTra = fatherNode->FirstChildElement(nodeName);
	
	if (pXmlTra && pXmlTra->Attribute(attrName))
	{
		sscanf(pXmlTra->Attribute(attrName), "%lf", value);
	}
	else
	{
		printf("node [%s] null.\n", nodeName);
	}
    return;
}

void xmlGetNodeAttr(XMLElement *fatherNode, const char *nodeName, const char *attrName, float *value)
{ 
	XMLElement *pXmlTra = NULL;

	pXmlTra = fatherNode->FirstChildElement(nodeName);
	
	if (pXmlTra && pXmlTra->Attribute(attrName))
	{
		sscanf(pXmlTra->Attribute(attrName), "%f", value);
	}
	else
	{
		printf("node [%s] null.\n", nodeName);
	}
    return;
}

/******************************************************************************************/
void xmlGetChildNode(XMLElement *fatherNode, const char *nodeName, bool *value)
{	
	SAFE_XML_NODE(fatherNode->FirstChildElement(nodeName),
		*value = (std::string("true") == fatherNode->FirstChildElement(nodeName)->GetText()) ? 1 : 0);

	return;
}

void xmlGetChildNode(XMLElement *fatherNode, const char *nodeName, int *value)
{	
	SAFE_XML_NODE(fatherNode->FirstChildElement(nodeName),
		sscanf(fatherNode->FirstChildElement(nodeName)->GetText(), "%d", value));

	return;
}

void xmlGetChildNode(XMLElement *fatherNode, const char *nodeName, double *value)
{	
	SAFE_XML_NODE(fatherNode->FirstChildElement(nodeName),
		sscanf(fatherNode->FirstChildElement(nodeName)->GetText(), "%lf", value));

	return;
}

void xmlGetChildNode(XMLElement *fatherNode, const char *nodeName, float *value)
{	
	SAFE_XML_NODE(fatherNode->FirstChildElement(nodeName),
		sscanf(fatherNode->FirstChildElement(nodeName)->GetText(), "%f", value));

	return;
}

void xmlGetChildNode(XMLElement *fatherNode, const char *nodeName, char *buf, int bufLen)
{	
	SAFE_XML_NODE(fatherNode->FirstChildElement(nodeName),
		snprintf(buf,
				std::min(bufLen - 1, (int)strlen(fatherNode->FirstChildElement(nodeName)->GetText()))+1,
				"%s", fatherNode->FirstChildElement(nodeName)->GetText()));
		
	return;
}

}


