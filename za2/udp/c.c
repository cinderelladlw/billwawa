#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>

#define IP "127.0.0.1"
#define PORT 7777

int main()
{
  int sockfd;
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd < 0) {
    perror("socket");
  }
  struct sockaddr_in serv;
  serv.sin_family = AF_INET;
  serv.sin_port = htons(PORT);
  serv.sin_addr.s_addr = inet_addr(IP);
  int len = sizeof(serv);
  
  char sendbuf[1024];
  int sendnum;
  fgets(sendbuf, strlen(sendbuf), stdin);
  sendnum = sendto(sockfd, sendbuf, sizeof(sendbuf), 0, (struct sockaddr *)&serv, sizeof(serv));
  close(sockfd);
  return 0;
}

  

