#include "socket.h"
#include <stdio.h>

int main()
{
  int sockfd = TcpConnect("127.0.0.1", 9998);
  printf("sockfd:%d\n", sockfd);
  char *sx = "hello world";
  printf("strlen(sx):%d\n", strlen(sx));
  int len = TcpSend(sockfd, sx, strlen(sx));
  printf("len:%d\n", len);
  return 0;
}
