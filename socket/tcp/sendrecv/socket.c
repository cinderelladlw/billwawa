#include "socket.h"
#include <stdio.h>
#include <stdlib.h>

int TcpRecv(int sockfd, char *buf, int len ,int timeout)
{
  int ret;
  int offset = 0;
  int rcvlen = 0;
  struct timeval tv_buf;
  if(timeout > 0) {
    tv_buf.tv_sec = timeout;
    tv_buf.tv_usec = 0;
    if(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv_buf, sizeof(tv_buf)) == -1) {
      printf("TcpRecv 1 :%s\n", strerror(errno));
      return -1;
    }
  }
  while(1) {
    rcvlen = recv(sockfd, buf+offset, len-offset, 0);
    printf("rcvlen:%d\n", rcvlen);
    if(rcvlen == -1) {
      if(errno == EINTR) continue;
      if(errno == EAGAIN)
        printf("TcpRecv 2:%s\n", strerror(errno));
      else
        printf("TcpRecv 3:%s, %d\n", strerror(errno), errno);
      ret = -1;
      break;
    }
    else if(rcvlen == 0) {
      ret = -1;
      break;
    } else {
      offset += rcvlen;
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
      printf("TcpRecv 4:%s, %d\n", strerror(errno), errno);
    }
  }
}

int TcpSend(int sockfd, const char *buf, int len)
{
  int offset = 0;
  int sndlen = 0;
  while(1) {
    sndlen = send(sockfd, buf+offset, len-offset, 0);
    if(sndlen == -1) {
      if(errno == EINTR) continue;
      printf(".....");
      return -1;
    }
    offset += sndlen;
    if(offset == len) return len;
  }  
}

int TcpRead(int sockfd, char *buf, int len, int lenlen, int timeout)
{
  int ret;
  char lenbuf[21];
  struct timeval tv_buf;
  if(lenlen > 0) {
    if(TcpRecv(sockfd, lenbuf, lenlen, timeout) == -1) return -1;
    lenbuf[lenlen] = 0;
    len = atoi(lenbuf);
    return TcpRecv(sockfd, buf, len, timeout);
  }
  else {
    if(len > 0) return TcpRecv(sockfd, buf, len, timeout);
    if(timeout > 0) {
      tv_buf.tv_sec = timeout;
      tv_buf.tv_usec = 0;
      if(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv_buf, sizeof(tv_buf)) == -1) {
        return -1;
      }
    }
    while(1) {
      len = recv(sockfd, buf, 1024*256, 0);
      if(len == -1) {
        if(errno == EINTR) continue;
        if(errno == EAGAIN)
          printf("...");
        else
          printf("...");
        ret = -1;
        break;
      }
      else if(len == 0) {
        ret = -1;
        break;
      }
      else {
        ret = len;
        break;
      }
    }
    if(timeout > 0) {
      tv_buf.tv_sec = 0;
      tv_buf.tv_usec = 0;
      if(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv_buf, sizeof(tv_buf)) == -1) {
        printf("TcpRead 4:%s, %d\n", strerror(errno), errno);
      }
    }
    return ret;
  }
}

int TcpWrite(int sockfd, const char *buf, int len, int lenlen)
{
  char lenbuf[21];
  if (lenlen > 0) {
    sprintf(lenbuf, "%0*d", lenlen, len);
    if (TcpSend(sockfd, lenbuf, lenlen) == -1) 
      return -1;
  }
  return TcpSend(sockfd, buf, len);  
}

