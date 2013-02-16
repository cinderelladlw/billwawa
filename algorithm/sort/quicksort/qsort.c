#include <stdio.h>
#include <stdlib.h>
 
static int cmp(const void *a, const void *b)
{
  return *(int *)b - *(int *)a;
}
 
int main()
{
  int arr[10]={5, 3, 7, 4, 1, 9, 8, 6, 2, 23};
  qsort(arr, 10, sizeof(int), cmp);
  int i;
  for (i = 0; i < 10; i++)
    printf("%d\n", arr[i]);
  return 0;
}
