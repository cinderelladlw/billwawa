#include <stdio.h>

int main()
{
  int j = 0;
  char buff[1000];
  fprintf(stdout, "%s:%d", "hello world", ++j); 
  return 0;
}
