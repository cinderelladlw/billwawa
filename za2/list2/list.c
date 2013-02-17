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
        printf("�����λ�ò��Ϸ�������\n");
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
        printf("�����λ�ò��Ϸ�������\n");
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
         printf("�����λ�ò��Ϸ�������\n");
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
    printf("��%dλ������Ԫ��Ϊ%d\n",i,e);
}
void menu()
{
    printf("*************Ŀ¼**************\n");
    printf("����������еĸ�Ԫ��ֵ        1\n");
    printf("�ڵ������в�������Ԫ��        2\n");
    printf("�ڵ�������ɾ������Ԫ��        3\n");
    printf("ȡ���������е�����Ԫ��        4\n");
    printf("      ��������                0\n");
    printf("*******************************\n");
}
int main()
{
    int n,m,i,e;
    LinkList L = NULL,p = NULL;
    L = InitList(L);
    printf("������Ԫ�ظ�����");
    scanf("%d",&n);
    printf("��������%d������Ԫ�أ�",n);
    L = CreateList_L(L,n);
    do
    {
        printf("\n \n");
        menu();
        printf("���������ѡ��");
        scanf("%d",&m);
        switch(m)
        {
            case 1:
                printf("���������Ԫ��Ϊ��");
                p = L->next;
                while(p!=NULL)
                {
                    printf("%d ",p->data);
                    p = p->next;
                }
                printf("\n");
                break;
            case 2:
                printf("�����������λ�ú�����Ԫ��(�ո����)��");
                scanf("%d %d",&i,&e);
                L = ListInsert(L,i,e);
                break;
            case 3:
                printf("������Ҫɾ����Ԫ�ص�λ�ã�");
                scanf("%d",&i);
                L = ListDelete(L,i);
                break;
            case 4:
                printf("������Ҫȡ����Ԫ�ص�λ�ã�");
                scanf("%d",&i);
                GetElem(L,i);
                break;
            case 0:
                printf("�ѽ������򣡣���\n");
                break;
            default:
                printf("������󣡣���\n");
        }
    }while(m!=0);
  return 0;
}

