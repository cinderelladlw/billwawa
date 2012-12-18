#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE *fp1 = fopen("a.txt", "w+");
  FILE *fp2 = fopen("a.txt", "w+");
  char buf[10];
  printf("insert:\n");
  scanf("%s", buf);
  fputs(buf, fp2);
  fgets(buf, 10, fp1);
  printf("buf:%s\n", buf);
  return 0;
}

