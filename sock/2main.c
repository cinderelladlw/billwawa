#include "socket.h"
#include <stdio.h>

#define PORT 9999
int main()
{
  int rc;
//  int sockfd  = UdpInit(PORT);
  int sockfd;
  char buff[1024] = "hello wolrd";
  rc = UdpSendTo(sockfd, buff, 1024,"192.168.1.3",9999);
  printf("%s\n", buff);
  return 0;
}
