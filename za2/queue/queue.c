#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct node_s node;
typedef struct queue_s queue;
struct node_s {
        node* next;
        node* prev;
        int state;
};


struct queue_s {
        node* head; /* = 0 */
        node* tail; /* = 0 */
        pthread_mutex_t mtx;
        pthread_cond_t cond;
} *vm_queue;

void queue_init()
{
        vm_queue = (queue *)malloc(sizeof(queue));//error handle
        vm_queue->head = NULL;
        vm_queue->tail = NULL;
        pthread_mutex_init(&vm_queue->mtx, NULL);
        pthread_cond_init(&vm_queue->cond, NULL);
}
void queue_push(int state)
{
        node* this, *tail;

        this = (node *)malloc(sizeof(node)); //error handle
        this->next = NULL;
        this->prev = NULL;
        this->state = state;

        pthread_mutex_lock(&vm_queue->mtx);
        if (! (tail = vm_queue->tail)) {
                tail = this;
                vm_queue->head = this;
        } else {
                this->next = tail;
                tail->prev = this;
        }
        vm_queue->tail = this;
        pthread_mutex_unlock(&vm_queue->mtx);

        pthread_cond_signal(&vm_queue->cond);
}


int queue_pop()
{
        node* head;
        int state;

        pthread_mutex_lock(&vm_queue->mtx);
        while (! (head = vm_queue->head)) {
                pthread_cond_wait(&vm_queue->cond, &vm_queue->mtx);
        }

        if(! (vm_queue->head = head->prev))
                vm_queue->tail = NULL;

        //vm_queue->head = head->prev;
        state = head->state;
        free(head);
        pthread_mutex_unlock(&vm_queue->mtx);

        return state;
}

void * enqueue()
{
        int i;
        while(1)
        {
                i++;
                queue_push(i);
                sleep(1);
        }
}

void *dequeue(void *tid)
{
        int j;

        while(1)
        {
                j = queue_pop();
                if(j%2 == 0)
                {
                        write(1,"even",4);
                }
                sleep(1);
        }
}

int main()
{
        pthread_t tid1, tid2, tid3, tid4;
        int pid;
        int pipefd[2];

        queue_init();
        pipe(pipefd);

        pid = fork();
        switch (pid)
        {
                case -1:
                        exit(0);
                case 0:

                        close(pipefd[1]);
                        dup2(pipefd[0],0);
                        execlp("./mytest","./mytest",NULL);

                default:
                        break;


        }
        close(pipefd[0]);
        dup2(pipefd[1],1);

        pthread_create(&tid1, NULL, dequeue, NULL);
        pthread_create(&tid2, NULL, enqueue, NULL);
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);

}
