#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
 
#define NUM_THREADS     5
   struct thread {
     int num;
     char *a;
   } thread_args[NUM_THREADS];
 
void *TaskCode(void *argument)
{
   int tid;
 
   tid = (*((struct thread *) argument)).num;
   char *str = (*((struct thread *) argument)).a;
   printf("Hello World! It's me, thread %d!\n", tid);
   printf("Hello World! It's me, thread %s!\n", str);
 
   /* optionally: insert more useful stuff here */
 
   return NULL;
}
 
int main(void)
{
   pthread_t threads[NUM_THREADS];
   int rc, i;
 
   /* create all threads */
   for (i=0; i<NUM_THREADS; ++i) {
      thread_args[i].num = i;
      thread_args[i].a = "sx";
      printf("In main: creating thread %d\n", i);
      rc = pthread_create(&threads[i], NULL, TaskCode, (void *) &thread_args[i]);
      assert(0 == rc);
   }
 
   /* wait for all threads to complete */
   for (i=0; i<NUM_THREADS; ++i) {
      rc = pthread_join(threads[i], NULL);
      assert(0 == rc);
   }
 
   exit(EXIT_SUCCESS);
}
