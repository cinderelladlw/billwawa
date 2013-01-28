#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <assert.h>

typedef struct worker
{
    void *(*process) (void *arg);
    void *arg;
    struct worker *next;
} CThread_worker;


/*线程池结构*/
typedef struct
{
    pthread_mutex_t queue_lock;
    pthread_cond_t queue_ready;
    CThread_worker *queue_head;
    int shutdown;              /*是否销毁线程池*/
    pthread_t *threadid;       /*线程池中允许的活动线程数目*/
    int max_thread_num;        /*当前等待队列的任务数目*/
    int cur_queue_size;
} CThread_pool;


int pool_add_worker (void *(*process) (void *arg), void *arg);
void *thread_routine (void *arg);

static CThread_pool *pool = NULL;

void pool_init (int max_thread_num)
{
    pool = (CThread_pool *) malloc (sizeof (CThread_pool));
    pthread_mutex_init (&(pool->queue_lock), NULL);
    pthread_cond_init (&(pool->queue_ready), NULL);
    pool->queue_head = NULL;
    pool->max_thread_num = max_thread_num;
    pool->cur_queue_size = 0;
    pool->shutdown = 0;
    pool->threadid = (pthread_t *) malloc (max_thread_num * sizeof (pthread_t));
    int i = 0;
    for (i = 0; i < max_thread_num; i++)
    {
        pthread_create (&(pool->threadid[i]), NULL, thread_routine, NULL);
    }
}

int pool_add_worker (void *(*process) (void *arg), void *arg)
{
    CThread_worker *newworker = (CThread_worker *) malloc (sizeof (CThread_worker));
    newworker->process = process;
    newworker->arg = arg;
    newworker->next = NULL;
    pthread_mutex_lock (&(pool->queue_lock));
     /*将任务加入到等待队列中*/
    CThread_worker *member = pool->queue_head;
    if (member != NULL)
    {
        while (member->next != NULL)
            member = member->next;
        member->next = newworker;
    }
    else
    {
        pool->queue_head = newworker;
    }

    assert (pool->queue_head != NULL);

    pool->cur_queue_size++;
    pthread_mutex_unlock (&(pool->queue_lock));
    pthread_cond_signal (&(pool->queue_ready));
    return 0;
}

int pool_destroy ()
{
    if (pool->shutdown)
        return -1;
    pool->shutdown = 1;

    pthread_cond_broadcast (&(pool->queue_ready));

    /*阻塞等待线程退出，否则就成僵尸了*/
    int i;
    for (i = 0; i < pool->max_thread_num; i++)
        pthread_join (pool->threadid[i], NULL);
    free (pool->threadid);

    /*销毁等待队列*/
    CThread_worker *head = NULL;
    while (pool->queue_head != NULL)
    {
        head = pool->queue_head;
        pool->queue_head = pool->queue_head->next;
        free (head);
    }
    /*条件变量和互斥量也别忘了销毁*/
    pthread_mutex_destroy(&(pool->queue_lock));
    pthread_cond_destroy(&(pool->queue_ready));
    free (pool);
    /*销毁后指针置空是个好习惯*/
    pool=NULL;
    return 0;
}


void *thread_routine (void *arg)
{
    printf ("starting thread 0x%x\n", pthread_self ());
    while (1)
    {
        pthread_mutex_lock (&(pool->queue_lock));
        while (pool->cur_queue_size == 0 && !pool->shutdown)
        {
            printf ("thread 0x%x is waiting\n", pthread_self ());
            pthread_cond_wait (&(pool->queue_ready), &(pool->queue_lock));
        }

        /*线程池要销毁了*/
        if (pool->shutdown)
        {
            pthread_mutex_unlock (&(pool->queue_lock));
            printf ("thread 0x%x will exit\n", pthread_self ());
            pthread_exit (NULL);
        }

        printf ("thread 0x%x is starting to work\n", pthread_self ());

        assert (pool->cur_queue_size != 0);
        assert (pool->queue_head != NULL);
       
        /*等待队列长度减去1，并取出链表中的头元素*/
        pool->cur_queue_size--;
        CThread_worker *worker = pool->queue_head;
        pool->queue_head = worker->next;
        pthread_mutex_unlock (&(pool->queue_lock));

        /*调用回调函数，执行任务*/
        (*(worker->process)) (worker->arg);
        free (worker);
        worker = NULL;
    }
    pthread_exit (NULL);
}
