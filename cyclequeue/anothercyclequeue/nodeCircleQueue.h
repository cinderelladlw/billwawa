#ifndef _NODECIRCLEQUEUE_H
#define _NODECIRCLEQUEUE_H

typedef enum { false=0, true=!false } bool;

typedef void *Node;

typedef struct NodeCircleQueue_T{
	Node	*queue;
	int	head;
	int	tail;
	int	initLength;
	int	maxLength;
}NodeCircleQueue;

typedef void (*NodeFunc) (Node node,void *args);

bool vInitNodeCircleQueue(NodeCircleQueue *cqueue,int initLength,int maxLength);

void vDestoryNodeCircleQueue(NodeCircleQueue *cqueue);

bool vOfferNodeCircleQueue(NodeCircleQueue *cqueue,Node node);

Node vPollNodeCircleQueue(NodeCircleQueue *cqueue);

void vTraversalNodeCircleQueue(NodeCircleQueue *cqueue,NodeFunc func,void *args);

#endif
