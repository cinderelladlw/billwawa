#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node Node;
struct node {
  char name[20];
  int id;
  Node *next;
};
typedef struct node *List;

Node *init(List l)
{
  List node = NULL;
  node = (List)malloc(sizeof(Node));
  if(!node)
    return NULL;
  node -> next = NULL;
  l = node;
  return l;
}

Node *create(List l, int n)
{
  int i;
  List tmp = NULL;
  for(i = n; i > 0; i--) {
    tmp = (Node *)malloc(sizeof(Node));
    scanf("%s", (tmp->name));
    tmp -> next = l -> next;
    l -> next = tmp;
  }
  return l;
}

Node *print(List l)
{
  Node *p = NULL;
  p = l -> next;
  while(p != NULL) {
    printf("%s\n", p -> name);
    p = p -> next;
  }
  return l;
}

int main()
{
  List L = NULL;
  L = init(L);
  L = create(L, 3);
  L = print(L);
  return 0;
} 
