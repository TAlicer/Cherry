#include "tinyxml2.h"
using namespace tinyxml2;

namespace easyxml
{

///< xml节点安全操作
#define SAFE_XML_NODE(node, expr)                \
    do                                           \
    {                                            \
        if (node && node->GetText())             \
        {                                        \
            expr;                                \
        }                                        \
        else                                     \
        {                                        \
            printf("node [%s] null.\n", #node);  \
        }                                        \
    } while (0)

///< 添加空节点元素
XMLElement *xmlAddNode(XMLDocument& doc, XMLElement *fatherNode, const char *nodeName);
XMLElement *xmlAddNode(XMLDocument& doc, XMLNode *fatherNode, const char *nodeName);

///< 添加节点元素,带实体
XMLElement *xmlAddNode(XMLDocument& doc, XMLElement *fatherNode, const char *nodeName, const char *value);
XMLElement *xmlAddNode(XMLDocument& doc, XMLElement *fatherNode, const char *nodeName, int value);
XMLElement *xmlAddNode(XMLDocument& doc, XMLElement *fatherNode, const char *nodeName, float value);
XMLElement *xmlAddNode(XMLDocument& doc, XMLElement *fatherNode, const char *nodeName, double value);

XMLElement *xmlAddNode(XMLDocument& doc, XMLNode *fatherNode, const char *nodeName, const char *value);
XMLElement *xmlAddNode(XMLDocument& doc, XMLNode *fatherNode, const char *nodeName, int value);
XMLElement *xmlAddNode(XMLDocument& doc, XMLNode *fatherNode, const char *nodeName, double value);
XMLElement *xmlAddNode(XMLDocument& doc, XMLNode *fatherNode, const char *nodeName, float value);



///< 设置节点属性
void xmlSetNodeAttr(XMLElement *nodeName, const char *attrName, const char *value);


///< 获取nodeName节点的某个属性值
void xmlGetNodeAttr(XMLElement *nodeName, const char *attrName, char *buf, int bufLen);
void xmlGetNodeAttr(XMLElement *nodeName, const char *attrName, int *value);
void xmlGetNodeAttr(XMLElement *nodeName, const char *attrName, double *value);
void xmlGetNodeAttr(XMLElement *nodeName, const char *attrName, float *value);

///< 获取fatherNode节点下nodeName节点的某个属性值
void xmlGetNodeAttr(XMLElement *fatherNode, const char *nodeName, const char *attrName, char *buf, int bufLen);
void xmlGetNodeAttr(XMLElement *fatherNode, const char *nodeName, const char *attrName, int *value);
void xmlGetNodeAttr(XMLElement *fatherNode, const char *nodeName, const char *attrName, double *value);
void xmlGetNodeAttr(XMLElement *fatherNode, const char *nodeName, const char *attrName, float *value);


///< 获取节点实体值
void xmlGetChildNode(XMLElement *fatherNode, const char *nodeName, bool *value);
void xmlGetChildNode(XMLElement *fatherNode, const char *nodeName, int *value);
void xmlGetChildNode(XMLElement *fatherNode, const char *nodeName, float *value);
void xmlGetChildNode(XMLElement *fatherNode, const char *nodeName, double *value);
void xmlGetChildNode(XMLElement *fatherNode, const char *nodeName, char *buf, int bufLen);

}

