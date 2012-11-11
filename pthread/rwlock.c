#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define THREADCOUNT 20

pthread_rwlock_t rwlock;

void *reader(void *pvoid)
{
  pthread_rwlock_rdlock(&rwlock);
  printf("reader %d worked.\n", (int)pvoid);
  if(pthread_rwlock_unlock(&rwlock)) {
    printf("reader %d unlock error!\n", (int)pvoid);
  }
  return NULL;
}

void *writer(void *pvoid)
{
  pthread_rwlock_wrlock(&rwlock);
  printf("writer %d worked.\n", (int)pvoid);
  if(pthread_rwlock_unlock(&rwlock)) {
    printf("writer %d unlock error!\n", (int)pvoid);
  }
  return NULL;
}

int main(void)
{
  pthread_t reader_id, writer_id;
  pthread_attr_t threadattr;
  int i, rand;
  int readercount = 1, writercount = 100;
  int halfmax = RAND_MAX/2;
  if(pthread_rwlock_init(&rwlock, NULL)) {
    printf("init pthread error.\n");
  }
  pthread_attr_init(&threadattr);
  pthread_attr_setdetachstate(&threadattr, PTHREAD_CREATE_DETACHED);
  
  pthread_rwlock_wrlock(&rwlock);
  for(i = 0; i < THREADCOUNT; i++) {
    rand = random();
    if(rand < halfmax) {
      pthread_create(&reader_id, &threadattr, reader, (void *)readercount);
      printf("created reader %d \n", readercount++);
    }
    else {
      pthread_create(&writer_id, &threadattr, writer, (void *)writercount);
      printf("created writer %d \n", writercount++);
    }
  }
  pthread_rwlock_unlock(&rwlock);
  pthread_exit(NULL);
  return 0;
} 
