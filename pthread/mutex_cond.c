#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void *producer(void *arg1);
void *consumer(void *arg2);
  
pthread_mutex_t mutex;
pthread_cond_t cond;
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int glob = 100;

int main()
{
  pthread_t tid[2];
  pthread_create(&tid[0], NULL, producer, NULL);
  pthread_create(&tid[1], NULL, consumer, NULL);
  
  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);
  return 0;
}

void *producer(void *arg1)
{
  pthread_mutex_lock(&mutex);
 // pthread_cond_wait(&cond, &mutex);
  glob ++; 
  printf("producer:%d\n", glob);
  pthread_mutex_unlock(&mutex);
  int i;
  for(i = 0; i < 3; i++) {
    printf(".........\n");
  }
  usleep(100000);
  pthread_cond_signal(&cond);
} 
void *consumer(void *arg2)
{
  pthread_mutex_lock(&mutex);
  pthread_cond_wait(&cond, &mutex);
  usleep(1000000);
  glob -= 10; 
  printf("producer:%d\n", glob);
  pthread_mutex_unlock(&mutex);
  pthread_cond_signal(&cond);

}
