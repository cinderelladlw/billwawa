#include <setjmp.h>
#include <stdio.h>

jmp_buf buf;
void banana() {
  printf("in banana()\n");
  longjmp(buf, 1);
  printf("u will never see this, because i longjmp\n");
}

int main()
{
  if(setjmp(buf)) {
    printf("back in main\n");
  }
  else {
    printf("first time through\n");
    banana();
  }
  return 0;
} 
