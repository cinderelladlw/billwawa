#include <stdio.h>
#include <pthread.h>

void *func(void *arg)
{
  printf("a\n");
}

int main()
{
  pthread_t b;
  pthread_create(&b, NULL, func, NULL);
  printf("sx\n");
  sleep(100);
  return 0;
}
