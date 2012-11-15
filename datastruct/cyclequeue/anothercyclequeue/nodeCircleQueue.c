#include <stdlib.h>
#include <string.h>
#include "nodeCricleQueue.h"

bool vInitNodeCircleQueue(NodeCircleQueue *cqueue,int initLength,int maxLength){
	cqueue->queue = (Node*)malloc(initLength * sizeof(Node));
	if(cqueue->queue == NULL){
		return false;	
	}
	cqueue->head = cqueue->tail = 0;
	cqueue->initLength = initLength;
	cqueue->maxLength = maxLength;
	return true;
}

void vDestoryNodeCircleQueue(NodeCircleQueue *cqueue){
	free(cqueue->queue);
}

bool vOfferNodeCircleQueue(NodeCircleQueue *cqueue,Node node){
	//queue is full
	if(cqueue->head == ((cqueue->tail+1) % cqueue->initLength)){
		if(cqueue->initLength == cqueue->maxLength)
			return false;

		Node* newQueue;
		int newLength;
		
		newLength = cqueue->initLength * 2;
		if(newLength > cqueue->maxLength)
			newLength = cqueue->maxLength;

		newQueue = (Node*)malloc(newLength * sizeof(Node));
		if(newQueue == NULL)
			return false;
		memcpy(newQueue , cqueue->queue , cqueue->initLength * sizeof(Node));
		free(cqueue->queue);

		cqueue->initLength = newLength;
		cqueue->queue = newQueue;
	}
	//put node at tail,tail++
	*(cqueue->queue + cqueue->tail) = node;
	cqueue->tail = (cqueue->tail + 1) % cqueue->initLength;
	return true;
}

Node vPollNodeCircleQueue(NodeCircleQueue *cqueue){
	//queue is empty
	if(cqueue->tail == cqueue->head)
		return NULL;
	Node node;
	//node = head, head++
	node = *(cqueue->queue + cqueue->head);
	cqueue->head = (cqueue->head + 1) % cqueue->initLength;
	return node;
}

void vTraversalNodeCircleQueue(NodeCircleQueue *cqueue,NodeFunc func,void *args){
	int ptr;
	
	ptr = cqueue->head;
	while(ptr != cqueue->tail){
		func(*(cqueue->queue + ptr),args);
		ptr = (ptr + 1)% cqueue->initLength;
	}
}




