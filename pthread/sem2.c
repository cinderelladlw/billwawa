#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void *producter(void *arg);
void *consumer(void *arg);

sem_t sem;
int running = 1;
int main()
{
  pthread_t producter_t;
  pthread_t consumer_t;
  sem_init(&sem, 0, 16);
  pthread_create(&producter_t, NULL, producter, NULL);
  pthread_create(&consumer_t, NULL, consumer, NULL);
  sleep(13);
  running = 0;
  pthread_join(consumer_t, NULL);  
  pthread_join(producter_t, NULL);  
  sem_destroy(&sem);
  return 0;
}

void *producter(void *arg)
{
  int semval = 0;
  while(running) {
    usleep(100000);
    sem_post(&sem);
    sem_getvalue(&sem, &semval);
    printf("生产总数量:%d\n", semval);
  }
}
void *consumer(void *arg)
{
  int semval = 0;
  while(running) {
    usleep(30000);
    sem_wait(&sem);
    sem_getvalue(&sem, &semval);
    printf("::::::消费总数量:%d\n", semval);
  }
}
