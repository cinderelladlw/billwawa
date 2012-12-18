#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_EMPTY(ptr) (!(ptr))
#define IS_FULL(ptr) (ptr)

typedef struct node Node;
typedef struct node *Queue;
struct node {
  int item;
  struct node *next;
};


void addq(Queue *front, Queue *rear, int i)
{
  Queue temp = (Queue)malloc(sizeof(Node));
  if(temp != NULL)
    printf("malloc ok\n");
//  if(IS_FULL(temp)) {
//    fprintf(stderr, "the memory is full\n");
//  }
  temp -> item = i;
  temp -> next = NULL;
  if(*front)
    (*rear)->next = temp;
  else
    *front = temp;
  *rear = temp;
}

int deleteq(Queue *front)
{
  Queue temp = *front;
  int i;
  i = temp->item;
//  if(IS_EMPTY(*front)) {
//    fprintf(stderr, "the memory is empty\n");
//  }
  *front = temp -> next;
  free(temp);
  return i;
}

int main()
{
  Queue *p = (Queue *)malloc(sizeof(Node)*5);
  Queue *q = (Queue *)malloc(sizeof(Node)*5);
  int sx = 100;
  addq(p, q, sx);
  addq(p, q, sx);
  printf(":%d\n", deleteq(p));
  return 0;
}








