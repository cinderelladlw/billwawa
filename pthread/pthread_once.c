#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_once_t once = PTHREAD_ONCE_INIT;

void once_run(void)
{
  printf("once run:%ld\n",(unsigned int) pthread_self());
}

void *thread1(void *arg1)
{
  pthread_t tid1 = pthread_self();
  printf("thread 1 start\n");
  pthread_once(&once, once_run);  
  printf("thread 1 end\n");
}


void *thread2(void *arg2)
{
  pthread_t tid2 = pthread_self();
  printf("thread 2 start:%d\n", tid2);
  pthread_once(&once, once_run);  
  printf("thread 2 end\n");
}

int main()
{
  pthread_t t[2];
  pthread_create(&t[0], NULL, thread1, NULL);
  pthread_create(&t[1], NULL, thread2, NULL);

  pthread_join(t[0], NULL);
  pthread_join(t[1], NULL);
  sleep(10);
  return 0;
}
  
