#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/msg.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <string.h>  
  
#define BUFSZ 512  
  
/*消息缓冲区*/  
struct message  
{  
  long msg_type;          //消息标识符  
  char msg_text[BUFSZ];   //消息，这个字段不但可以存储字符，还可以存储其他类型数据  
};  
  
int main()  
{  
  int qid;  
  /*IPC关键字*/  
  key_t key;  
  int len;  
  struct message msg;  
  /*产生IPC关键字,用当前目录*/  
  if((key=ftok(".",'a'))==-1)  
  {  
    perror("ftok");  
    exit(1);  
  }  
  /*创建一个新的消息队列,返回消息队列标识符*/  
  if((qid=msgget(key,IPC_CREAT|0666))==-1)  
  {  
    perror("msgget");  
    exit(1);  
  }  
  printf("opened queue %d\n",qid);  
  puts("Please enter the message to queue:");  
  /*用户输入消息,到msg.msg_text去*/  
  if((fgets(msg.msg_text,BUFSZ,stdin))==NULL)  
  {  
    puts("no message");  
    exit(1);  
  }  
  /*消息标识符*/  
  msg.msg_type = getpid();  
  len = strlen(msg.msg_text);  
  /*发送消息*/  
  if((msgsnd(qid,&msg,len,0))<0)  
  {  
    perror("message posted");  
    exit(1);  
  }  
  /*从消息队列读出消息,到msg*/  
  if(msgrcv(qid,&msg,BUFSZ,0,0)<0)  
  {  
    perror("msgrcv");  
    exit(1);  
  }  
  printf("message is:%s\n",(&msg)->msg_text);  
  /*消息队列控制，这里删除消息队列*/  
  if((msgctl(qid,IPC_RMID,NULL))<0)  
  {  
    perror("msgctl");  
    exit(1);  
  }  
  exit(0);  
}
