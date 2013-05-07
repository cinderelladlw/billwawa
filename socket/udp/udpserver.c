#include "common.h"

int main(int argc, char **argv)
{
  int sockfd;
  char recvbuf[RECVLEN+1];
  char sendbuf[SENDLEN+1];
  int recvlen, sendlen;
  struct sockaddr_in serveraddr, clientaddr;
  socklen_t clientaddrlen;
 
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  memset(&serveraddr, 0x00, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); 
  serveraddr.sin_port = htons(atoi(argv[1])?atoi(argv[1]):PORT);
  
  bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)); 
  while (1) {
    recvlen = recvfrom(sockfd, recvbuf, RECVLEN+1, 0, (struct sockaddr *)&clientaddr, &clientaddrlen); 
    recvbuf[recvlen] = '\0';
    fputs(recvbuf, stdout);  
  } 
    
  return 0;
}
