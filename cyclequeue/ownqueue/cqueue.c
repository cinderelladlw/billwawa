#include "cqueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encqueue(list_pointer *ptr, list_pointer node);
void delcqueue(list_pointer *ptr, list_pointer trail, list_pointer node);
void discqueue(list_pointer ptr);

int main()
{
  list_pointer *shit = NULL;
  list_pointer boy;
  printf("1............\n");
  encqueue(shit, boy);
  printf("1............\n");
  discqueue(*shit);
  printf("1............\n");
  return 0;
}

 
void encqueue(list_pointer *ptr, list_pointer node)
{
  list_pointer tmp = (list_pointer)malloc(sizeof(struct list_node));
  tmp -> data = 50;  
  printf("2............\n");
  if(*ptr) {
  printf("2............\n");
    tmp -> link = node -> link;
  printf("2............\n");
    node -> link = tmp -> link;
  printf("2............\n");
  } else {
  printf("2............\n");
    tmp -> link = NULL;
    *ptr = tmp;
  }
}
   
void delcqueue(list_pointer *ptr, list_pointer trail, list_pointer node)
{
  if(trail)
    trail -> link = node -> link;
  else
    *ptr = (*ptr) -> link;
  free(node);
}

void discqueue(list_pointer ptr)
{
  printf("the list contains:\n");
  for(;ptr; ptr = ptr -> link) 
    printf("%4d", ptr -> data);
  printf("\n");
}

