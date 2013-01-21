#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define NUM 7

int main()
{
  pid_t pid[NUM];
  int i;
  for (i = 0; i < NUM; i++) {
    pid[i] = fork(); 
    if (pid[i] == 0) {
      printf("child:%d\n", i); 
      break;
    } 
  }
  printf("main..\n");
  return 0;
}


