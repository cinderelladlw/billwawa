#include <stdio.h>

typedef void(*fp)(int);
void getcall(fp, int);
void f1(int a);
void f2(int a);
int main()
{
  getcall(f1, 10);
  getcall(f2, 20);
  return 0;
}

void getcall(fp sb, int x)
{
  sb(x);
}
 
void f1(int a)
{
  printf("...............1\n");
} 
void f2(int a)
{
  printf("...............2\n");
} 
