#include <ev.h>
#include <stdio.h>
#include <netinet/in.h>
#include<stdlib.h>
#include <string.h>

#define PORT 57789
#define BUFFER_SIZE 2048
#define MAX_ALLOWED_CLIENT 10240

struct ev_io *libevlist[MAX_ALLOWED_CLIENT] = {NULL};

void accept_cb(struct ev_loop *loop, struct ev_io *watcher, int revents);

void read_cb(struct ev_loop *loop, struct ev_io *watcher, int revents);

void timer_beat(struct ev_loop *loop, struct ev_timer *watcher, int revents);

int freelibev(struct ev_loop *loop, int fd);


int main()
{
    struct ev_loop *loop=ev_default_loop(0);
    int sd;
    struct sockaddr_in addr;
    int addr_len = sizeof(addr);
    
    //创建一个io watcher和一个timer watcher
    struct ev_io socket_accept;
    struct ev_timer timeout_w;
    //创建socket连接
    sd = socket(PF_INET, SOCK_STREAM, 0);
    if(sd < 0)
    {
        printf("socket error\n");
        return -1;
    }
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;
    //正常bind
    if(bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0)
    {
        printf("bind error\n");
        return -1;
    }
    //正常listen
    if(listen(sd, SOMAXCONN) < 0)
    {
        printf("listen error\n");
        return -1;
    }
    //设置fd可重用
    int bReuseaddr=1;
    if(setsockopt(sd,SOL_SOCKET ,SO_REUSEADDR,(const char*)&bReuseaddr,sizeof(bReuseaddr)) != 0)
    {
        printf("setsockopt error in reuseaddr[%d]\n", sd);
        return ;
    }
    
    //初始化io watcher，用于监听fd
    ev_io_init(&socket_accept, accept_cb, sd, EV_READ);
    ev_io_start(loop, &socket_accept);
    
    //可以向远端发送心跳包
    //ev_timer_init(&timeout_w, timer_beat, 1., 0.);
    //ev_timer_start(loop, &timeout_w);
    
    ev_run(loop, 0);
    
    return 1;
}

void accept_cb(struct ev_loop *loop, struct ev_io *watcher, int revents)
{
    /*
        如果有链接，则继续监听fd；
    */
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_sd;
    //创建客户端的io watcher
    struct ev_io *w_client = (struct ev_io*) malloc(sizeof(struct ev_io));
    
    if(w_client == NULL)
    {
        printf("malloc error in accept_cb\n");
        return ;
    }
    
    if(EV_ERROR & revents)
    {
        printf("error event in accept\n");
        return ;
    }
    
    //获取与客户端相连的fd
    client_sd = accept(watcher->fd, (struct sockaddr*)&client_addr, &client_len);
    if(client_sd < 0)
    {
        printf("accept error\n");
        return;
    }
    //如果连接数超出指定范围，则关闭连接
    if( client_sd > MAX_ALLOWED_CLIENT)
    {
        printf("fd too large[%d]\n", client_sd);
        close(client_sd);
        return ;
    }
    
    if(libevlist[client_sd] != NULL)
    {
        printf("client_sd not NULL fd is [%d]\n", client_sd);
        return ;
    }
    
    printf("client connected\n");
    //监听新的fd
    ev_io_init(w_client, read_cb, client_sd, EV_READ);
    ev_io_start(loop, w_client);
    
    libevlist[client_sd] = w_client;

}

void read_cb(struct ev_loop *loop, struct ev_io *watcher, int revents)
{
    char buffer[BUFFER_SIZE];
    ssize_t read;
    
    if(EV_ERROR & revents)
    {
        printf("error event in read\n");
        return ;
    }
    //正常的recv
    read = recv(watcher->fd, buffer, BUFFER_SIZE, 0);
    if(read < 0)
    {
        printf("read error\n");
        return;
    }
    
    if(read == 0)
    {
        printf("client disconnected.\n");
        //ev_io_stop(loop, watcher);
        //free(watcher);
        //如果客户端断开连接，释放响应的资源，并且关闭监听
        freelibev(loop, watcher->fd);
        return;
    }
    else
    {
        //buffer[read] = '\0';
        printf("receive message:%s\n", buffer);
    }
    //返回给客户端
    send(watcher->fd, buffer, read, 0);
    bzero(buffer, read);
}

void timer_beat(struct ev_loop *loop, struct ev_timer *watcher, int revents)
{
    float timeout = 2.0;
    //这里可以发送心跳包，也可以什么都不做
    printf("send beat per[%f]\n",timeout);    
    fflush(stdout);
    
    if(EV_ERROR & revents)
    {
        printf("error event in timer_beat\n");
        return ;
    }
    
    ev_timer_set(watcher, timeout,0.);
    ev_timer_start(loop, watcher);
    return;
}

int freelibev(struct ev_loop *loop, int fd)
{
    /*if(fd > MAX_ALLOWED_CLIENT)
    {
        printf("more than MAX_ALLOWED_CLIENT[%d]", fd);
        return -1;
    }*/
    //清理相关资源
    
    if(libevlist[fd] == NULL)
    {
        printf("the fd already freed[%d]\n", fd);
        return -1;
    }
    
    close(fd);
    ev_io_stop(loop, libevlist[fd]);
    free(libevlist[fd]);
    libevlist[fd] = NULL;
    return 1;
}


