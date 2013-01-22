#include <stdio.h>
#include <stdarg.h>

void simpleva(int start, ...)
{
  va_list arg_ptr;
  int nArgValue = start;
  int nArgCount = 0;
  va_start(arg_ptr, start);
  do {
    ++nArgCount;
    printf("the %dth arg:%d\n", nArgCount, nArgValue);
    nArgValue = va_arg(arg_ptr, int);
  } while (nArgValue != -1);
}

int main()
{
  simpleva(100, -1);
  simpleva(100, 200, -1); 
  return 0;
}
