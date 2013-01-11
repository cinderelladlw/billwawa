#ifndef __NODE_H__
#define __NODE_H__

//元素类型
typedef int Element;

//节点类型
typedef struct node Node;
typedef struct node *pNode;

struct node {
  Element elem;
  struct node *next; 
};

#endif
