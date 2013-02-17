#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define ERROR 0

typedef struct LNode LNode;
typedef struct LNode *LinkList;
struct LNode {
  char abc[100];
  LNode *next;
};

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

int ListLength(LinkList L)
{
  LinkList p = NULL;
  int count = 1 ;
  p = L -> next;
  while(p -> next) {
    count++;
    p = p -> next;
  }
  return count;
} 

LinkList CreateList(LinkList L, int n)
{
  int i;
  LinkList p = NULL;
  for(i = n; i >0; i--) {
    p = (LinkList)malloc(sizeof(LNode));
    scanf("%s", &p->abc);
    p -> next = L -> next;
    L -> next = p;
  }
  return L;
}

LinkList PrintList(LinkList L)
{
  LinkList p = NULL;
  p = L -> next;
  while(p) {
    printf("::%s\n", p -> abc);
    p = p -> next;
  }
  return L;
}

  
int main()
{
  LinkList L = NULL;
  L = InitList(L);
  L = CreateList(L, 3);
  L = PrintList(L);
  return 0;
}






