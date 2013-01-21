#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define NUM 7

int main()
{
  int i;
  int childFlag;
  childFlag = 0;
  pid_t pid;
  for (i = 0; i < NUM && childFlag == 0; i++) {
    pid = fork();
    if(pid == 0) {
      childFlag = 1;
    }     
  }
  printf("main...\n");
  return 0;
}
