#include <stdio.h>

int main()
{
  char *p = NULL;
  p = "hello";
  printf("%s\n", p);
  char *a[2];
  a[0] = "hello";
  a[1] = "world";
  printf("%s\n", a[0]);
  printf("%s\n", a[1]);
 // char a[10];
 // a = "hello";
 // printf("%s\n", a);
  return 0;
}
