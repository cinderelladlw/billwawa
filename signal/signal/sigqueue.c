#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void new_op(int, siginfo_t*, void*);

int main(int argc,char**argv)
{
	struct sigaction act;	
	union sigval mysigval;
	int i;
	int sig;
	pid_t pid;		
	char data[10];
	memset(data, 0x00, sizeof(data));
	for(i=0;i < 5;i++)
		data[i]='2';
	mysigval.sival_ptr = data;
	
	sig=atoi(argv[1]);
	pid=getpid();
	
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = new_op;    //�������źŴ�����
	act.sa_flags = SA_SIGINFO;    //��Ϣ���ݿ���
	if(sigaction(sig, &act, NULL) < 0)
	{
		printf("install sigal error\n");
	}
	while(1)
	{
                int j;
                for(j = 0; j < 17; j++) {
//		usleep(100000);
                printf("[%d]\n", j);
          	sigqueue(pid, sig, mysigval);//�򱾽��̷����źţ������ݸ�����Ϣ
		printf("wait for the signal\n");
                }
                if(j == 17) {
                  printf("�������\n");
                  sleep(1000);
                  //break;
                }
                
	}
        while(1);
        return 0;
}
void new_op(int signum, siginfo_t *info, void *myact)//�������źŴ�������ʵ��
{
	int i;
	for(i=0;i<10;i++)
	{
		printf("%c: ",(*( (char*)((*info).si_ptr)+i)));
	}
	printf("handle signal %d over;\n", signum);
        sleep(5);
}

