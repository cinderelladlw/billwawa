#ifndef SWW
#define SWW
#include <stdio.h>
#include <stdlib.h>
#include "node.h"

//bool isemp(stack s);

int emp(stack s) {
  return ((s->next) == NULL);
}

stack create() {
  stack s;
  s = (stack)malloc(sizeof(struct node));
  if( s == NULL)
    printf("error...\n");
  s -> next = NULL;
  return s;
}

void push(int x, stack s) {
  stack tmp;
  tmp = (stack)malloc(sizeof(struct node));
  if(tmp == NULL) 
    printf("error......\n");
  else {
    tmp -> data = x;
    tmp -> next = s -> next;
    s -> next = tmp;
  }
}

void pop(stack s) {
  stack first;
  if(emp(s))
    printf("e............\n");
  else {
    first = s -> next;
    printf("%d\n", first -> data);
    s -> next = s -> next ->next;
    free(first);
  }
}

#endif
