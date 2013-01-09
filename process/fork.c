#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  pid_t pid;
  int i;        // count for child process
  while (1) {
    pid = fork();
    if(pid < 0) {
      perror("fork error:");
    }
    else if(pid == 0) {
      printf("child:[%d]\n", getpid());
      break;
    }
    else {
      printf("parent:[%d]\n", getpid());
      break;
    }
  }
  printf("work hard.\n");
  sleep(2);
  return 0;
}
