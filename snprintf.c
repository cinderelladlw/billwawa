#include <stdio.h>

int main()
{
  char *a = "hello world";

  char *b = "!!!";
  char hey[20];
  snprintf(hey, 5, "%s", a);
  printf(":%s\n", hey);
  snprintf(hey, 5, "%s", a,2, "%s", b);
  printf(":%s\n", hey);
  printf(":%s\n", hey+5);
  return 0;
}
