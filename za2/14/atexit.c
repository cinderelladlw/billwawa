#include <stdio.h>
#include <stdlib.h>

void exit_fn1(void)
{
  printf("1 called\n");
}
void exit_fn2(void)
{
  printf("2 called\n");
}

int main()
{
  atexit(exit_fn1);
  atexit(exit_fn2);
  exit(0);
}

