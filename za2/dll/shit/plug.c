#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *upper(char *str) 
{
  char *temp = str;
  char *st = (char *)malloc(strlen(str)+1);
  for(*st = *str; *str != '\0'; str++, st++)
    ;
  return temp;
}

#if 0
int main()
{
  char *sb = "hello world";
  char *sx = upper(sb);
  printf(":[%s]\n",sx);
  return 0;
} 

#endif
