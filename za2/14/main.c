#include <stdio.h>

int main(int argc, char **argv)
{
  if(argc < 2) {
    fprintf(stdout, "sb:%s\n", "hello <ip> <port>");
    return -1;
  }
  printf("argv[0]:%s\n", argv[0]); 
  printf("argv[1]:%s\n", argv[1]); 
  return 0;
}
