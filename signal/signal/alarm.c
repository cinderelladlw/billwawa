#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int sig);
 
int main()
{
  signal(SIGALRM, handler);
  alarm(1);
  while(1)
    ;
  return 0;
}

void handler(int sig)
{
  static int num = 0;
  if(++num > 10) {
    printf("BOOM\n");
    exit(0);
  }
  else {
    printf("BEE\n");
    alarm(1);
  }
}
