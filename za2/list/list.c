#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node Node;
typedef struct node *List;
struct node {
  char name[20];
  struct node *next;
};


List init(List l)
{
  Node *node = (Node *)malloc(sizeof(Node));
  node -> next = NULL;
  l = node;
  return l;
}

List create(List l, char **a, int n)
{
  int i;
  char **p = NULL;
  p = (char **)malloc(n);
  for(i = 0; i < n; i ++)
    *(p+i) = (char *)malloc(strlen(*(a+i))); 
  p = a;
  for(i = 0; i < n; i++) {
    printf(":%s\n", *(p+i));
    Node *node = (Node *)malloc(sizeof(Node));
    strcpy(node -> name, *(p+i));
    node -> next = l -> next; 
    l -> next = node;
  }
  return l;
}

List print(List l)
{
  Node *p = l -> next;
  while(p) {
    printf(":[%s]\n", p -> name);
    p = p -> next;
  } 
  return l; 
}

int main()
{
  List sx;
  sx = init(sx);  
  char *sxx[6] = {"hello", "world", "we", "all", "love", "u"};
  sx = create(sx, sxx, 6);  
  sx = print(sx);  
  return 0;
}










