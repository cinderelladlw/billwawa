#include <stdio.h>
#include <signal.h>

void ding(int sig)
{
  printf("sigterm..\n");
}

int main()
{
  signal(SIGTERM, ding);
  pause();
  return 0;
}



