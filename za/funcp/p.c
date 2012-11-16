#include <stdio.h>

void myfun(int x);

int main()
{
  myfun(10);
  return 0;
}

void myfun(int x)
{
  printf("%d\n", x);
}
