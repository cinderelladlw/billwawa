#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node Node;
struct node {
  int id;
  void (*init)(Node *this);
};

void tp_init(Node *this);

Node *create(int sid)
{
  Node *sx = (Node *)malloc(sizeof(Node));
  sx -> init = tp_init;
  printf("create..\n");
  sleep(3);
  sx -> id   = sid;
}

void tp_init(Node *this)
{
  printf("tp_init:");
  sleep(this -> id);
}

int main()
{
  Node *sb;
  //sb = create(23);
  //(*(sb -> init))(sb);
  sb->init = &tp_init;
  *(sb -> init)(sb);
  
  return 0;
}


