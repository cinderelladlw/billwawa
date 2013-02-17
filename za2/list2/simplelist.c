#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define ERROR 0;
typedef struct LNode
{
    int data;
    struct LNode *next;
}LNode,*LinkList;
LinkList InitList(LinkList L)
{
    LinkList node = NULL;
    node = (LinkList)malloc(sizeof(LNode));
    if(!node)
    {
        return ERROR;
    }
    node->next = NULL;
    L = node;
    return L;
}
int ListLength(LinkList L)
{
    LinkList p = NULL;
    int count = 0;
    p = L;
    while(p->next)
    {
        count++;
        p = p->next;
    }
    return count;
}
LinkList CreateList_L(LinkList L,int n)
{
    int i;
    LinkList p = NULL;
    for(i=n;i>0;i--)
    {
        p = (LinkList)malloc(sizeof(LNode));
        scanf("%d",&p->data);
        p->next = L->next;
        L->next = p;
    }
    return L;
}
LinkList ListInsert(LinkList L,int i,int e)
{
    int j = 0;
    LinkList s = NULL,p = NULL;
    p = L;
    while(p&&j<i-1)
    {
        p = p->next;
        j++;
    }
    if(!p||j>i-1)
    {
        printf("输入的位置不合法！！！\n");
        return L;
    }
    s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return L;
}
LinkList ListDelete(LinkList L,int i)
{
    int j;
    LinkList q = NULL,p = NULL;
    p = L;
    j = 0;
    while(p->next&&j<i-1)
    {
        p = p->next;
        j++;
    }
    if(!(p->next)||j>i-1)
    {
        printf("输入的位置不合法！！！\n");
        return L;
    }
    q = p->next;
    p->next = q->next;
    free(q);
    return L;
}
int GetElem(LinkList L,int i)
{
    int j,e;
    LinkList p = NULL;
    if(i<1||i>ListLength(L))
    {
         printf("输入的位置不合法！！！\n");
         return;
    }
    p = L->next;
    j = 1;
    while(j<i)
    {
        p = p->next;
        j++;
    }
    e = p->data;
    printf("第%d位的数据元素为%d\n",i,e);
}
int main()
{
  int n,m,i,e;
  LinkList L = NULL, p = NULL;
  L = InitList(L);
  L = CreateList_L(L,3);
  printf("...\n"); 
  p = L -> next;
  while(p != NULL) {
    printf(":%d\n", p -> data);
    p = p -> next;
  } 
  return 0;
}

