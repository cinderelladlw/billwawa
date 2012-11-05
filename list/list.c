#include<stdio.h>
#include<stdlib.h>
struct linknode //建立链表节点
{
  int data; //需要更通用的数据类型
  struct linknode *next;
};
struct link
{
  struct linknode *head;
  struct linknode *tail;
};
struct linknode *create() //创建链表，接受INT型值
{
  int datas;
  struct linknode *head,*temp,*tail;
  head=tail=NULL;
  while(scanf("%d",&datas)==1) //输入方式有待改进
  {
  temp=(struct linknode *)malloc(sizeof(struct linknode));
  if(temp==NULL)
  printf("allocate erro!");
  else
  {
  temp->data=datas;
  temp->next=NULL;
  if(head==NULL)
  head=tail=temp;
  else
  {
  tail->next=temp;
  tail=temp;
  }
  }
  }
  return head;
}
void print(struct linknode *head) //打印链表
{
  struct linknode *p;
  p=head;
  while(p)
  {
  printf("%d\t",p->data);
  p=p->next;
  }
}
struct linknode *find(struct linknode *head,int datas) //查找特定的值的节点
{
struct linknode *p;
p=head;
while(p->data!=datas&&p->next!=NULL)
{
p=p->next;
}
if(p->data==datas)
return p;
else
return NULL;
}
struct linknode *findAhead(struct linknode *head,int datas) //查找特定值得前一个节点
{
struct linknode *p,*q;
q=NULL;
p=head;
while(p->data!=datas&&p->next!=NULL)
{
q=p;
p=p->next;
}
if(p->data==datas)
return q;
else
return NULL;
}
struct linknode *enterTohead(struct linknode *head,int datas) //在头部添加节点
{ //改变了头节点指针，需重新赋值
struct linknode *enter;
enter=(struct linknode *)malloc(sizeof(struct linknode));
if(enter==NULL)
printf("allocate erro!");
enter->data=datas;
enter->next=NULL;
if(head==NULL)
head=enter;
else
{
enter->next=head;
head=enter;
}
return head;
}
struct linknode *enterTotail(struct linknode *head,int datas) //在尾部添加节点
{
struct linknode *enter,*p;
p=head;
enter=(struct linknode *)malloc(sizeof(struct linknode));
if(enter==NULL)
printf("allocate erro!");
enter->data=datas;
enter->next=NULL;
if(head==NULL)
{
head=enter;
}
else
{
while(p->next)
{
p=p->next;
}
p->next=enter;
}
return head;
}
struct linknode *enterTovalue(struct linknode *head,int value,int datas) //在特定的位置添加节点
{
struct linknode *enter,*fd,*p;
p=findAhead(head,value);
fd=find(head,value);
if(fd==NULL)
printf("find no member is value.");
enter=(struct linknode *)malloc(sizeof(struct linknode));
enter->data=datas;
enter->next=NULL;
if(enter==NULL)
printf("allocate erro!");
if(fd==head)
{
enter->next=head;
head=enter;
}
else
{
p->next=enter;
enter->next=fd;
}
return head;
}
struct linknode *delet(struct linknode *head,int datas) //删除节点
{
struct linknode *delet,*p;
p=findAhead(head,datas);
delet=find(head,datas);
if(!delet)
return NULL;
else
{
p->next=delet->next;
free(delet);
return head;
}
}
void main() //链表建立测试
{
struct linknode *head,*fd;
head=create();
print(head);
fd=findAhead(head,4);
if(fd==NULL)
{
printf("Ahead of found is NULL.");
printf("\n");
}
else
{
printf("\n");
printf("%d\n",fd->data);
}
print(head=enterTohead(head,88));
printf("\n");
print(enterTotail(head,77));
printf("\n");
print(head=enterTovalue(head,5,413));
printf("\n");
head=delet(head,6);
if(head)
print(delet(head,6));
else
printf("have no this number.");
printf("\n");
}
