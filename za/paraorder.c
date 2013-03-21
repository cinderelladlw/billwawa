/* 通常都是后面的函数参数先入栈，
   第二个参数被++，这样第一个参数>第二个参数
   于是ret == 1
*/
#include <stdio.h>

int func(int, int);

int main()
{
  int ret;
  int a = 100;
  ret = func(a, a++);
  printf("%d\n", ret); 
  return 0;
}

int func(int x, int y)
{
  if(x>y)
    return 1;
  else if(x == y)
    return 0;
  else 
    return -1;
}
