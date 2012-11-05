#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

unsigned long  i;
void * thr_fn(void * arg)
{
        for(i=0;;i++)
        {
                if((i%1000)==0)
                        printf("i=%ld\n",i);
                pthread_testcancel();
        }
        printf("test cancel fail.\n");
        return ((void *)1);
}
int main(int argc,char ** argv)
{
        pthread_t tid;
        int err;
        void * tret;
        //设置线程数目
        pthread_setconcurrency(2);
        err=pthread_create(&tid,NULL,thr_fn,NULL);
        if(err!=0)
                printf("create thread error :%s\n",strerror(err));
        usleep(20000);
      //  pthread_cancel(tid);
        err=pthread_join(tid,&tret);
        if(err!=0)
                printf("can't join thread : %s\n",strerror(err));
        printf("thread exit code %d\n",(int)tret);
        sleep(10);
        return 0;
}
