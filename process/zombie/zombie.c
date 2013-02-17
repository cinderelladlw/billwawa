#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main()
{
  pid_t pid = fork();
  if(pid == 0) {
    printf("child:[%d]\n", getpid());
    sleep(5);
    exit(0);
  } else {
    printf("parent:[%d]\n", getpid());
#ifdef SIGNA
    signal(SIGCHLD, SIG_IGN);
#endif
    sleep(5);
    printf("sleeping..\n");
    sleep(5);
    printf("sleeping..\n");
    sleep(3);
#ifdef WAIT 
    printf("wait:[%d]\n", wait(NULL));
#endif
    sleep(10);
  }
  return 0;
}
