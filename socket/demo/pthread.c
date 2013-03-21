#include <stdio.h>
#include <pthread.h>

int sx = 23; 
void *func(void *arg)
{
  printf("sxxxxxxxxxxxxxx id:%d\n", pthread_self());
  sleep(3);
  printf("thread exit\n");
  pthread_exit(&sx);
}
int main()
{
  pthread_t tid;
  pthread_t tid2;
  
  pthread_create(&tid, NULL, func, NULL);
  sleep(1);
  int *sb;
  pthread_join(tid, &sb);
  printf(":%d\n",*sb);
  sleep(1);
  printf(".......\n");
  sleep(10000);
  return 0;
}
