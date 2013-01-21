#include <stdio.h>

int main()
{
  int a = 5;
  printf("%08x\n", a);
  printf("%08x\n", a<<4); 
  printf("%08x\n", a<<8); 
  printf("%08x\n", (a<<8)|(a<<4)); 
  return 0;

}
