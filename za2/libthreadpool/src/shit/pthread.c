#include <stdio.h>
#include <pthread.h>
#include <signal.h>

#define N 2

static int sx = 0;

void *func(void *args)
{
  sx = pthread_self();
  printf(":%d\n", sx);
  printf("thread..%d\n", pthread_self());
  sleep(10);
  printf("..\n");
  sleep(100);
}

void *funckill(void *args)
{
  printf("thread..%d\n", pthread_self());
  sleep(8);
  printf(":%d\n", sx);
  kill(sx, SIGTERM);
  
  printf("kill over..\n");
  sleep(100);
}


int main()
{
  pthread_t tid[N];
  int i;
    pthread_create(&tid[0], NULL, funckill, NULL);
    pthread_create(&tid[1], NULL, func, NULL);
  while(1);
  for(i = 0; i < N; i++) {
    pthread_join(tid[i], NULL);
  }
  sleep(100000);
  return 0;
}
