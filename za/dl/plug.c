#include <stdio.h>

void add()
{
  char *argv[] = {"ls", "-al", NULL};
  if(fork() > 0) {
    printf("parent..\n");
    sleep(10);
    printf("parent..end...\n");
    
  } else {
    printf("child..\n");
    execvp("ls", argv);  
    sleep(7);
    printf("child..end...\n");
//    exit(1);
  }
  printf("add ok!\n");
  printf("2.add ok!\n");
}

//int main()
//{
//  add();
//  return 0;
//}

//execvp();


