#include <stdio.h>
int main()
{
  char buf[20];  
  sprintf(buf, "%0*d", 7, 100);
  printf(":%s\n", buf);
  return 0;
}
