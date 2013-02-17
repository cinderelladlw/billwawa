#include <stdio.h>

int main()
{
  int num[100];
  memset(num, -1, 390);
  int i;
  for(i = 0; i < 100; i++) {
    printf(":%d\n", num[i]);
  }
  return 0;
}


