#include <stdio.h>
#include <pthread.h>

pthread_t a1, a2, a3;
static int b1 = 1;
static int b2 = 2;
static int b3 = 3;

void *func1(void *arg1)
{
  printf("thread 1: %u\n", pthread_self());
  sleep(1);
  pthread_exit(&b1);
}

void *func2(void *arg2)
{
  printf("thread 2: %u\n", pthread_self());
  sleep(5);
  pthread_exit(&b2);
}

void *func3(void *arg3)
{
  printf("thread 3: %u\n", pthread_self());
  sleep(9);
  pthread_exit(&b3);
}

int main()
{
  int err;
  pthread_create(&a2, NULL, func2, NULL);
  usleep(4500000);
  pthread_create(&a2, NULL, func2, NULL);
  int *qt = NULL;
  err = pthread_join(a2, (void *)&qt);
  if(err == 0)
    printf("ok\n");
  printf("a2:%d\n", *qt);
  *qt = 111111;
  err = pthread_join(a2, (void *)&qt);
  if(err == 0)
    printf("ok\n");
  printf("a2:%d\n", *qt);
  sleep(10000);
  return 0;
}





