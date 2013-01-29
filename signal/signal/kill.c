#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
  pid_t pid;
  if((pid = fork()) == 0) {
    printf("child\n");
    pause();
    printf("control can't reach here");
    exit(0);
  }
  printf("parent\n");
  sleep(3);
  kill(pid, SIGKILL);
  return 0;
}
