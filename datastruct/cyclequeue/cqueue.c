#include <stdlib.h>
#include <stdio.h>
/*#include <taskLib.h>*/
struct Node
{
	char ch;
	struct Node *pNextNode;
};

class Circular_Queue_Linked
{
	private :
		Node Head_Node;
		int length;
		Node * head;
		Node * tail;
	public :
		Circular_Queue_Linked();
		bool Insert_Queue(char ch);
		bool Delete_Queue(char *p_ch);
		bool Is_Empty();
		bool Is_Full();	
		void Print_Queue();
		void Clear_Queue();

};

Circular_Queue_Linked::Circular_Queue_Linked()
{
	length = 3;
	head = Head_Node;
	tail = Head_Node;
	Node *CurNode;
	int i=0;
	/* head node */
	for(i = 0; i<length; i++)
	{
		CurNode = (Node *)malloc( sizeof(Node) );
		CurNode->ch = 'a'+i;
		CurNode->pNextNode = Head_Node;
		Head_Node->pNextNode = CurNode;
		printf(" \n\r %c \n\r ",CurNode->ch);
		/*CurNode = CurNode->pNextNode;	*/			
	}
}

void Circular_Queue_Linked::Print_Queue()
{
	int i=0;
	Node *CurNode = Head_Node;
	for(i=0; i<length; i++)
	{
		printf(" \n\r print char --> %c \n\r ",CurNode->ch);
		CurNode = CurNode->pNextNode;		
	}
}

bool Circular_Queue_Linked::Is_Empty()
{
	if(head == tail)
	{
		printf(" \n\r Queue is empty \n\r ");
		return true;
	}
	else
	{
		return false;
	}
}

bool Circular_Queue_Linked::Is_Full()
{
	if(head == tail->pNextNode)
	{
		printf(" \n\r Queue is full \n\r ");
		return true;
	}
	else
	{
		return false;
	}
}

void demo_linked_Queue()
{
	Circular_Queue_Linked CQ_Linked;
	CQ_Linked.Is_Empty();
	CQ_Linked.Print_Queue();	
}


