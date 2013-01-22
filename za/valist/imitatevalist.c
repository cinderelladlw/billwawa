#include <stdio.h>

long sum(int i, ...)
{
  int *p, j;
  long s = 0;
  p = &i + 1;
  for (j = 0; j < i; j++) {
    s += p[j]; 
  }
  return s;
}

int main()
{
  long summ = sum(3, 1, 2, 3);
  printf("%d\n", summ);
  return 0;
}
