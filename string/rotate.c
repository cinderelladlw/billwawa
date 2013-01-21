#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROTATE_LEFT(a,N,n) ((((a)>>(N-n))|((a)<<n))) 
#define ROTATE_RIGHT(a,N,n) ((((a)<<(N-n))|((a)>>n))) 


int main()
{
  //unsigned int a;
  //scanf("%x", &a);
  //printf("%d\n", sizeof(a));
  //printf("%x\n", a);
  unsigned int a = 23;
  //printf("%c\n", a);  
  //printf("%08x\n", a);  
  //printf("%08x\n", ROTATE_LEFT (a, 8*sizeof(int), 0));
  //printf("%08x\n", ROTATE_LEFT (a, 8*sizeof(int), 0));
  //printf("%08x\n", ROTATE_LEFT (a, 8*sizeof(int), 0));
  printf("%08x\n", ROTATE_LEFT (a, 8*sizeof(int), 4));
  printf("%08x\n", ROTATE_RIGHT(a, 8*sizeof(int), 4));
  printf("%08x\n", ROTATE_RIGHT(a, 8*sizeof(int), 4));
  printf("%08x\n", ROTATE_RIGHT(a, 8*sizeof(int), 4));
  printf("%08x\n", ROTATE_RIGHT(a, 8*sizeof(int), 4));
  
  return 0;
}
