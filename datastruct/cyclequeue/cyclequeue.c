#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 10

typedef struct _queue {
  char elems[MAXSIZE];
  char front, rear;
}queue;

int initqueue(queue *q)
{
  q->front = q->rear = 0;
  return OK;
}

int showqueue(queue *q)
{
  int i;
  if(q->front == q->rear) {
    printf("empty queue\n");
    return ERROR;
  }
  printf("elements of queue:\n");
  for(i=((q->front)%MAXSIZE);i<q->rear;i=((i+1)%MAXSIZE))
  printf(" %c",q->elems[i]);
  printf("\n");
  printf("队首元素为%c\n",q->elems[q->front]);
  printf("队尾元素为%c\n",q->elems[q->rear-1]);
  return OK;
}

//向队尾插入元素e
int InQueue(queue *q,char e)
{
  if((q->rear+1)%MAXSIZE==q->front) {
    printf("空间不足\n");
    return(OVERFLOW);
  }
  q->elems[q->rear]=e;
  q->rear=(q->rear+1)%MAXSIZE;
  return OK;
}

//从队首删除元素
int OutQueue(queue *q)
{
  if(q->front==q->rear) {
    printf("队列为空\n");
    return ERROR;
  }
  printf("被删除的队首元素为%c\n",q->elems[q->front]);
  q->front=(q->front+1)%MAXSIZE;
  return OK;
}

//队列中的元素个数
int Length(queue *q)
{
  return (q->rear-q->front+MAXSIZE)%MAXSIZE;
}

int main()
{
  queue q;
  initqueue(&q);
  showqueue(&q);

  printf("对尾插入元素...\n");
  InQueue(&q,'a');
  InQueue(&q,'b');
  InQueue(&q,'c');
  InQueue(&q,'d');
  showqueue(&q);
  printf("队列中的元素个数为%d\n",Length(&q));

  printf("队首删除元素..\n");
  OutQueue(&q);
  showqueue(&q);
  return 0;
}

