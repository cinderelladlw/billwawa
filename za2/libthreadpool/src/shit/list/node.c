#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  int  id;
  char name[20];
  struct node *next;
} Node, *List;

List init(List l)
{
  List tmp = (List)malloc(sizeof(Node));
  l = tmp;
  tmp -> next = NULL;
  return l;
}

List insert(List l, int a, char *b)
{
  Node *sb = (Node *)malloc(sizeof(Node));
  sb -> id = a;
  strcpy(sb -> name, b);
  Node *sx = l;
  while(sx -> next) {
    sx = sx -> next;
  }
  sx -> next = sb;
  sb -> next = NULL;
  
  return l;
}

int main()
{
  List list;
  list = init(list);
  list = insert(list, 23, "hello boy");
  list = insert(list, 24, "hello girl");
  list = insert(list, 23, "hello boy");
  printf("%d\t%s\n", (*(list->next)).id, (*(list->next)).name);
  printf("%d\t%s\n", (*(list->next->next)).id, (*(list->next->next)).name);
  printf("%d\t%s\n", (*(list->next)).id, (*(list->next)).name);
  return 0;

} 
  
