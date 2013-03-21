#include <stdio.h>
#include <stdlib.h>

static int sum(int value);

struct inout {
  int value;
  int result;
};

int main(int argc, char **argv)
{
  struct inout *io = (struct inout *)malloc(sizeof(struct inout));
  if (NULL == io) {
    perror("io malloc:");
    return -1;
  }
  if (argc != 2) {
    perror("insert :");
    return -1;
  }
  io -> value = atoi(argv[1]);
  io -> result = sum(io -> value);
  printf("insert:%d, ouput:%d\n", io -> value, io -> result);
  return 0;
}

int sum(int value)
{
  int result = 0;
  int i = 0;
  for (i = 0; i < value; i++) {
    result += i; 
  }
  return result;
}
