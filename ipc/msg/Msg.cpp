#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/msg.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <string.h>  
#include <iostream>

using namespace std;
  
#define BUFSZ 512  
  
/*��Ϣ������*/  
struct message  
{  
  long msg_type;          //��Ϣ��ʶ��  
  char msg_text[BUFSZ];   //��Ϣ������ֶβ������Դ洢�ַ��������Դ洢������������  
};  

class Msg
{
  public:
    int qid;
    key_t key; 
    int len;  
    struct message msg;  
  public:
    int msgget(key_t key,int falg);
    int msgsnd(int msqid,const void *ptr,size_t len,int flag);
    ssize_t msgrcv(int msqid,void *ptr,size_t len,long type,int flag);
    int msgctl(int msgqid,int cmd,struct msqid_ds *buf);   
};
  
int main()  
{  
  Msg msg1;
  if((key=ftok(".",'a'))==-1)  
  {  
    perror("ftok");  
    exit(1);  
  }  

  if((qid=msg1.msgget(key,IPC_CREAT|0666))==-1)  
  {  
    perror("msgget");  
    exit(1);  
  }  
  cout << "opened queue %d\n" << qid;  
  cout << "Please enter the message to queue:";  
  /*�û�������Ϣ,��msg.msg_textȥ*/  
  if((fgets(msg.msg_text,BUFSZ,stdin))==NULL)  
  {  
    cout << "no message";  
    exit(1);  
  }  
  /*��Ϣ��ʶ��*/  
  msg.msg_type = getpid();  
  len = strlen(msg.msg_text);  
  /*������Ϣ*/  
  if((msg1.msgsnd(qid,&msg,len,0))<0)  
  {  
    cout << "message posted";  
    exit(1);  
  }  
  /*����Ϣ���ж�����Ϣ,��msg*/  
  if(msg1.msgrcv(qid,&msg,BUFSZ,0,0)<0)  
  {  
    perror("msgrcv");  
    exit(1);  
  }  
  printf("message is:%s\n",(&msg)->msg_text);  
  /*��Ϣ���п��ƣ�����ɾ����Ϣ����*/  
  if((msg1.msgctl(qid,IPC_RMID,NULL))<0)  
  {  
    perror("msgctl");  
    exit(1);  
  }  
  exit(0);  
}
