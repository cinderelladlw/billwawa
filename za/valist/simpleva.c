#include <stdio.h>
#include <stdarg.h>

void simpleva(int i, ...)
{
  va_list arg_ptr;
  int j = 0;
  va_start(arg_ptr, i);
  j = va_arg(arg_ptr, int);
  printf("%d %d\n", i, j);
  j = va_arg(arg_ptr, int);
  printf("%d %d\n", i, j);
  j = va_arg(arg_ptr, int);
  printf("%d %d\n", i, j);
  va_end(arg_ptr);
}

int main()
{
  simpleva(100, 200, 300, 500);
  return 0;
}
