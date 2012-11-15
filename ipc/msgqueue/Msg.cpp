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
  
/*消息缓冲区*/  
struct message  
{  
  long msg_type;          //消息标识符  
  char msg_text[BUFSZ];   //消息，这个字段不但可以存储字符，还可以存储其他类型数据  
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
  /*用户输入消息,到msg.msg_text去*/  
  if((fgets(msg.msg_text,BUFSZ,stdin))==NULL)  
  {  
    cout << "no message";  
    exit(1);  
  }  
  /*消息标识符*/  
  msg.msg_type = getpid();  
  len = strlen(msg.msg_text);  
  /*发送消息*/  
  if((msg1.msgsnd(qid,&msg,len,0))<0)  
  {  
    cout << "message posted";  
    exit(1);  
  }  
  /*从消息队列读出消息,到msg*/  
  if(msg1.msgrcv(qid,&msg,BUFSZ,0,0)<0)  
  {  
    perror("msgrcv");  
    exit(1);  
  }  
  printf("message is:%s\n",(&msg)->msg_text);  
  /*消息队列控制，这里删除消息队列*/  
  if((msg1.msgctl(qid,IPC_RMID,NULL))<0)  
  {  
    perror("msgctl");  
    exit(1);  
  }  
  exit(0);  
}
