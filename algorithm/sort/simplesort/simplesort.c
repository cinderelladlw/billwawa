#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define swap(x,y,z)  {z=(*y);(*y)=(*x);(*x)=z;}

// —°‘Ò≈≈–Ú
int selectsort(int a[], int n)
{
  int i, j;
  int tmp;
  for (i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {
      if (a[i] > a[j]) {
        swap(&a[i], &a[j], tmp);
      }
    }
  } 
  return 0;
}

// √∞≈›≈≈–Ú
int bubblesort(int a[], int n)
{
  int i, j;
  int tmp;
  for (i = 0; i < n; i++) {
    for (j = n - 1; j > i; j--) {
      if (a[i] > a[j]) {
        swap(&a[i], &a[j], tmp);
      }
    }
  }
  return 0;
}

// ≤Â»Î≈≈–Ú
int insertsort(int a[], int n)
{
  int i, j;
  int tmptmp;
  for (i = 1; i < n; i++) {
    tmptmp = a[i];
    j = i - 1;
    while ((a[j] > tmptmp)&&(j >= 0)) {
      a[j + 1] = a[j];
      j--;
    }
    a[j+1] = tmptmp;
  }
  return 0;
}

void print(int b[])
{
  int i;
  for (i = 0; i < 7; i++) {
    printf("%d:", b[i]);
  }
  printf("\n");
}     
int main()
{
  int unsorted[] = {2, 4, 6, 8, 1, 2, 17};
  //selectsort(unsorted, 7);
  //bubblesort(unsorted, 7);
  //print(unsorted);
  insertsort(unsorted, 7);
  print(unsorted);
  return 0;
}
