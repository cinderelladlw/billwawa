#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <sys/types.h>

#define DBGPRINTF_DEBUG printf
#define DBGPRINTF_ERROR printf
#define ASSERT  assert
#include "thread-control.h"

struct _thread_control_cond_t
{
    pthread_mutex_t lock;
    pthread_cond_t condition;
};
typedef struct _thread_control_cond_t thread_control_cond_t;

int thread_control_init(THREAD_CONTROL* thread_control)
{
    *thread_control = NULL;
    thread_control_cond_t* cond = (thread_control_cond_t*)malloc(sizeof(thread_control_cond_t)); 
    assert(cond != NULL);
    pthread_mutex_init(&(cond->lock), NULL);
    pthread_cond_init(&(cond->condition), NULL);
    *thread_control = cond;
    return 0;
}


int thread_control_deinit(THREAD_CONTROL* thread_control)
{
    thread_control_cond_t* cond = (thread_control_cond_t*)(*thread_control); 
    pthread_mutex_destroy(&(cond->lock));
    pthread_cond_destroy(&(cond->condition));
    free(cond);
    *thread_control = NULL;
    return 0;
}

int thread_control_wait(THREAD_CONTROL thread_control)
{
    thread_control_cond_t* cond = (thread_control_cond_t*)(thread_control); 
    //Wait pthread condition.
    pthread_mutex_lock(&(cond->lock));
    pthread_cond_wait(&(cond->condition), &(cond->lock));
    pthread_mutex_unlock(&(cond->lock));
    return 0;
}


int thread_control_start(THREAD_CONTROL thread_control)
{
    thread_control_cond_t* cond = (thread_control_cond_t*)(thread_control); 
    //start pthread condition.
    pthread_mutex_lock(&(cond->lock));
    pthread_cond_signal(&(cond->condition));
    pthread_mutex_unlock(&(cond->lock));
    return 0;
}
