#include <stdio.h>

int main()
{
  int c;
  while((c = getc(stdin)) != EOF)
    if(putc(c, stdout) == EOF)
      printf("getcc....\n");
  if(ferror(stdin))
    printf("std...\n");
  return 0;
}
