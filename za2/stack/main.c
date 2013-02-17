#include "stack.h"

int main()
{
  stack sx = create();
  int s1 = 1;
  int s2 = 2;
  int s3 = 3;
  push(s1, sx);
  push(s2, sx); 
  push(s3, sx); 
  int i,j;
  for (i = 0; i < 10; i++) {
    push(s2, sx);
  }
  for (j = 0; j < 10; j++) {
    pop(sx);
  }
  pop(sx);
  pop(sx);
  pop(sx);
  return 0;
}
