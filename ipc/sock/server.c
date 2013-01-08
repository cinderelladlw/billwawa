#include "socket.h"
#include <stdio.h>

int main()
{
  int sockfd, rc;
  int port = 9997;
  sockfd = TcpListenX("127.0.0.1", port);
  printf("sockfd:%d\n", sockfd);
  int sport;
  char buf[1025]; 
  char sip[100]; 
  while(1) {
    rc = TcpAccept(sockfd, sip, &sport);
    printf("rc : %d\n", rc);
    printf("sip:%s, sport:%d\n", sip, sport);
    int sx = 0;
    rc = TcpRecv(rc, buf, 1024, sx);
  } 
  return 0;
}
