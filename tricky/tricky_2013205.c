#include <stdio.h>

int main()
{
  unsigned char a[(100 + 7)/8];
  memset(a, 0x00, (100 + 7)/8);
  a[0] = 0x01;
  printf("%x\n", (a[0]<<1|0x00));
  printf("%x\n", a[1]);
  return 0;
}
