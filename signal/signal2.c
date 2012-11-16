#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

static int alarm_fired = 0;
void ding(int sig)
{
  alarm_fired = 1;
}

int main()
{
  pid_t pid;
  printf("alarm start..\n");
  pid = fork();
  switch(pid) {
    case -1:
      perror("fork error ..\n");
      exit(1);
    case  0:
      sleep(5);
      kill(getppid(), SIGALRM);
      exit(1);
  }
  printf("waiting for alarm to go off..\n");
  (void)signal(SIGALRM, ding);
  pause();
  if(alarm_fired)
    printf("Ding..\n");
  printf("done\n");
  return 0;
}
  
