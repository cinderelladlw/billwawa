#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
using namespace std;

#define MAXLINE 5
#define OPEN_MAX 100
#define LISTENQ 20
#define SERV_PORT 5000
#define INFTIM 1000
void setnonblocking(int sock)
{
    int opts;
    opts=fcntl(sock,F_GETFL);
    if(opts<0)
    {
        perror("fcntl(sock,GETFL)");
        exit(1);
    }
    opts = opts|O_NONBLOCK;
    if(fcntl(sock,F_SETFL,opts)<0)
    {
        perror("fcntl(sock,SETFL,opts)");
        exit(1);
    }   
}
int main()
{
    /* ************************************************** */ 
//    void *handle;
//    handle = dlopen("./lib/libfile.so", RTLD_LAZY);
//    void (*sendfile)();
//    sendfile = dlsym(handle, "sendfile");
//    (* sendfile)();
//    dlclose(handle);    
    /* ************************************************** */ 
    int i, maxi, listenfd, connfd, sockfd,epfd,nfds;
    ssize_t n;
    char line[MAXLINE];
    socklen_t clilen;

    //声明epoll_event结构体的变量,ev用于注册事件, events数组用于回传要处理的事件
    struct epoll_event ev,events[20];

    //生成用于处理accept的epoll专用的文件描述符
    epfd=epoll_create(256);

    struct sockaddr_in clientaddr;
    struct sockaddr_in serveraddr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    //把socket设置为非阻塞方式
    setnonblocking(listenfd);

    //设置与要处理的事件相关的文件描述符
    ev.data.fd=listenfd;
    //设置要处理的事件类型
    ev.events=EPOLLIN|EPOLLET;

    //注册epoll事件
    epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);

    //设置listen socket数据
    memset(&serveraddr, 0x00, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    const char *local_addr = "127.0.0.1";
    inet_aton(local_addr, &(serveraddr.sin_addr));
    serveraddr.sin_port=htons(SERV_PORT); 
    bind(listenfd, (sockaddr *)&serveraddr, sizeof(serveraddr));

    listen(listenfd, LISTENQ);
    maxi = 0;
    for(;;) {
        //等待epoll事件的发生
        nfds=epoll_wait(epfd, events, 20, 500);
        printf("...\n");
        //处理所发生的所有事件     
        for(i=0;i<nfds;++i) {
            printf("nfds..\n");
            //有新的客户链接listenfd
            if(events[i].data.fd == listenfd)
            {
                connfd = accept(listenfd, (sockaddr *)&clientaddr, &clilen);
                if(connfd<0) {
                    perror("connfd<0");
                    exit(1);
                }
                setnonblocking(connfd);
                char *str = inet_ntoa(clientaddr.sin_addr);
                cout << "accapt a connection from " << str << endl;

                //将建立的链接注册到epoll中，使其在epoll的监测下
                //设置用于读操作的文件描述符
                ev.data.fd = connfd;
                //设置用于注测的读操作事件
//                ev.events=EPOLLIN|EPOLLET;
                ev.events=EPOLLIN|EPOLLET;
                //ev.events = EPOLLIN;
                //注册ev
                epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);
            } 
            //已注册的用户发出数据到本server的输入缓存
            else if(events[i].events & EPOLLIN)
            {
                cout << "EPOLLIN" << endl;
                if ((sockfd = events[i].data.fd) < 0) 
                    continue;
                if ((n = read(sockfd, line, MAXLINE)) < 0) {
                    if (errno == ECONNRESET) {
                        close(sockfd);
                        events[i].data.fd = -1;
                    } else
                        std::cout<<"readline error"<<std::endl;
                } else if (n == 0) {
                    close(sockfd);
                    events[i].data.fd = -1;
                }
                line[n] = '\0';
                cout << "read " << line << endl;
                //设置用于写操作的文件描述符
                ev.data.fd = sockfd;
                //设置用于注测的写操作事件
                ev.events = EPOLLOUT|EPOLLET;
//                ev.events = EPOLLIN|EPOLLET;
                //修改sockfd上要处理的事件为EPOLLOUT
                epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
            }
            else if(events[i].events & EPOLLOUT) 
            //已注册的用户请求server发送数据
            {   
                cout << "EPOLLIN 2" << endl;
                sockfd = events[i].data.fd;
                n =  write(sockfd, line, 5);
                printf("n : %d [%s]", n, line);
                //设置用于读操作的文件描述符
                ev.data.fd = sockfd;
                //设置用于注测的读操作事件
                ev.events = EPOLLIN|EPOLLET;
                //修改sockfd上要处理的事件为EPOLIN
                epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
            }
        }
    }
    return 0;
}


#if 0
下面给出测试所用的Perl写的client端,在client中发送10字节的数据,同时让client在发送完数据之后进入死循环, 也就是在发送完之后连接的状态不发生改变--既不再发送数据, 也不关闭连接,这样才能观察出server的状态:
#!/usr/bin/perl
use IO::Socket;
my $host = "127.0.0.1";
my $port = 5000;
my $socket = IO::Socket::INET->new("$host:$port") or die "create socket error $@";
my $msg_out = "1234567890";
print $socket $msg_out;
print "now send over, go to sleep \n";
while (1) {
  sleep(1);
}

#endif




