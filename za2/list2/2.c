#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR 0
typedef struct LNode {
  char name[20];
  struct LNode *next;
}LNode, *LinkList;

LinkList InitList(LinkList L)
{
  LinkList node = NULL;
  node = (LinkList)malloc(sizeof(LNode));
  if(!node) {
    return ERROR;
  }
  node -> next = NULL;
  L = node;
  return L;
}

LinkList ListInsert(LinkList L, int i, char *name)
{
  int j = 0;
  LinkList s = NULL, p = NULL;
  p = L;
  while(p&&j<i-1) {
    p = p -> next;
    j++;
  }
  if(!p||j>i-1) {
    printf("insert error... \n");
    return L;
  }
  s = (LinkList)malloc(sizeof(LNode));
  strcpy(s -> name, name);
  s -> next = p -> next;
  p -> next = s;
  return L;
}
LinkList CreateList_L(LinkList L,int n)
{
    int i;
    LinkList p = NULL;
    for(i=n;i>0;i--)
    {
        p = (LinkList)malloc(sizeof(LNode));
        scanf("%s",&p->name);
        p->next = L->next;
        L->next = p;
    }
    return L;
}

LinkList ListPrint(LinkList L)
{
  LinkList p = NULL;
  p = L -> next;
  while(p != NULL) {
    printf(":%s\n", p -> name);
    p = p -> next;
  }
  return L;
}
 
int main()
{
  int n,m,i,e;
  LinkList L = NULL, p = NULL;
  L = InitList(L);
  L = CreateList_L(L,3);
  printf("...\n"); 
  L = ListPrint(L); 
  return 0;
}
