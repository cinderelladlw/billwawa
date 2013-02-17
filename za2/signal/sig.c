#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

void new_op(int,siginfo_t*,void*);

int main(int argc,char**argv)
{
  printf(".................\n");
	struct sigaction act;	
	int sig;
	sig=atoi(argv[1]);
	
  printf(".................\n");
	sigemptyset(&act.sa_mask);
	act.sa_flags=SA_SIGINFO;
	act.sa_sigaction=new_op;
	
  printf(".................\n");
	if(sigaction(sig,&act,NULL) < 0)
	{
		printf("install sigal error\n");
	}
	
  printf(".................\n");
	while(1)
	{
		sleep(2);
		printf("wait for the signal\n");
	}
        return 0;
}
void new_op(int signum,siginfo_t *info,void *myact)
{
	printf("receive signal %d", signum);
	sleep(5);
}
