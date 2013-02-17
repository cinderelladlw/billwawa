#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>

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
  serv.sin_addr.s_addr = htonl(INADDR_ANY);
  int len = sizeof(serv);
  if(bind(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
    perror("bind");
  }
  char recvbuf[1024];
  int recvnum;
  struct sockaddr_in clie;
  while(1) {
    recvnum = recvfrom(sockfd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr *)&clie, &len);
    if(recvnum < 0) {
      perror("recefrom");
    }
    recvbuf[recvnum] = '\0';
    printf("addr[%s],recvnum[%d],recvbuf[%s]\n",inet_ntoa(clie.sin_addr.s_addr), recvnum, recvbuf);
  }
  close(sockfd);
  return 0;
}
    
