#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  int id;
  char name[20];
  struct node *next;
}Node, *List;

Node *init(List l)
{
  Node *tmp = (Node *)malloc(sizeof(Node));
  if(!tmp)
    return NULL;
  tmp -> next = NULL;
  l = tmp;
  return l;
}

Node *create(List l, int n)
{
  int i;
  Node *tmp = NULL;
  for(i = n; i > 0; i--) {
    tmp = (Node *)malloc(sizeof(Node));
    scanf("%s", tmp -> name);
    tmp -> next = l -> next;
    l -> next = tmp;
  }
  return l;
}

Node *print(List l)
{
  Node *tmp = l -> next;
  while(tmp != NULL) {
    printf(":%s\n", tmp->name);
    tmp = tmp -> next;
  }
  return l;
}


int main()
{
  List L;
  L = init(L);
  L = create(L, 5);
  L = print(L);
  return 0;
} 

 
