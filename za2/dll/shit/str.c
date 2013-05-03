#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inv(char *s)
{
 int i;
 for(i=1;i<=strlen(s);i++)
 {
  if(*(s+i)>=65 && *(s+i)<=92)
    *(s+i)+=32;
  else if (*(s+i)>=97 && *(s+i)<=122)
    *(s+i)-=32;
 }
}

int main()
{
  char *str = "helLLOOOa";
  inv(str);
  printf(":%s\n", str);
  return 0;
}
