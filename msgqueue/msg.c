#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/msg.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <string.h>  
  
#define BUFSZ 512  
  
/*��Ϣ������*/  
struct message  
{  
  long msg_type;          //��Ϣ��ʶ��  
  char msg_text[BUFSZ];   //��Ϣ������ֶβ������Դ洢�ַ��������Դ洢������������  
};  
  
int main()  
{  
  int qid;  
  /*IPC�ؼ���*/  
  key_t key;  
  int len;  
  struct message msg;  
  /*����IPC�ؼ���,�õ�ǰĿ¼*/  
  if((key=ftok(".",'a'))==-1)  
  {  
    perror("ftok");  
    exit(1);  
  }  
  /*����һ���µ���Ϣ����,������Ϣ���б�ʶ��*/  
  if((qid=msgget(key,IPC_CREAT|0666))==-1)  
  {  
    perror("msgget");  
    exit(1);  
  }  
  printf("opened queue %d\n",qid);  
  puts("Please enter the message to queue:");  
  /*�û�������Ϣ,��msg.msg_textȥ*/  
  if((fgets(msg.msg_text,BUFSZ,stdin))==NULL)  
  {  
    puts("no message");  
    exit(1);  
  }  
  /*��Ϣ��ʶ��*/  
  msg.msg_type = getpid();  
  len = strlen(msg.msg_text);  
  /*������Ϣ*/  
  if((msgsnd(qid,&msg,len,0))<0)  
  {  
    perror("message posted");  
    exit(1);  
  }  
  /*����Ϣ���ж�����Ϣ,��msg*/  
  if(msgrcv(qid,&msg,BUFSZ,0,0)<0)  
  {  
    perror("msgrcv");  
    exit(1);  
  }  
  printf("message is:%s\n",(&msg)->msg_text);  
  /*��Ϣ���п��ƣ�����ɾ����Ϣ����*/  
  if((msgctl(qid,IPC_RMID,NULL))<0)  
  {  
    perror("msgctl");  
    exit(1);  
  }  
  exit(0);  
}
