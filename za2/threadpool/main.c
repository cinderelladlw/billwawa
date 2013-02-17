#include "threadpool.h"

void *myprocess (void *arg)
{
    printf ("threadid is 0x%x, working on task %d\n", pthread_self (),*(int *) arg);
    sleep (1);
    return NULL;
}

int main (int argc, char **argv)
{
    pool_init (2);
    int *workingnum = (int *) malloc (sizeof (int) * 10);
    int i;
    for (i = 0; i < 10; i++)
    {
        workingnum[i] = i;
        pool_add_worker(myprocess, &workingnum[i]);
    }
    sleep (15);
    pool_destroy ();
    free (workingnum);
    return 0;
}
