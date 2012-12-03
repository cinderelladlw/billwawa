#include "socket.h"
#include <stdio.h>

int main()
{
  int sockfd, rc;
  int port = 9998;
  sockfd = TcpListenX("192.168.1.19", port);
  printf("sockfd:%d\n", sockfd);
  int sport;
  char *buf;
  char sip[100];
    rc = TcpAccept(sockfd, sip, &sport);
    printf("sip:%s, sport:%d\n", sip, sport);
    int sx = 10;
    rc = TcpRecv(sockfd, buf, 1024, sx);
  return 0;
}
