#include <stdio.h>

int func(int , int );

int main()
{
  int a = 10;
  int i = func(a,a++);
  printf("%d\n", i);
  return 0;
}


int func(int x, int y)
{
  if(x < y) {
    printf(":%d\n", y);
    return 1;
  }
  else if(x == y) {
    printf(":%d\n", y);
    return 0;
  }
  else {
    printf(":%d\n", y);
    return -1;
  }
}
