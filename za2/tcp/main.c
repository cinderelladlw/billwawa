#include <stdio.h>
#include <stdlib.h>

int main()
{
  int j = 1231213;
  int i = 19;
  char *buf = (char *)malloc(20);
  sprintf(buf, "%0*d", i, j);
  printf(":%s\n", buf);
  return 0;
}
