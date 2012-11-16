#include <stdio.h>
#include <stdlib.h>

void myfun1(int x);
void myfun2(int x);
void myfun3(int x);

typedef void (*fun)(int);
void callfun(fun fp, int x);

int main()
{
  callfun(myfun1, 10);
  callfun(myfun2, 20);
  callfun(myfun3, 30);
}

void callfun(fun fp, int x)
{ 
  sleep(1);
  fp(x);
}

void myfun1(int x)
{
  printf("1........\n");
}
void myfun2(int x)
{
  printf("2........\n");
}
void myfun3(int x)
{
  printf("3........\n");
}


