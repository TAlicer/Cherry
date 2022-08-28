#include <string>
#include"tinyxml2/tinyxml2.h"  

using namespace std;  
using namespace tinyxml2_onvif;

#define _TO_STR(name) #name

///< 添加节点（不带节点值）
#define XML_INSERT_NODE(doc, father, name)		\
({												\
	XMLElement *node = doc.NewElement(name);	\
	father->InsertEndChild(node);				\
	node;										\
})


///< 添加节点（带节点值）	
#define XML_INSERT_TEXT_NODE(doc, father, name, text)	\
({														\
	XMLElement *node = doc.NewElement(name);			\
	node->SetText(text);								\
	father->InsertEndChild(node);						\
	node;												\
})

   
///< 设置节点属性
#define XML_SET_ATTR_NODE(node, attribute, value)		\
	do													\
	{													\
		node->SetAttribute(attribute, value);			\
	} while(0)


///< xml节点安全操作
#define SAFE_XML_NODE(node, expr)				\
	do											\
	{											\
		if (node && node->GetText())			\
		{										\
			expr;								\
		}										\
		else									\
		{										\
			printf("node [%s] null.\n", #node);	\
		}										\
	} while (0)


///< 空指针处理
#define PTR_NULL(ptr, expr)				\
	do									\
	{									\
		if (!ptr)						\
		{								\
			printf("%s null.\n", #ptr);	\
			expr;						\
		}								\
	} while (0)


///< xml节点判空处理
#define NODE_NULL(node, expr) PTR_NULL(node, expr)


///< xml节点为空时返回false
#define NODE_NULL_RET_FALSE(node) NODE_NULL(node, return false)


// xml节点为空时忽略
#define NODE_NULL_IGNORE(node) NODE_NULL(node, (void)0)


///< xml查询节点是否有值为value的属性
#define FIND_ATTR_VALUE(node, value)						\
({															\
	int flag;												\
	if (node && node->FirstAttribute())						\
	{														\
		const XMLAttribute* a = NULL;						\
		for(a = node->FirstAttribute(); a; a = a->Next())	\
		{													\
			if( XMLUtil::StringEqual( a->Value(), value))	\
			{												\
				flag = 1;									\
			}												\
			else											\
			{												\
				flag = 0;									\
			}												\
		}													\
	}														\
	else													\
	{														\
		printf("node [%s] null.\n", #node);					\
	}														\
	flag;													\
})


///< xml获取节点属性
#define XML_ATTR(node, attr, buf)														\
	do																					\
	{																					\
		if (node && node->Attribute(attr))												\
		{																				\
			snprintf(buf, std::min(sizeof(buf) - 1, strlen(node->Attribute(attr)))+1,	\
						"%s", node->Attribute(attr));									\
		}																				\
		else																			\
		{																				\
			printf("node [%s] null.\n", #node);											\
		}																				\
	} while (0)	


///< xml获取节点int型属性
#define XML_INT_ATTR(node, attr, ret)								\
		do															\
		{															\
			if (node && node->Attribute(attr))						\
			{														\
				sscanf(node->Attribute(attr), "%d", (int *)&ret);	\
			}														\
			else													\
			{														\
				printf("node [%s] null.\n", #node);					\
			}														\
		} while (0)


///< xml获取bool结果
#define XML_BOOL(node, elm, ret)					\
	SAFE_XML_NODE(node->FirstChildElement(elm),		\
				  ret = (std::string("true") == node->FirstChildElement(elm)->GetText()) ? 1 : 0)


///< xml获取int结果
#define XML_INT(node, elm, ret)						\
	SAFE_XML_NODE(node->FirstChildElement(elm),		\
				  sscanf(node->FirstChildElement(elm)->GetText(), "%d", (int *)&ret))


///< xml获取float结果
#define XML_FLOAT(node, elm, ret)					\
	SAFE_XML_NODE(node->FirstChildElement(elm),		\
				  sscanf(node->FirstChildElement(elm)->GetText(), "%f", &ret))


///< xml获取string结果，NOTE:buf应该是一个数组
#define XML_STR(node, elm, buf)																				\
	SAFE_XML_NODE(node->FirstChildElement(elm),																\
				  snprintf(buf,																				\
						   std::min(sizeof(buf) - 1, strlen(node->FirstChildElement(elm)->GetText()))+1,	\
						   "%s", node->FirstChildElement(elm)->GetText()))


///< 获取当前节点的值
#define XML_STR_CUR(node,  buf)														\
	SAFE_XML_NODE(node,																\
				  snprintf(buf,														\
						   std::min(sizeof(buf) - 1, strlen(node->GetText()))+1,	\
						   "%s", node->GetText()))


///< 有命名空间也能获取, 且返回当前节点
#define XML_STR_EXT(node, elm, buf)														\
	SAFE_XML_NODE(node->FirstChildElement(elm),											\
		do																				\
		{																				\
			node = node->FirstChildElement();											\
			while(node != NULL)															\
			{																			\
				if(NULL != strstr(node->Name(),elm))									\
				{																		\
					snprintf(buf,														\
							std::min(sizeof(buf) - 1, strlen(node->GetText())) + 1,		\
							"%s", node->GetText());										\
					break;																\
				}																		\
				node = node->NextSiblingElement();										\
			}																			\
		} while(0))

