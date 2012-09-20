#include <stdio.h>
#include <stdlib.h>

char *copy(char *s, char *t);

int main()
{
  char *a = "hello world..";
  char *b = NULL;
  char *c = copy(b, a);
  printf("[%s]\n", c);
  return 0;
}

char *copy(char *s, char *t)
{
  s = (char *)malloc(100);
  char *tmp = s;
  for( ;(*s = *t) != '\0'; s++,t++)
    ;
  return tmp;
} 
