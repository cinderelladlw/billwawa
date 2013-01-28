#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct demo {
  int x,y;
  int (*func)(int, int);
};

int add2(int x, int y)
{
  return x+y;
}

int main()
{
  struct demo *dem = (struct demo *)malloc(sizeof(struct demo));
  dem->func = &add2;
  printf(":%d\n", (*(dem->func))(3,7));
  printf(":%d\n", dem->func(3,7));
  return 0;
}
  
