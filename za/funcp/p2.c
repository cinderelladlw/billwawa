#include <stdio.h>

void myfun(int x);
typedef void (*fp)(int);
void (*fpname)(int);

int main()
{
  fp a = &myfun;
  a(10);
  
  fpname = &myfun;
  (*fpname)(23); 
  
  return 0;  
}

void myfun(int x)
{
  printf("%d\n", x);
}
