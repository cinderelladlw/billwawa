#include <stdio.h>

char *upper(char *tmp)
{
  char *source = tmp;
  for(; *tmp != '\0'; tmp++) {
    if(*tmp >= 0x41 && *tmp <= 0x5A) {
      printf(".%c\n", *tmp);
      *tmp = (*tmp) + 32; 
      printf(".%c\n", *tmp);
    } 
  }
  return source;
}

int main()
{
  char *str = "HEllo"; 
  char *sx = upper(str);
  printf("sx:%s\n", sx); 
  return 0;
}
