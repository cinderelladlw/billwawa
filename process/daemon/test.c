#include <stdio.h> 
#include <time.h> 

void init_daemon(void);//�ػ����̳�ʼ������ 

int main() 
{ 
  FILE *fp; 
  time_t t; 
  init_daemon();//��ʼ��ΪDaemon 
  
  while(1)//ÿ��һ������test.log��������״̬ 
  { 
    sleep(60);//˯��һ���� 
    if((fp=fopen("test.log","a")) >=0) 
    { 
      t=time(0); 
      fprintf(fp,"Im here at %sn",asctime(localtime(&t)) ); 
      fclose(fp); 
    } 
  } 
}
