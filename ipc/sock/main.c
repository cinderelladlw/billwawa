#include "socket.h"
#include <stdio.h>
#define PORT 9999
int main()
{
  int rc;
  int sockfd  = UdpInit(PORT);
  char buff[1024];
  int len;
  rc = UdpRecvFrom(sockfd, buff, 1024, NULL, &len);
  printf("%s\n", buff);
  return 0;
}
