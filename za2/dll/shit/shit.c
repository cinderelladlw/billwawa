#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  //char *q = (char *)malloc(10);
  //memcpy(q, "ABc", 4);
  char q[] = "ABSsdjl";
  char *p = q;
  for(; *p != '\0'; p++) {
    if(*p >= 'A' && *p <= 'Z') {
      *p += 'a' - 'A'; 
      printf("%c\n", *p);
    }
  }
  return 0;
}
