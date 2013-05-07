#include "common.h"

int main(int argc, char **argv)
{
  struct sockaddr_in serveraddr;
  char recvbuf[RECVLEN+1], sendbuf[SENDLEN+1];
  int recvlen, sendlen;
  int sockfd;
 
  memset(&serveraddr, 0x00, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = inet_addr(argv[1]?argv[1]:"127.0.0.1");
  serveraddr.sin_port = htons(atoi(argv[2])?atoi(argv[2]):PORT);
  
  sockfd = socket(AF_INET, SOCK_STREAM, 0); 
  connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
  send(sockfd, "hello", strlen("hello")+1, 0);
  
  return 0;
}
