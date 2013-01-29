#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define MAXBUFF 4096

void handler(int sig)
{
  pid_t pid;
  //while ((pid = waitpid(-1, NULL, 0)) > 0)
  //  printf("handler reaped child %d\n", (int)pid);
  //if (errno != ECHILD)
  //  printf("waitpid error\n");
  sleep(1);
  printf("shit...\n");
  return;
}

int main()
{
  int i, n;
  char buf[MAXBUFF];

  if(signal(SIGINT, handler) == SIG_ERR)
    printf("child\n");
  
  //for(i = 0; i < 3; i++) {
  //  if(fork() == 0) {
  //    printf("hello from child %d\n", (int)getpid()); 
  //    sleep(1);
  //    exit(0);
  //  }
  //}
  
  if((n = read(STDIN_FILENO, buf, sizeof(buf))) < 0) {
    printf("read\n");
  }
  printf("parent processing input\n");
  while(1)
    ;
  return 0;
}
