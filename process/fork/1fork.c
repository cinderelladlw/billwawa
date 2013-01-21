#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define NUM 7

int main()
{
  int i;
  pid_t pid;
  for (i = 0; i < NUM; i++) {
    if((pid = fork()) == 0) {
      break; 
    }
  }
  printf("main....\n");
  return 0;
}
