#include <stdio.h>

int main()
{
  while(1) {
    printf(".1......\n");
    while(1) {
      printf(".2......\n");
      sleep(1);
      int j = -2;
      if(j > 0) {
        printf("j = 2\n");
      }
      else {
        printf("break.......\n");
        break;
      }
      printf(".2......end\n");
    }
    sleep(1);
    printf(".1.....end.\n");
  }
  printf("main end\n");
  return 0;
}
