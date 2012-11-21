#include "socket.h"

int main()
{
  int sockfd, rc;
  int port = 9998;
  char buf[1024];
  sockfd = TcpListen(port);
  int sport;
  char sip[100];
  rc = TcpAccept(sockfd, sip, &sport);
  int sx = 10000;
  rc = TcpRecv(sockfd, buf, 1024, sx);

   
  return 0;
}
