#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
pthread_t ntid;
pthread_t ntid2;
static int sb = 2323;
static int sb2 = 23231111;
void printids(const char *s)
{
  pid_t pid;
  pthread_t tid;
  pid = getpid();
  tid = pthread_self();
  printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid, (unsigned int)tid, (unsigned int)tid);
} 
void *thr_fn(void *arg)
{
  printids("new thread: ");
  sleep(5);
  pthread_exit((void *)&sb);
}
void *thr_fn2(void *arg)
{
  printids("new thread2: ");
  sleep(3);
  pthread_exit((void *)&sb2);
}
int main(void)
{
  int err;
  err = pthread_create(&ntid, NULL, thr_fn, NULL);
  err = pthread_create(&ntid, NULL, thr_fn, NULL);
  err = pthread_create(&ntid, NULL, thr_fn, NULL);
  err = pthread_create(&ntid, NULL, thr_fn, NULL);
  err = pthread_create(&ntid, NULL, thr_fn, NULL);
  err = pthread_create(&ntid2, NULL, thr_fn2, NULL);
  err = pthread_create(&ntid2, NULL, thr_fn2, NULL);
  err = pthread_create(&ntid2, NULL, thr_fn2, NULL);
  err = pthread_create(&ntid2, NULL, thr_fn2, NULL);
  if (err != 0)
    printf("can't create thread: %s\n", strerror(err));
  int *sz;
//  pthread_join(ntid,(void *)&sz);
//  pthread_join(ntid,(void *)&sz);
  pthread_join(ntid,(void *)&sz);
  printf(":%d\n", *sz); 
 
  
  pthread_join(ntid,(void *)&sz);
  printf(":%d\n", *sz); 
  
  pthread_join(ntid2,(void *)&sz);
  printf(":%d\n", *sz); 
  
  pthread_join(ntid,(void *)&sz);
  printf(":%d\n", *sz); 
  printids("main thread:");
  sleep(7);
  exit(0);
}
