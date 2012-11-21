#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#define KEY 1234 
#define SIZE 1024 
#define PORT 9999 
#define MAXFDS 5000
#define EVENTSIZE 100
void process(); 
int fd, cfd,opt=1;
int shmid;
char *shmaddr;
struct shmid_ds buf;
int num = 0 ; 
int main(int argc, char *argv[])
{
    shmid = shmget(KEY,SIZE,IPC_CREAT|0600); /* 建立共享内存 */
    if(shmid == -1){
        printf("create share memory failed/n"); 
    }
    shmaddr = (char *)shmat(shmid,NULL,0);
    if(shmaddr == (void *)-1){
        printf("connect to the share memory failed: %s",strerror(errno));
        return 0;
    }
    strcpy(shmaddr,"1/n");
    
    struct sockaddr_in sin, cin;
    socklen_t sin_len = sizeof(struct sockaddr_in);
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) <= 0)
    {
        fprintf(stderr, "socket failed/n");
        return -1;
    }
    memset(&sin, 0, sizeof(struct sockaddr_in));
    sin.sin_family = AF_INET;
    sin.sin_port = htons((short)(PORT));
    sin.sin_addr.s_addr = INADDR_ANY;
    if (bind(fd, (struct sockaddr *)&sin, sizeof(sin)) != 0)
    {
         fprintf(stderr, "bind failed/n");
         return -1;
    }
    if (listen(fd, 32) != 0)
    {
        fprintf(stderr, "listen failed/n");
        return -1;
    }
    int i ;  
    for(i = 0; i < 2; i++)
    {
      int pid = fork();
      if(pid == 0)
      {
          process();      
      }
    }  
    while(1) ; 
   
    return 0;
}
void process()
{
    struct epoll_event ev;
    struct epoll_event events[1000];
    int    kdpfd = epoll_create(1000);
    int  len = sizeof(struct sockaddr_in);
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = fd;
    int new_fd; 
    if((fcntl(fd, F_GETFL, 0)&O_NONBLOCK))
        printf("ok non block/n"); 
    else printf("wrong non block/n"); 
    printf("sub socket is %d /n", fd); 
    
    if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, fd, &ev) < 0) 
    {
        fprintf(stderr, "epoll set insertion error: fd=%d/n", fd);
        return ;  
    }
    else
    {
        printf("监听 socket 加入 epoll 成功！/n");
    }
    struct sockaddr_in my_addr, their_addr;
    while (1) 
    {
        /* 等待有事件发生 */
        int nfds = epoll_wait(kdpfd, events, 20, 500);
        if (nfds == -1)
        {
            perror("epoll_wait");
            break;
        }
        /* 处理所有事件 */
        //printf("num of event is :%d /n",nfds);
        int n;  
        for (n = 0; n < nfds; ++n)
        {
            if (events[n].data.fd == fd) 
            {
                new_fd = accept(fd, (struct sockaddr *) &their_addr,&len);
                if (new_fd < 0) 
                {
                    printf("accept error/n");
                    continue;
                } 
                else
                {
                    printf("%d create new socket: %d/n", getpid(), new_fd); 
                }
            } 
        }
 
    }
}

