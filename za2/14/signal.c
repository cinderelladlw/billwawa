#include <stdio.h>
#include <signal.h>

void sig(int arg)
{
  printf("signal..sx \n");
  signal(SIGINT, sig); 
}

int main()
{
  signal(SIGINT, sig);
  sleep(10000);
  return 0;
}  
