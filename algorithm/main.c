#include <stdio.h>

int isprime(int num);

int main()
{
  int i = 10;
  for (i = 10; i < 100000000; i ++) {
    if(isprime(i)) {
      printf(":%d\n", i); 
    }
  //  printf(":%d\n", i); 
  }

  return 0;
}

int isprime(int num)
{
  int tmp = 0;
  int old = num;
  while(num > 0) {
    tmp = tmp * 10 + num%10;
    num = num / 10;
  }
  return old == tmp;
}
