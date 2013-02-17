#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define ERROR 0;
typedef struct LNode
{
    int data;
    struct LNode *next;
}LNode,*LinkList;
LinkList InitList(LinkList L)
{
    LinkList node = NULL;
    node = (LinkList)malloc(sizeof(LNode));
    if(!node)
    {
        return ERROR;
    }
    node->next = NULL;
    L = node;
    return L;
}
int ListLength(LinkList L)
{
    LinkList p = NULL;
    int count = 0;
    p = L;
    while(p->next)
    {
        count++;
        p = p->next;
    }
    return count;
}
LinkList CreateList_L(LinkList L,int n)
{
    int i;
    LinkList p = NULL;
    for(i=n;i>0;i--)
    {
        p = (LinkList)malloc(sizeof(LNode));
        scanf("%d",&p->data);
        p->next = L->next;
        L->next = p;
    }
    return L;
}
LinkList ListInsert(LinkList L,int i,int e)
{
    int j = 0;
    LinkList s = NULL,p = NULL;
    p = L;
    while(p&&j<i-1)
    {
        p = p->next;
        j++;
    }
    if(!p||j>i-1)
    {
        printf("输入的位置不合法！！！\n");
        return L;
    }
    s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return L;
}
LinkList ListDelete(LinkList L,int i)
{
    int j;
    LinkList q = NULL,p = NULL;
    p = L;
    j = 0;
    while(p->next&&j<i-1)
    {
        p = p->next;
        j++;
    }
    if(!(p->next)||j>i-1)
    {
        printf("输入的位置不合法！！！\n");
        return L;
    }
    q = p->next;
    p->next = q->next;
    free(q);
    return L;
}
int GetElem(LinkList L,int i)
{
    int j,e;
    LinkList p = NULL;
    if(i<1||i>ListLength(L))
    {
         printf("输入的位置不合法！！！\n");
         return;
    }
    p = L->next;
    j = 1;
    while(j<i)
    {
        p = p->next;
        j++;
    }
    e = p->data;
    printf("第%d位的数据元素为%d\n",i,e);
}
void menu()
{
    printf("*************目录**************\n");
    printf("输出单链表中的各元素值        1\n");
    printf("在单链表中插入数据元素        2\n");
    printf("在单链表中删除数据元素        3\n");
    printf("取出单链表中的数据元素        4\n");
    printf("      结束程序                0\n");
    printf("*******************************\n");
}
int main()
{
    int n,m,i,e;
    LinkList L = NULL,p = NULL;
    L = InitList(L);
    printf("请输入元素个数：");
    scanf("%d",&n);
    printf("依次输入%d个数据元素：",n);
    L = CreateList_L(L,n);
    do
    {
        printf("\n \n");
        menu();
        printf("请输入你的选择：");
        scanf("%d",&m);
        switch(m)
        {
            case 1:
                printf("现在链表的元素为：");
                p = L->next;
                while(p!=NULL)
                {
                    printf("%d ",p->data);
                    p = p->next;
                }
                printf("\n");
                break;
            case 2:
                printf("依次输入插入位置和数据元素(空格隔开)：");
                scanf("%d %d",&i,&e);
                L = ListInsert(L,i,e);
                break;
            case 3:
                printf("输入需要删除的元素的位置：");
                scanf("%d",&i);
                L = ListDelete(L,i);
                break;
            case 4:
                printf("输入需要取出的元素的位置：");
                scanf("%d",&i);
                GetElem(L,i);
                break;
            case 0:
                printf("已结束程序！！！\n");
                break;
            default:
                printf("输入错误！！！\n");
        }
    }while(m!=0);
  return 0;
}

