#include <stdio.h>

int main()
{
  char ch = 0;
  printf("[%d]\n", ch);
  ch >>= 1;
  printf("[%d]\n", ch);
  return 0;
}
