#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

char choose;
int input;
bool unbalanced = false;
struct node
{
  int data;
  int bf;//平衡因子balance factor
  struct node *lchild;
  struct node *rchild;
};
typedef struct node *BST;
BST R = NULL;

void Choose()
{
  printf("i) Insert a point\n"
         "d) Delete a point\n"
         "e) exit\n"
         "Input your choose:");
  scanf(" %c", &choose);
}

int Height(BST T)     
{
  if (T == NULL)
    return -1;
  else
    return T->bf;
}

int Max(int A, int B)
{
  return ((A > B) ? A:B);
}

BST SingleRotateWithRight(BST K2)          
{
  BST K1;
  K1 = K2->rchild;
  K2->rchild = K1->lchild;
  K1->lchild = K2;
  K2->bf = Max(Height(K2->lchild), Height(K2->rchild)) + 1;
  K1->bf = Max(Height(K1->lchild), Height(K1->rchild)) + 1;
  return K1;
}

BST SingleRotateWithLeft(BST K2)           
{
  BST K1;
  K1 = K2->lchild;
  K2->lchild = K1->rchild;
  K1->rchild = K2;
  K2->bf = Max(Height(K2->lchild), Height(K2->rchild)) + 1;
  K1->bf = Max(Height(K1->lchild), Height(K1->rchild)) + 1;
  return K1;
}

BST DoubleRotateWithLeft(BST K3)           
{
  K3->lchild = SingleRotateWithRight(K3->lchild);
  return SingleRotateWithLeft(K3);
}

BST DoubleRotateWithRight(BST K3)          
{
  K3->rchild = SingleRotateWithLeft(K3->rchild);
  return SingleRotateWithRight(K3);
}

void OUT(BST T)                
{
  if (T->lchild)
  {
    printf("Left\t%d\t[parent:%d]\n", T->lchild->data, T->data);
    OUT(T->lchild);
  }
  if (T->rchild)
  {
    printf("Right\t%d\t[parent:%d]\n", T->rchild->data, T->data);
    OUT(T->rchild);
  }
}

BST Rotate(BST T)              
{
  if (Height(T->lchild) - Height(T->rchild) == 2)
  {
    if (Height(T->lchild->lchild) >= Height(T->lchild->rchild))
    {
      T = SingleRotateWithLeft(T);
    }
    else
    {
      T = DoubleRotateWithLeft(T);
    }
  }
  if (Height(T->rchild) - Height(T->lchild) ==2)
  {
    if (Height(T->rchild->rchild) >= Height(T->rchild->lchild))
    {
      T = SingleRotateWithRight(T);
    }
    else
    {
      T = DoubleRotateWithRight(T);
    }
  }
  return T;
}

BST AVLInsert(BST T)           
{
  if (T == NULL)
  {
    T = (BST)malloc(sizeof(struct node));
    T->data = input;
    T->lchild = T->rchild = NULL;
    T->bf = 0;
  }
  else if (input < T->data)
  {
    T->lchild = AVLInsert(T->lchild);
    if (Height(T->lchild) - Height(T->rchild) == 2)
    {
      if (input < T->lchild->data)
      {
        T = SingleRotateWithLeft(T);           
      }
      else
      {
        T = DoubleRotateWithLeft(T);           
      }
    }
  }
  else if (input > T->data)
  {
    T->rchild = AVLInsert(T->rchild);
    if (Height(T->rchild) - Height(T->lchild) == 2)
    {
      if (input > T->rchild->data)
      {
        T = SingleRotateWithRight(T);          
      }
      else
      {
        T = DoubleRotateWithRight(T);          
      }
    }
  }
  T->bf = Max(Height(T->lchild), Height(T->rchild)) + 1;
  return T;
}

void Output(BST T)
{
  if (T == NULL)
  {
    printf("None\n");
  }
  else
  {
    printf("%d\troot\n", T->data);
    OUT(T);
  }
}

void Insert()
{
  printf("\nInput the point your want to Insert: ");
  scanf("%d", &input);
  R = AVLInsert(R);
  Output(R);
}

BST AVLDelete(BST T, int key)
{
  if (T == NULL)
    return NULL;
  if (key == T->data) {
    if (T->lchild == NULL) {
      BST temp = T;
      T = T->rchild;
      free(temp);
    } else {     
      BST temp = T->lchild;    
      while (temp->rchild != NULL) {       
        temp = temp->rchild;
      }
      T->data = temp->data;     
      T->lchild = AVLDelete(T->lchild, temp->data);
      T->bf = Max(Height(T->lchild), Height(T->rchild))+1;

      //由于删除了树的左枝，有可能导致平衡因子的变化
      if (Height(T->rchild) - Height(T->lchild) == 2) {
        if (Height(T->rchild->lchild) > Height(T->rchild->rchild)) {
          T = DoubleRotateWithRight(T);          
        } else {
          T = SingleRotateWithRight(T);    
        }      
      }
    }   
  } else if (key < T->data) {
    T->lchild = AVLDelete(T->lchild, key);
    T->bf = Max(Height(T->lchild), Height(T->rchild))+1;

    if (Height(T->rchild) - Height(T->lchild) == 2) {
      if (Height(T->rchild->lchild) > Height(T->rchild->rchild)) {
        T = DoubleRotateWithRight(T);          
      } else {
        T = SingleRotateWithRight(T);      
      }    
    }
  } else {
    T->rchild = AVLDelete(T->rchild, key);
    T->bf = Max(Height(T->lchild), Height(T->rchild))+1;

    if (Height(T->lchild) - Height(T->rchild) == 2) {
      if (Height(T->lchild->rchild) > Height(T->lchild->lchild)) {
        T = DoubleRotateWithLeft(T);           
      } else {
        T = SingleRotateWithLeft(T);      
      }     
    }
  }
  return T;
}

void Delete()
{
  printf("\nInput the point you want to Delete: ");
  scanf("%d", &input);
  R = AVLDelete(R, input);
  Output(R);
}

int main()
{
  while (1)
  {
    Choose();
    switch (choose)
    {
    case 'i':
      Insert();
      break;
    case 'd':
      Delete();
      break;
    case 'e':
      exit(0);
    }
  }
  return 0;
}

