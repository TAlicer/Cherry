#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    evtNone,
    evtPrinterChanged,
    evtPrinterStatus,
    evtPrinterCondition,
    evtPrinterConditionCleared,
    evtPrinterJobStatus,
    evtPrinterJobEndState,
    
	evtScannerChanged,
    evtScannerStatus,
    evtScannerCondition,
    evtScannerConditionCleared,
    evtScannerJobStatus,
    evtScannerJobEndState,
    evtScannerAvailable,
    
    // psuedo-events
    evtPrinterConfigChanged,
    evtPrinterCapsChanged,
    evtPrinterTicketChanged
}
WSDEVENT;

typedef struct tag_wsd_subscription
{
    char            addr[32];
    unsigned short  port;
    WSDEVENT        event;                          ///< the thing we are subscribing to
    time_t          subscibed;                      ///< time when subscription was created
    time_t          expires;                        ///< time when subscription expires
    int             push;                           ///< set non-0 to indicate event should be sent/triggered
    struct tag_wsd_subscription *next; 
 
}WSEVTSUBS, *PWSEVTSUBS;

static PWSEVTSUBS printerEventHead = NULL;
static PWSEVTSUBS printerEventTail = NULL;
static PWSEVTSUBS scannerEventHead = NULL;
static PWSEVTSUBS scannerEventTail = NULL;

static PWSEVTSUBS create_linked_node(WSDEVENT evcode, char *address, unsigned short port)
{
	PWSEVTSUBS eventNode = NULL;
	
	if(0!=evcode && (NULL==address || 0==port))
	{
		return NULL;
	}
	
	eventNode = (PWSEVTSUBS)malloc(sizeof(WSEVTSUBS));
	if(	NULL == eventNode)
	{
		return NULL;
	}

	memset(eventNode, 0, sizeof(WSEVTSUBS));
	
	if(0==evcode)
	{
		printf("0==evcode\n");
		return eventNode;
	}
	
	eventNode->event = evcode;
	eventNode->port = port;
	strncpy(eventNode->addr, address, sizeof(eventNode->addr));

	return eventNode;
}

int init_subscribe_event(PWSEVTSUBS *eventHead)
{
	if(NULL != *eventHead)
	{
		free(*eventHead);
		*eventHead = NULL;
	}
	
	*eventHead = create_linked_node(evtNone, NULL, 0);
	if(NULL == *eventHead)
	{
		return -1;
	}
	
	return 0;
}

static int add_subscribe_printer_event(WSDEVENT evcode, char *address, unsigned short port)
{
	PWSEVTSUBS new_Node = NULL;
	
	if(NULL == printerEventHead)
	{
		return -1;
	}
	
	new_Node = create_linked_node(evcode, address, port);
	if(NULL == new_Node)
	{
		return -1;
	}
	
	if(printerEventHead->next == NULL)       	//如果为空链表
	{
		printerEventHead->next = new_Node;   	//头指针指向第一个节点
		printerEventTail = new_Node;        	//尾指针指向第一个节点
	}
	else
	{
		printerEventTail->next = new_Node;  	//尾指针指向的节点(上一个节点)的指针域指向新插入的节点
		printerEventTail = new_Node;        	//这两句不能反
	}
	return 0;
}

static int add_subscribe_scanner_event(WSDEVENT evcode, char *address, unsigned short port)
{
	PWSEVTSUBS new_Node = NULL;
	
	new_Node = create_linked_node(evcode, address, port);
	if(NULL == new_Node)
	{
		return -1;
	}
	
	if(scannerEventHead->next == NULL)       	//如果为空链表
	{
		scannerEventHead->next = new_Node;   	//头指针指向第一个节点
		scannerEventTail = new_Node;        	//尾指针指向第一个节点
	}
	else
	{
		scannerEventTail->next = new_Node;  	//尾指针指向的节点(上一个节点)的指针域指向新插入的节点
		scannerEventTail = new_Node;        	//这两句不能反
	}
	return 0;
}

static PWSEVTSUBS del_subscribe_event_byEvcode(PWSEVTSUBS eventLink, WSDEVENT evcode)
{
    PWSEVTSUBS  tmp = eventLink;
    PWSEVTSUBS  ptr = eventLink;
    int number = 0;
    while (ptr)
    {
        if (ptr->event == evcode)
        {
            ++number;
        }
        ptr = ptr->next;
    }

    while (number--)
    {
        if (tmp->event == evcode)
        {
            PWSEVTSUBS  tmp1 = tmp;
            tmp = tmp->next;
            free(tmp1);
            eventLink = tmp;
        }
        else
        {
            PWSEVTSUBS  tmp = eventLink;
            while (tmp)
            {
                if (tmp->next!=NULL)
                {
                    if (tmp->next->event == evcode)
                    {
                        PWSEVTSUBS  tmp1 = NULL;
                        tmp1 = tmp->next->next;
                        free(tmp->next);
                        tmp->next = tmp1;
                        tmp = tmp->next;
                    }
                    else
                    {
                        tmp = tmp->next;
                    }
                }
                else
                {
                    break;
                }
            }
        }
    }
    return eventLink;
}

static PWSEVTSUBS del_subscribe_event_byIp(PWSEVTSUBS eventLink, PWSEVTSUBS *linktail, char *address)
{
    PWSEVTSUBS  tmp = eventLink;
    PWSEVTSUBS  ptr = eventLink;
    int number = 0;
    while (ptr)
    {
        //if (ptr->event == evcode)
		if(0==strcmp(ptr->addr, address))
        {
            ++number;
        }
        ptr = ptr->next;
    }

    while (number--)
    {
        //if (tmp->event == evcode)
		if(0==strcmp(tmp->addr, address))
        {
            PWSEVTSUBS  tmp1 = tmp;
            tmp = tmp->next;
            free(tmp1);
            eventLink = tmp;
        }
        else
        {
            PWSEVTSUBS  tmp = eventLink;
            while (tmp)
            {
                if (tmp->next!=NULL)
                {
                    //if (tmp->next->event == evcode)
					if(0==strcmp(tmp->next->addr, address))
                    {
                        PWSEVTSUBS  tmp1 = NULL;
                        tmp1 = tmp->next->next;
                        free(tmp->next);
                        tmp->next = tmp1;
                        tmp = tmp->next;
                    }
                    else
                    {
                        tmp = tmp->next;
						*linktail = tmp;
                    }
                }
                else
                {
					*linktail = tmp;
                    break;
                }
            }
        }
    }

    return eventLink;
}

int print_node(PWSEVTSUBS tmpEvent)
{ 
    if(!tmpEvent)
    return -1;
 
    PWSEVTSUBS p;
    p=tmpEvent->next;
	
    while(p!=NULL)
    {
      printf("event=[%d], port=[%d], addr=[%s]\n", p->event, p->port, p->addr);
      p=p->next;
    }
	printf("\n");
    return 0;
}

int print_specific(WSDEVENT evcode, PWSEVTSUBS tmpEvent)
{
	if(!tmpEvent)
    return -1;
 
    PWSEVTSUBS p;
    p=tmpEvent->next;
	
    while(p!=NULL)
    {
		if(evcode==p->event)
		{
			printf("event=[%d], port=[%d], addr=[%s]\n", p->event, p->port, p->addr);
		}
		p=p->next;
    }
	printf("\n");
    return 0;
}

void destroy(PWSEVTSUBS head)
{
   PWSEVTSUBS p;
   while (head!=NULL)//当还有头结点存在时
   {
      p=head;//头结点是待删除结点
      head=head->next;//先连
	  
	  printf("====p->port=[%d]\n", p->port);
	  p->next = NULL;
      free(p);//后断
   }
}

int main()
{	
	PWSEVTSUBS tmpEvent = NULL;
	init_subscribe_event(&printerEventHead);
    add_subscribe_printer_event(evtPrinterChanged, "192.168.1.1", 1111);
	add_subscribe_printer_event(evtPrinterStatus, "192.168.1.2", 2222);
	//add_subscribe_printer_event(evtPrinterChanged, "192.168.1.3", 3333);
	//add_subscribe_printer_event(evtPrinterStatus, "192.168.1.4", 4444);
	//add_subscribe_printer_event(evtPrinterChanged, "192.168.1.5", 5555);

	tmpEvent = printerEventHead;
    print_node(tmpEvent);
	
	//del_subscribe_event_byEvcode(printerEventHead, evtPrinterChanged);
	del_subscribe_event_byIp(printerEventHead, &printerEventTail, "192.168.1.2");
	del_subscribe_event_byIp(printerEventHead, &printerEventTail, "192.168.1.3");
	//destroy(printerEventHead);
	
	printf("-----------del end----------\n");
	print_node(tmpEvent);
	add_subscribe_printer_event(evtPrinterStatus, "192.168.1.8", 8888);
	add_subscribe_printer_event(evtPrinterChanged, "192.168.1.9", 9999);
	printf("-----------print specific----------\n");
	//print_specific(evtPrinterChanged, tmpEvent);
	print_node(tmpEvent);
    return 0;
}