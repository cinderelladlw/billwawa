#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>

#define PORT 8899
#define BACKLOG 5
#define BUFFLEN 10

//缓冲区中读取数据的相关函数
static int TcpSend (int sockfd, char *buf, int len); 
static int TcpRecv (int sockfd, char *buf, int len, int timeout); 
static int TcpWrite(int sockfd, char *buf, int len, int lenlen);
static int TcpRead (int sockfd, char *buf, int len, int lenlen, int timeout);

handle_request(int sock)
{
  char *buff = (char *)malloc(BUFFLEN);
//  int n = recv(sock, buff, BUFFLEN, 0);
//  buff[strlen(buff)] = '\0';
//  printf("\n\n:l:::%s\n", buff);
//  send(sock, buff, BUFFLEN, 0);
  int n = TcpRecv(sock, buff, 100, 10);
  printf(":%s\n", buff);
  int m = TcpSend(sock, buff, 100);
  printf(":m = %d\n", m);
  close(sock); 
}

handle_connect(int sock)
{
  int newsockfd;
  struct sockaddr_in client;
  socklen_t len = sizeof(client);
  if((newsockfd = accept(sock, (struct sockaddr *)&client, &len)) != -1) {
    printf("accept ok\n");
    if(fork() > 0) {
      fprintf(stdout, "accept: %s \n", strerror(errno));
      close(sock);
    }
    else {
      handle_request(newsockfd); 
    }
  }
}

int main()
{
  struct sockaddr_in local;
  memset(&local, 0x00, sizeof(local));
  local.sin_family = AF_INET;
  local.sin_addr.s_addr = htonl(INADDR_ANY);
  local.sin_port = htons(PORT);
  
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  int ret;
  if((ret = bind(sockfd, (struct sockaddr *)&local, sizeof(local))) == -1) {
    fprintf(stdout, "%s", strerror(errno));
  }
  if((ret = listen(sockfd, BACKLOG)) == -1) {
    fprintf(stdout, "%s", strerror(errno));
  }
  handle_connect(sockfd);
  close(sockfd);
  return 0;
}














//发送固定长度的报文
static int TcpSend(int sockfd, char *buf, int len)
{
  int offset = 0;
  int sendlen = 0;
  while(1) {
    sendlen = send(sockfd, buf + offset, len - offset, 0);
    if(sendlen == -1) {
      if(errno == EINTR) continue;
      printf("TcpSend:[%s]", strerror(errno));
      return -1; 
    }
    offset += sendlen;
    if(offset == len) return len;
  }
}
//接受固定长度的报文
static int TcpRecv(int sockfd, char *buf, int len, int timeout)
{
  int ret;
  int offset = 0;
  int recvlen = 0;
  struct timeval tv_buf;
  
  if(timeout > 0) {
    tv_buf.tv_sec = timeout;
    tv_buf.tv_usec = 0;
    if(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv_buf, sizeof(tv_buf)) == -1) {
      printf("TcpRecv1: [%s]", strerror(errno));
      return -1;
    }
  }
  
  while(1) {
    recvlen = recv(sockfd, buf+offset, len-offset, 0);
    if(recvlen == -1) {
      if(errno == EINTR) continue;
      if(errno == EAGAIN)
        printf("TcpRecv2: timeout.[%d]\n", timeout);
      else
        printf("TcpRecv2: [%s]\n", strerror(errno));
      ret = -1;
      break;
    } else if(recvlen == 0) {
      printf("TcpRecv3:[%s]\n", strerror(errno));
      ret == -1;
      break;
    } else {
      offset += recvlen;
      if(offset == len) {
        ret = len;
        break;
      }
    }
  }
  if(timeout > 0) {
    tv_buf.tv_sec = 0;
    tv_buf.tv_usec = 0;
    if(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv_buf, sizeof(tv_buf)) == -1) {
      printf("TcpRecv : [%s]", strerror(errno));
    }
  }
  return ret;
}

//读取预读长度的报文
static int TcpRead(int sockfd, char *buf, int len, int lenlen, int timeout)
{
  int ret;
  char lenbuf[21];
  struct timeval tv_buf;
  
  if(lenlen > 0) {
    if(TcpRecv(sockfd, lenbuf, lenlen, timeout) == -1) return -1;
    lenbuf[lenlen] = '\0';
    len = atoi(lenbuf);
    return TcpRecv(sockfd, buf, len, timeout);
  } else {
    if(len > 0) return TcpRecv(sockfd, buf, len, timeout);
    if(timeout > 0) {
      tv_buf.tv_sec = timeout;
      tv_buf.tv_usec = 0;
      if(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv_buf, sizeof(tv_buf)) == -1) {
        printf("TcpRead : [%s]", strerror(errno));
        return -1;
      }
    }
    while(1) {
      len = recv(sockfd, buf, 1024*256, 0);
      if(len == -1) {
        if(errno = EINTR) continue;
        if(errno = EAGAIN)
          printf("TcpRead:timeout[%d]s\n", timeout);
        else
          printf("TcpRead:[%s]\n", strerror(errno));
        ret = -1;
        break;
      } else if(len == 0) {
        printf("TcpRead2 : [%s]", strerror(errno));
        ret = -1;
        break;
      } else {
        ret = len;
        break;
      }
    }
    if(timeout > 0) {
      tv_buf.tv_sec = 0;
      tv_buf.tv_usec = 0;
      if(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv_buf, sizeof(tv_buf)) == -1) {
        printf("TcpRead3 : [%s]", strerror(errno));
        return -1;
      }
    } 
    return ret;
  } 
}

//写入预读长度的报文

static int TcpWrite(int sockfd, char *buf, int len, int lenlen)
{
  char lenbuf[21];
  if(lenlen > 0) {
    sprintf(lenbuf, "%0*d", lenlen, len);
    if(TcpSend(sockfd, lenbuf, lenlen) == -1) return -1;
  }
  return TcpSend(sockfd, buf, len);
}



