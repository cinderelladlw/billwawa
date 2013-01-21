#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROTATE_LEFT(a,N,n) (((a)>>(N-n))|((a)<<n)) 
#define ROTATE_RIGHT(a,N,n) (((a)<<(N-n))|((a)>>n)) 

void ensecret(char *p)
{
  int i;
  for (i = 0; i < strlen(p); i++) {
    ROTATE_LEFT(*(p+i), 8, 2);  
  } 
}

void desecret(char *p)
{
  int i;
  for (i = 0; i < strlen(p); i++) {
    ROTATE_LEFT(*(p+i), 8, 2);  
  } 
}

int main()
{
  char *string = "hello world";
  ensecret(string);
  printf("string:%s\n", string);
  desecret(string);
  printf("string:%s\n", string);
  return 0;
}
