#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 5
pthread_rwlock_t lock;
int lock_num = 100;

void *read(void *num1);
void *write(void *num2);
int main()
{
  pthread_t tid[N+2];
  int i;
  for(i = 0; i < N; i++) {
    pthread_create(&tid[i], NULL, read, NULL);
  }
  pthread_create(&tid[N], NULL, write, NULL);
  pthread_create(&tid[N+1], NULL, write, NULL);


  
  for(i = 0; i < N; i++) {
    pthread_join(tid[i], NULL);
  }
  pthread_join(tid[N], NULL);
  pthread_join(tid[N+1], NULL);
  
  return 0;
}


void *read(void *num1)
{
  pthread_rwlock_rdlock(&lock);
  usleep(1000000);
  printf("read--------lock_num:%d\n", lock_num);
  pthread_rwlock_unlock(&lock);  
}
void *write(void *num2)
{
  pthread_rwlock_wrlock(&lock);
  lock_num++;
  printf("write-------lock_num:%d\n", lock_num); 
  pthread_rwlock_unlock(&lock);
}
