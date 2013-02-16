#include <stdio.h>

int quicksort(int a[], int l, int h)
{
  int i = l;
  int j = h;
  int key = a[i];
  while (i < j) {
    while (i < j && a[j] > key)
      j--;
    if (i < j)
      a[i++] = a[j];
    while (i < j && a[i] < key)
      i++;
    if (i < j)
      a[j--] = a[i];  
  }
  a[i] = key;
  if (l < i-1)
    quicksort(a, l, i - 1);
  if (i + 1 < h)
    quicksort(a, i + 1, h);
}

int main()
{
  int sx[] = {2,3,2,2,3,23,24,212,90};
  int n = sizeof(sx)/sizeof(int);
  quicksort(sx, 0, n - 1);
  
  int i;
  for (i = 0; i < n; i++)
    printf("%d:", sx[i]);  
  printf("\n");
  return 0;
}
