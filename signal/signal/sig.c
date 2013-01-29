#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void new_op(int signum, siginfo_t *info, void *myact);

int main(int argc, char **argv)
{
  struct sigaction act;
  int sig = atoi(argv[1]);
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_SIGINFO;
  act.sa_sigaction = new_op;
  
  if(sigaction(sig, &act, NULL) < 0) {
    printf("install error\n");
  }
  while(1) {
    sleep(2);
    printf("wait for signal\n");
  }
  return 0;
}

void new_op(int signum, siginfo_t *info, void *myact)
{
  printf("recvive signal [%d]\n", signum);
  sleep(5);
} 
