#include <stdio.h>

//unsigned char a[2*1024*1024*1024];
//unsigned int  b[10];
static int  b[10];
int count(int a[], int n)
{
  int i, j;
  i = 0;
  while (i < n) {
    for (j = 0; j < 10; j++) {
      if (a[i]%10 == j) {
        b[j]++;
        break;
      }
    }
    i++;
  }        
}

int main()
{
  int sx[] = {1,2,3,4,3,2,2,23,23,23,23,23,234,65,89};
  count(sx, 15);
  int sb;
  for (sb = 0; sb < 10; sb++) {
    printf("%d:", b[sb]);
  }
  printf("\n");
  return 0;
}
