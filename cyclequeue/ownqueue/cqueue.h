#ifndef _cqueue_
#define _cqueue_
#include <stdio.h>

typedef struct list_node *list_pointer;
struct list_node {
//  char msg[50];
  int data;
  list_pointer link;
};

list_pointer p = NULL;

#endif
