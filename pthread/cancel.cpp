#include<iostream>
#include<unistd.h>
#include<pthread.h>
using namespace std;

#define MAX 23333333

pthread_t pid[3];

void* thread_run_1(void* arg){
    cout<<"Now in the thread 1\n";
    int sum = 0;
    int state, oldstate;
    state = PTHREAD_CANCEL_DEFERRED;
    pthread_setcancelstate(state, &oldstate);

    cout<<"oldstate is "<<(state == oldstate? "Deferred":"Async")<<endl;
    cout<<"before testcancel"<<endl;
    while(1) {
    pthread_testcancel();
    pthread_testcancel();
    }
    cout<<"after testcancel"<<endl;
    cout<<"thread 1 done!"<<endl;
}

void* thread_run_2(void* arg){
    cout<<"Now in the thread 2\n";
//    pthread_join(pid[1],NULL);
    sleep(1);
    for(;;) {
    pthread_cancel(pid[1]);
    }
    cout<<"thread 2 done!"<<endl;
}

int main()
{
    pid[0] = pthread_self();
    if (pthread_create(&pid[1],NULL,thread_run_1,NULL) != 0){
        cout<<"error create thread 1"<<endl;
        return -1;
    }
    if (pthread_create(&pid[2],NULL,thread_run_2,NULL) != 0){
        cout<<"error create thread 2"<<endl;
        return -1;
    }

    sleep(10);
    cout<<"Main thread done!"<<endl;
}
