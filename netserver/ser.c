#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <sys/epoll.h> 
#include <errno.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <signal.h> 

#define EPOLL_SIZE 10 
#define EVENT_ARR 20 
#define BACK_QUEUE 10 
#define PORT 5000
#define BUF_SIZE 16 
#define REPEAT_NUM 20000 
#define OUT_BUF_SIZE 32*REPEAT_NUM 

int g_srv_fd; 

//由于有可能不能一次write所有的内容，所以需要全局变量保存内容的长度，内容输出到那里， 
//在监听到epollout事件后继续上一次的发送 
char g_out_buf[OUT_BUF_SIZE];//保存输出的内容 
int g_out_buf_offset;                //保存输出到那里 
int g_out_buf_len;                     //保存输出内容的长度 
int g_has_write_buf;        //保存是否要写输出内容 

void setnonblocking(int sockFd) { 
  int opt; 

  opt = fcntl(sockFd, F_GETFL); 
  if (opt < 0) { 
    printf("fcntl(F_GETFL) fail."); 
    exit(-1); 
  } 
  opt |= O_NONBLOCK; 
  if (fcntl(sockFd, F_SETFL, opt) < 0) { 
    printf("fcntl(F_SETFL) fail."); 
    exit(-1); 
  } 
} 

void handle_sig(int signum) { 
  close(g_srv_fd); 
  fprintf(stderr, "receiv sig int"); 
  sleep(5); 
  exit(0); 
} 


int write_out_buf(int fd, char *out_buf,int buf_len,int offset) 
{ 
  int snd_len = write(fd, out_buf+offset, buf_len-offset); 
  int tmp_len; 
  if (snd_len==(buf_len-offset)){ 
    do{ 
      tmp_len = write(fd, out_buf+offset+snd_len, buf_len-offset-snd_len); 
      if (tmp_len>0 && tmp_len<(buf_len-offset-snd_len)){ 
        snd_len += tmp_len; 
        break; 
      } 
      if(tmp_len == -1){ 
        break; 
      } 
      snd_len += tmp_len; 
    }while(tmp_len>0); 
  } 
  if (((snd_len==-1||tmp_len==-1)    && errno ==EAGAIN) || snd_len<buf_len-offset){ 
    fprintf(stderr, "snd receiv eagin or snd_len<out_len\r\n"); 
  } 
  fprintf(stderr, "snd ret:%d\r\n", snd_len); 
  return snd_len; 

} 
// 
void process_write(int fd, char *in_buf,int buf_len) 
{ 
  char *p_out_buf=g_out_buf; 
  int tmp_offset; 
  int i; 
  for(i=0; i<REPEAT_NUM;i++){ 
    tmp_offset+=snprintf(p_out_buf+tmp_offset,OUT_BUF_SIZE-tmp_offset,"%d:%s\r\n", i,in_buf); 
  } 
  g_out_buf_len =tmp_offset; 
  g_out_buf_offset = 0; 
  g_has_write_buf = 0; 
  g_out_buf_offset +=write_out_buf(fd, g_out_buf, g_out_buf_len,g_out_buf_offset); 
  fprintf(stderr, "write_out_buf len:%d wret:%d\r\n", g_out_buf_len, g_out_buf_offset); 
  if (g_out_buf_offset<g_out_buf_len){ 
    g_has_write_buf=1; 
  } 
} 


int main() { 

  int serverFd; 

  serverFd = socket(AF_INET, SOCK_STREAM, 0); 
  g_srv_fd = serverFd; 

  setnonblocking(serverFd); 
  signal(SIGPIPE, SIG_IGN); 
  signal(SIGINT, handle_sig); 

  int epFd = epoll_create(EPOLL_SIZE); 
  struct epoll_event ev, evs[EVENT_ARR]; 
  ev.data.fd = serverFd; 
  ev.events = EPOLLIN | EPOLLET; 
  epoll_ctl(epFd, EPOLL_CTL_ADD, serverFd, &ev); 

  struct sockaddr_in serverAddr; 
  socklen_t serverLen = sizeof(struct sockaddr_in); 
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); 
  serverAddr.sin_port = htons(PORT); 
  serverAddr.sin_family = AF_INET;
  if (bind(serverFd, (struct sockaddr *) &serverAddr, serverLen)) { 
    printf("errno:[%d]:[%s]\n", errno, strerror(errno));
    printf("bind() fail.\n"); 
    exit(-1); 
  } 

  if (listen(serverFd, BACK_QUEUE)) { 
    printf("Listen fail.\n"); 
    exit(-1); 
  } 

  int clientFd; 
  struct sockaddr_in clientAddr; 
  socklen_t clientLen; 
  char buf[BUF_SIZE]; 

  int i = 0; 
  while (1) { 

    int nfds = epoll_wait(epFd, evs, EVENT_ARR, -1); 
    for (i = 0; i < nfds; i++) { 
      if (evs[i].data.fd == serverFd && (evs[i].events & EPOLLIN)) { 
        //epollet需要循环对监听的套接字accept，直到返回EAGAIN 
        do { 
          if ((clientFd = accept(serverFd, 
              (struct sockaddr *) &clientAddr, &clientLen)) < 0) { 
            printf("accept fail.\n"); 
            break; 
          } 
          printf("Connect from %s:%d\n", inet_ntoa(clientAddr.sin_addr), 
              htons(clientAddr.sin_port)); 
          setnonblocking(clientFd); 
          ev.data.fd = clientFd; 
          //注意，为了效率，这里直接对EPOLLIN，EPOLLOUT事件监听 
          ev.events = EPOLLIN | EPOLLET | EPOLLOUT; 
          //ev.events = EPOLLIN; 
          epoll_ctl(epFd, EPOLL_CTL_ADD, clientFd, &ev); 
        }while(clientFd>0); 
      } else if (evs[i].events & EPOLLIN) { 
        fprintf(stderr, "epollin event fd:%d\n", clientFd); 
        if ((clientFd = evs[i].data.fd) > 0) { 
          //epollet需要对套接字循环的读，直到len < BUF_SIZE，或者len<=0返回 
          int len = read(clientFd, buf, BUF_SIZE); 
          fprintf(stderr, "read fd:%d len:%d\n", clientFd, len); 
          if (len == BUF_SIZE) { 
            do { 
              /* 
              if (write(clientFd, buf, len) < 0) { 
                fprintf(stderr, "write fail!\n"); 
                //break; 
              } 
              */ 
              process_write(clientFd, buf, len); 
              if (len < BUF_SIZE) { 
                fprintf(stderr, "len <bufsize %d<%d\n", len, 
                    BUF_SIZE); 
                break; 
              } 
              len = read(clientFd, buf, BUF_SIZE); 
              fprintf(stderr, "read2 fd:%d len:%d\n", clientFd, len); 
            } while (len > 0); 
            if (len == 0) { 
              epoll_ctl(epFd, EPOLL_CTL_DEL, clientFd, &ev); 
              close(clientFd); 
              evs[i].data.fd = -1; 
              fprintf(stderr, "close fd:%d\n", clientFd); 
            } else if (len == -1 && errno != EAGAIN) { 
              fprintf(stderr, " fd:%d\n", clientFd); 
              epoll_ctl(epFd, EPOLL_CTL_DEL, clientFd, &ev); 
              close(clientFd); 
              evs[i].data.fd = -1; 
            } 
          } else if (len > 0 && len < BUF_SIZE) { 
            process_write(clientFd, buf, len); 
          } else if (len == 0 || (len == -1 && errno != EAGAIN)) { 
            epoll_ctl(epFd, EPOLL_CTL_DEL, clientFd, &ev); 
            close(clientFd); 
            evs[i].data.fd = -1; 
            fprintf(stderr, "close fd:%d\n", clientFd); 
          } 

        } 
      } else if(evs[i].events & EPOLLOUT){ 
        //监听到epollout时间，说明发送缓冲去可以写，那继续上一次的写操作 
        clientFd = evs[i].data.fd; 
        fprintf(stderr, "receive epoll out fd:%d\n", clientFd); 
        if(g_has_write_buf){ 
          g_out_buf_offset +=write_out_buf(clientFd, g_out_buf, g_out_buf_len,g_out_buf_offset); 
          fprintf(stderr, "write len :%d writed:%d\n",g_out_buf_len,g_out_buf_offset); 
          if(g_out_buf_offset==g_out_buf_len){ 
            g_has_write_buf = 0; 
          } 
        } 
      }else { 
        printf("other event.\n"); 
      } 
    } 
  } 

  return 0; 
} 
