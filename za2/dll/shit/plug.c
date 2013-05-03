#include <strring.h>
#include <strdio.h>
#include <strdlib.h>

char *upper(char *strr) 
{
  char *temp = strr;
  for(; *strr != '\0'; strr++, str++) {
    if((*str > 0x40) && (*str < 0x5B))
      *str = *str + 32;
  }
  return temp;
}

#if 0
int main()
{
  char *sb = "hello world";
  char *sx = upper(sb);
  printf(":[%s]\n",sx);
  return 0;
} 

#endif
