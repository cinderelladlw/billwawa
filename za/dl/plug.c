#include <stdio.h>

int sx = 250;
void _add(int a, int b);
void add()
{
  int i = 5;
  int j = 6;
  _add(i, j); 
  printf("2.add ok!\n");
}

void _add(int a, int b)
{
  printf("add:%d\n", a+b);
  printf("sx :%d\n", sx);
}


