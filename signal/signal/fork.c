#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main()
{
  pid_t pid;
  int i;
 
  for(i = 0; i < 3; i++) {
    pid = fork();
    if(pid == 0) {
      printf("child %d\n", getpid());
      sleep(1);
      exit(0);
    } 
   // else {
   //   printf("parent %d\n", getpid());
   //   sleep(1);
   // }
  }
  
  printf("main.............\n");
  
  return 0;
}

