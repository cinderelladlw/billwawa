#include "list.h"

pNode listInit(pNode l)
{
  pNode p;
  p = (pNode)malloc(sizeof(Node));
  p -> next = NULL;
  l = p;
  return l;
}

int listCreate(pNode l, int len)
{
  pNode p;
  int i;
  p = l -> next;
  
  printf("insert the number of list:");
  scanf("%d", &len);
  
  for (i = 0; i < len; i++) {
    Element insertnum;
    printf("insert[%d]:", i + 1);
    scanf("%d", &insertnum);
    p = (pNode)malloc(sizeof(Node));
    p -> elem = insertnum;
    p -> next = l -> next; 
    l -> next = p; 
  }
  return 0;
}

int listPrint(pNode l)
{
  pNode p;
  p = l -> next;
  while(p) {
    printf(":%d\n", p -> elem); 
    p = p -> next;
  }
  return 0;
}






