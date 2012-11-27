#include <stdio.h>
#include <stdlib.h>
//定义结点
typedef struct __Node{
	int data;
	struct __Node *pre;
	struct __Node *next;
}Node;
//定义带头结点的双向链表
typedef struct __doublyLinkedList{
	Node * head;
}dLinkedList;
//初始化：头结点置空
void init(dLinkedList *L){
	if(L == NULL){
		printf("链表异常/n");
		return;
	}
	L->head = NULL;
}
//
void insert(dLinkedList *L, int data){
	Node *p = NULL;
	if(L == NULL){
		printf("双向链表不存在/n");
		return;
	}
	
	p = (Node*)malloc(sizeof(Node));
	if(p == NULL){
		printf("内存分配失败!/n");
		return;
	}
	p->data = data;
	p->next = L->head;
	if(L->head != NULL){
		L->head->pre = p;
	}
	p->pre = NULL;
	L->head = p;
}
Node *search(dLinkedList L, int data){
	Node *p = NULL;
	if(L.head == NULL){
		printf("链表为空/n");
		return NULL;
	}
	p = L.head;
	
	while(p != NULL && p->data != data){
		p = p->next;
	}
	if(p != NULL){
		printf("查找值为 %d的元素成功/n", data);
		return p;
	}
	else{
		printf("查找值为 %d的元素失败/n", data);
		return NULL;
	}
}
void deleteFirstData(dLinkedList *L){
	Node *p = NULL;
	if(L == NULL){
		printf("双向链表异常!/n");
		return;
	}
	if(L->head == NULL){
		printf("双向链表为空!/n");
		return;
	}
	
	p = L->head;
	//only one element
	if(p->next == NULL){
		L->head = NULL;
		free(p);
		p = NULL;
		printf("成功删除第一个元素!/n");
		return;
	}
	else{
		L->head = p->next;
		L->head->pre = NULL;
		free(p);
		p = NULL;
		printf("成功删除第一个元素!/n");
		return;
	}
	
}
void deleteData(dLinkedList *L, int data){
	Node *p = NULL;
	Node *pre = NULL;
	printf("删除查找中.../n");
	if((p = search(*L, data)) == NULL){
		printf("删除值为 %d的元素失败/n", data);
		return;
	}
	else{
		//first element
		if(p == L->head){
//			deleteFirstData(L, data);
			deleteData(L, data);
//			deleteFirstData(&L);
			return;
		}
		//last element
		else if(p->next == NULL){
			pre = p->pre;
			pre->next = NULL;
			free(p);
			p = NULL;
			printf("删除最后一个元素成功/n/n");
			return;
		}
		else{
			pre = p->pre;
			pre->next = p->next;
			p->next->pre = pre;
			free(p);
			p = NULL;
			printf("删除值为 %d的元素成功/n/n", data);
			return;
		}
	}
}
void traversal(dLinkedList L){
	Node *p = NULL;
	if(L.head == NULL){
		printf("双向链表为空!/n");
		return;
	}
	p = L.head;
	while(p != NULL){
		printf("%d ", p->data);
		p = p->next;
	}
	printf("/n遍历成功/n/n");
}
void destroy(dLinkedList *L){
	Node *p = NULL;
	Node *temp = NULL;
	if(L == NULL){
		printf("链表异常/n");
		return;
	}
	printf("开始销毁链表.../n");
	p = L->head;
	while(p != NULL){
		temp = p;
		p = p->next;
		free(temp);
		temp = NULL;
	}
	L->head = NULL;
	printf("销毁成功!/n");
}
int main(int argc, char **args){
	dLinkedList L;
	int i;
	memset(&L, 0, sizeof(dLinkedList));
	init(&L);
	traversal(L);
	for(i=0;i<20;++i){
		insert(&L, i);
	}
	traversal(L);
	deleteFirstData(&L);
	deleteFirstData(&L);
	traversal(L);
	
	deleteFirstData(&L);
	deleteData(&L, 10);
	deleteData(&L, 16);
	deleteData(&L, 0);
	traversal(L);
	
	insert(&L, 100);
	insert(&L, 99);
	insert(&L, 98);
	insert(&L, 97);
	traversal(L);
	deleteData(&L, 99);
	deleteData(&L, 97);
	deleteData(&L, 96);
	traversal(L);
	destroy(&L);
	return 0;
}
