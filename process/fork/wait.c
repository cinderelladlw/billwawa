#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

void sighandle(int signo);

int main()
{
  int status;
  pid_t pc, pr;
  pc = fork();
  if (pc < 0) {
    printf("error \n");
  }
  else if (pc == 0) {
    printf("chilid [%d]\n", getpid());
    sleep(3);
    exit(3);
  }
  else {
    signal(SIGCHLD, sighandle);
    pr = wait(&status);
    if(WIFEXITED(status)) {
      printf("child exit normally [%d]\n", pr);
      printf("return code [%d]\n", WEXITSTATUS(status));
    }
    else {
      printf("child exit abnormally\n");
    } 
  }
  printf("work\n");
  return 0;
}

void sighandle(int signo)
{
  printf("sighandle..\n");
}
