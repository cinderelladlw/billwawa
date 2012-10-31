#include <stdio.h>
#include <sched.h>
#include <pthread.h>

void *producer(void *arg);
void *consumer(void *arg);

int item = 0;
pthread_mutex_t mutex;
int running = 1;

int main()
{
  pthread_t pid[2];
  pthread_mutex_init(&mutex, NULL);
  pthread_create(&pid[0], NULL, (void *)producer, NULL);
  pthread_create(&pid[1], NULL, (void *)consumer, NULL);
  usleep(1000000);
  running = 0;
  pthread_join(pid[0], NULL);
  pthread_join(pid[1], NULL);
  pthread_mutex_destroy(&mutex);

  return 0;
}


void *producer(void *arg)
{
  while(running) {
    pthread_mutex_lock(&mutex);
    item++;
    printf("producer:%d\n", item);
    pthread_mutex_unlock(&mutex);
  }
}

void *consumer(void *arg)
{
  while(running) {
    pthread_mutex_lock(&mutex);
    item--;
    printf("consumer:%d\n", item);
    pthread_mutex_unlock(&mutex);
  }
}

