#include <stdio.h>

int main()
{
  int a[10];
  memset(a, -1, 8*4);
  int i;
  for(i = 0; i < 10; i++) {
    printf(":%d\n", a[i]);
  }
  return 0;
}
