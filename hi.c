#include <stdio.h>
#include <stdlib.h>

char *copy(char *s, char *t);

int main()
{
  char *a = "hello world..";
  char *b = NULL;
  char *c = copy(b, a);
  printf("........................\n");
  //printf("%s\n", c);
  return 0;
}

char *copy(char *s, char *t)
{
  printf("....\n");
  s = (char *)malloc(100);
  char *tmp = s;
  printf("....\n");
  for( ;(*s = *t) != '\0'; s++,t++)
    printf("23....\n");
    ;
  printf("%s", tmp); 
  return tmp;
} 
